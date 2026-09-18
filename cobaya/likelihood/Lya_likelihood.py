"""
Lya likelihood for Cobaya using CLASS (classy) using x{H_I} - neutral hydrogen
"""


import json
import numpy as np
import scipy as sc
from scipy.integrate import quad, fixed_quad
from cobaya.likelihood import Likelihood


class LyaLikelihood(Likelihood):

    data_file: str = ""
    verbose: bool = False

    _FLOOR = 1e-10

    # ------------------------------------------------------------------ #
    def initialize(self):
        if not self.data_file:
            raise ValueError("LyaLikelihood: 'data_file' must be set in config.yaml.")

        self.data = self._load_Lya_data()
        if len(self.data) == 0:
            raise ImportError(f"Data file is empty! (loc = {self.data_file})")

        for key in self.data:
            xy = self.data[key]["xy"]
            self.data[key]["f"] = sc.interpolate.interp1d(
                xy[:, 0], xy[:, 1],
                kind='linear', bounds_error=False, fill_value="extrapolate", assume_sorted=True
            )
            safe_f = self._safe_integrand(self.data[key]["f"])
            self.data[key]["safe_f"] = safe_f
            norm = 0.0
            for a, b in zip(np.linspace(0.0, 1.0, 9)[:-1], np.linspace(0.0, 1.0, 9)[1:]):
                seg, _ = quad(safe_f, a, b, limit=100, epsabs=1e-5, epsrel=1e-4)
                norm += seg
            self.data[key]["norm"] = max(norm, self._FLOOR)

        self.log.info("Lya Likelihood: loaded %s", list(self.data.keys()))

    @staticmethod
    def _safe_integrand(f):
        def safe_f(x):
            v = float(f(x))
            if not np.isfinite(v) or v < 0.0:
                return 0.0
            return v
        return safe_f

    def _load_Lya_data(self):
        with open(self.data_file, 'r') as f:
            raw = json.load(f)
        return {
            key: {'z': d['z'], 'd1': d['d1'], 'd2': d['d2'], 'xy': np.array(d['xy'])}
            for key, d in raw.items()
        }
    # ------------------------------------------------------------------ #
    def get_requirements(self):
        return {"CLASS_thermodynamics": None}

    # ------------------------------------------------------------------ #
    def logp(self, **params_values):
        th = self.provider.get_CLASS_thermodynamics()
        z_arr = np.array(th["z"])
        xHI_arr = np.array(th["x_HI"])
        idx = np.argsort(z_arr)
        z_sorted = z_arr[idx]
        xHI_sorted = xHI_arr[idx]

        loglike = 0.0
        if self.verbose:
            print(f"\n{'Dataset':30s} {'z':>6}  {'x_HI':>8}  {'norm':>10}  {'p':>10}  {'logp':>10}")
            print("-" * 82)

        for name, d in self.data.items():
            z0, d1, d2 = d["z"], d["d1"], d["d2"]
            safe_f, norm = d["safe_f"], d["norm"]

            if d1 == 0.0 and d2 == 0.0:
                # point: single evaluation of the model at z0
                x_HI_val = float(np.interp(z0, z_sorted, xHI_sorted))
            else:
                # z-range: average the model's x_HI(theta, z) over [z0-d1, z0+d2]
                # first, then evaluate the dataset's posterior once at that single
                # averaged value -- i.e. p_i(<x_HI(theta,z)>_i), matching
                # arXiv:2604.24835 eq. 19 ("the average is computed over the
                # redshift range of the posterior").
                def xhi_of_z(z_pts):
                    return np.interp(z_pts, z_sorted, xHI_sorted)
                integral, _ = fixed_quad(xhi_of_z, z0 - d1, z0 + d2, n=20)
                x_HI_val = integral / (d1 + d2)

            p = float(safe_f(x_HI_val)) / norm

            lp = np.log(max(p, self._FLOOR))
            loglike += lp

            if self.verbose:
                print(f"  {name:28s} {z0:6.2f}  {x_HI_val:8.4f}  {norm:10.5f}  {p:10.5f}  {lp:10.4f}")

        return loglike
