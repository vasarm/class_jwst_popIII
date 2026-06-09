import numpy as np
from cobaya.run import run

import sys, os
# sys.path.insert(0, os.path.dirname(__file__))

# ---------------------------------------------------------------------------
info = {
    # "debug": True, # NB! REMOVE IT OR COMMENT OUT FOR ACTUAL RUN
    "params": {
        # --- Reionisation (sampled) ------------------------------------------
        "reio_jwst_popIII_logMvcut": {
            "prior": {"min": 4.0, "max": 8.0},
            "ref":   {"dist": "norm", "loc": 6.0, "scale": 0.5},
            "proposal": 0.3,
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
            "ref":   {"dist": "norm", "loc": 35, "scale": 5},
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
            "ref":   {"dist": "norm", "loc": 67.36, "scale": 1},
            "proposal": 0.5,
            "latex": r"H_0",
        },
        "omega_b": {
            "prior": {"min": 0.005, "max": 0.1},
            "ref":   {"dist": "norm", "loc": 0.02237, "scale": 0.0002},
            "proposal": 0.0001,
            "latex": r"\Omega_\mathrm{b} h^2",
        },
        "omega_cdm": {
            "prior": {"min": 0.001, "max": 0.25},
            "ref":   {"dist": "norm", "loc": 0.1200, "scale": 0.001},
            "proposal": 0.0005,
            "latex": r"\Omega_\mathrm{c} h^2",
        },
        "logA": {
            "prior": {"min": 1.61, "max": 3.91},
            "ref":   {"dist": "norm", "loc": 3.044, "scale": 0.002},
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
            "ref":   {"dist": "norm", "loc": 0.9649, "scale": 0.004},
            "proposal": 0.002,
            "latex": r"n_\mathrm{s}",
        },

        # --- Cosmological (fixed) -------------------------------------------
        "m_ncdm":  {"renames": "mnu", "value": 0.06},
        "k_pivot": 0.05,
        "T_cmb":   2.7255,
        "Omega_k": 0.0,
        "Omega_Lambda": 0, # Turn on dynamical DE

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
            "extra_args": {
                "YHe":                  "BBN",
                "recombination":        "HyRec",
                "Phi_UV_file":          "/home/marvas/cobaya/DESI_tau/class/external/jwst_reio/Phi_UV.dat",
                "reio_parametrization": "reio_jwst_popIII",
                "N_ncdm":               1,
                "N_ur":                 2.0328,
            },
        },
    },

    # ---- Likelihood --------------------------------------------------------
    # Planck 2018 no low-ell: plik + lensing only
    # + DESI DR2 BAO + DES-Dovekie SN Ia
    "likelihood": {
        "planck_2018_highl_plik.TTTEEE": None,
        "planck_2018_lensing.clik":    None,
        "bao.desi_dr2":                  None,
        "sn.desdovekie":                 None,
    },

    # ---- External prior on logMvcut ----------------------------------------
    "prior": {
        "log_cutoff_bound": lambda reio_jwst_popIII_logMvcut, omega_cdm, omega_b: (
            0.0 if reio_jwst_popIII_logMvcut + 0.5 * np.log10((omega_cdm + omega_b) / 0.143) < 8.0
            else -np.inf
        ),
    },

    # ---- Sampler -----------------------------------------------------------
    "sampler": {
        "mcmc": {
            "covmat":                             "auto",
            "burn_in":                            0,
            "Rminus1_stop":                       0.01,
            "learn_proposal":                     True,
            "learn_every":                        400,
            "measure_speeds":                     True,
            "drag":                               True,
            "oversample_power":                   0.4,
            "learn_proposal_Rminus1_max_early":   100,
        },
    },

    # ---- Output ------------------------------------------------------------
    "output": "cobaya_runs/output/cpl_planck_desi_des/cpl_planck_desi_des",
    "resume": True,
}

# ---------------------------------------------------------------------------
if __name__ == "__main__":
    updated_info, sampler = run(info)
