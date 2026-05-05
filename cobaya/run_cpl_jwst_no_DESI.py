"""
Cobaya MCMC run: Lya likelihood + tabulated logMvcut prior.

Sampled parameters: reio_jwst_popIII_{logMvcut, fesc, a, b, d, zpop},
                    H0, omega_b, omega_cdm, logA, n_s,
                    w0_fld, wa_fld
Fixed:              m_ncdm=0.06
"""

import numpy as np
from cobaya.run import run

import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

from likelihood.Lya_likelihood import LyaLikelihood

# ---------------------------------------------------------------------------
info = {
    "params": {
        # --- Reionisation (sampled) ------------------------------------------
        "reio_jwst_popIII_logMvcut": {
            "prior": {"min": 4.0, "max": 8.0},
            "ref": {
                "dist": "norm",
                "scale": 7,
                "scale": 0.5,
            },
            "proposal": 0.8,
            "latex": r"\log M_\mathrm{vcut}",
        },
        "reio_jwst_popIII_fesc": {
            "prior": {"min": 0.05, "max": 0.5},
            "ref":   0.099,
            "proposal": 0.005,
            "latex": r"f_\mathrm{esc}",
        },
        "reio_jwst_popIII_a": {
            "prior": {"dist": "norm", "loc": 0.15,  "scale": 0.008},
            "ref":   0.15,
            "proposal": 0.008,
            "latex": r"a",
        },
        "reio_jwst_popIII_b": {
            "prior": {"dist": "norm", "loc": 28.17, "scale": 0.17},
            "ref":   28.17,
            "proposal": 0.17,
            "latex": r"b",
        },
        "reio_jwst_popIII_d": {
            "prior": {"dist": "norm", "loc": 0.05,  "scale": 0.02},
            "ref":   0.05,
            "proposal": 0.02,
            "latex": r"d",
        },
        "reio_jwst_popIII_zpop": {
            "prior": {"min": 25, "max": 50},
            "ref":   {
                "dist": "norm",
                "loc": 35,
                "ref": 5,
            },
            "proposal": 1.0,
            "latex": r"z_\mathrm{pop}",
        },

        # --- CPL dark energy (sampled) --------------------------------------
        "w0_fld": {
            "prior": {"min": -3.0, "max": 1.0},
            "ref":   {"dist": "norm", "loc": -0.99, "scale": 0.02},
            "proposal": 0.02,
            "latex": r"w_{0,\mathrm{DE}}",
        },
        "wa_fld": {
            "prior": {"min": -3.0, "max": 2.0},
            "ref":   {"dist": "norm", "loc": 0.0, "scale": 0.05},
            "proposal": 0.05,
            "latex": r"w_{a,\mathrm{DE}}",
        },

        # --- Cosmological (sampled) -----------------------------------------
        "H0": {
            "prior": {"min": 20, "max": 100},
            "ref":   {"dist": "norm", "loc": 67, "scale": 2},
            "proposal": 2,
            "latex": r"H_0",
        },
        "omega_b": {
            "prior": {"min": 0.005, "max": 0.1},
            "ref":   {"dist": "norm", "loc": 0.0224, "scale": 0.0001},
            "proposal": 0.0001,
            "latex": r"\Omega_\mathrm{b} h^2",
        },
        "omega_cdm": {
            "prior": {"min": 0.001, "max": 0.25},
            "ref":   {"dist": "norm", "loc": 0.12, "scale": 0.001},
            "proposal": 0.0005,
            "latex": r"\Omega_\mathrm{c} h^2",
        },
        "logA": {
            "prior": {"min": 1.61, "max": 3.91},
            "ref":   {"dist": "norm", "loc": 3.05, "scale": 0.001},
            "proposal": 0.001,
            "drop": True,
            "latex": r"\log(10^{10} A_\mathrm{s})",
        },
        "A_s": {
            "value": "lambda logA: 1e-10*np.exp(logA)",
            "latex": r"A_\mathrm{s}",
        },
        "n_s": {
            "prior": {"min": 0.8, "max": 1.2},
            "ref":   {"dist": "norm", "loc": 0.965, "scale": 0.004},
            "proposal": 0.002,
            "latex": r"n_\mathrm{s}",
        },

        # --- Cosmological (fixed) -------------------------------------------
        "Omega_Lambda": 0,
        "m_ncdm":       {"renames": "mnu", "value": 0.06},
        "k_pivot":      0.05,
        "T_cmb":        2.7255,
        "Omega_k":      0.0,

        # --- Derived --------------------------------------------------------
        "jwst_popIII_tau": {"latex": r"\tau_\mathrm{popIII}"},
        "Omega_m":  {"latex": r"\Omega_\mathrm{m}"},
        "YHe":      {"latex": r"Y_\mathrm{P}"},
        "z_reio":   {"latex": r"z_\mathrm{re}"},
        "omegamh2": {
            "derived": "lambda Omega_m, H0: Omega_m*(H0/100)**2",
            "latex": r"\Omega_\mathrm{m} h^2",
        },
    },

    # ---- Theory ------------------------------------------------------------
    "theory": {
        "classy": {
            "path": "/mnt/Data/projects/class_reio",
            "extra_args": {
                "YHe":                  "BBN",
                "recombination":        "HyRec",
                "Phi_UV_file":          "external/jwst_reio/Phi_UV.dat",
                "reio_parametrization": "reio_jwst_popIII",
                "N_ncdm":               1,
                "N_ur":                 2.0328,
            },
        },
    },

    # ---- Likelihood --------------------------------------------------------
    "likelihood": {
        "Lya": {
            "external": LyaLikelihood,
            "data_file": "cobaya/likelihood/Lya_data.json",
        },
    },

    # ---- External prior on logMvcut ----------------------------------------
    "prior": {
        # (Phi_UV data does not go higher values)
        "log_cutoff_bound": lambda reio_jwst_popIII_logMvcut, omega_cdm, omega_b: (
            0.0 if reio_jwst_popIII_logMvcut + 0.5 * np.log10((omega_cdm + omega_b) / 0.143) < 8.0
            else -np.inf
        ),
    },

    # ---- Sampler -----------------------------------------------------------
    "sampler": {
        "mcmc": {
            "covmat":               "auto",
            "burn_in":              0,
            "Rminus1_stop":         0.01,
            "learn_proposal":       True,
            "learn_every":          50,
        },
    },

    # ---- Output ------------------------------------------------------------
    "output": "cobaya/output/cpl_jwst_no_DESI/cpl_jwst_no_DESI",
    "resume": True,
}

# ---------------------------------------------------------------------------
if __name__ == "__main__":
    updated_info, sampler = run(info)
