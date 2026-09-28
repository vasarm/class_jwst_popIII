Each run below is available in two equivalent forms, kept in sync with each other:

- `setups/python/run_<name>.py` — a Python driver script (`cobaya.run.run(info)`), run with `python cobaya/setups/python/run_<name>.py`.
- `setups/yaml/<name>.yaml` — a plain cobaya YAML config, run with `cobaya-run cobaya/setups/yaml/<name>.yaml`.

Both must be run from the repository root, since output paths and the JWST Lya likelihood's `data_file` are given relative to it.

Before running the MCMC runs make sure the class_jwst_popIII has been compiled and the config paths have correct locations.

## Paths to change if you move this repo

All configs use the `reio_jwst_popIII` reionisation parametrization, which only exists in
the modified CLASS fork checked into this repo at `class_jwst_popIII/`.

Every `setups/yaml/*.yaml` and `setups/python/run_*.py` file hardcodes three
absolute paths into it under `theory: classy:` (YAML) / `info["theory"]["classy"]`
(Python), currently set to `/mnt/Data/projects/class_jwst_popIII/class_jwst_popIII`:

- `path` — the fork directory itself.
- `extra_args: base_path` — same value; without it `classy` can't find its own `external/` data files.
- `extra_args: Phi_UV_file` — `<path above>/external/jwst_reio/Phi_UV.dat`.

The `Lya` likelihood block (in `*_jwst*.yaml`) also has two path-bearing keys, set to
absolute paths so the run doesn't depend on the process's working directory:

```yaml
Lya:
  class: Lya_likelihood.LyaLikelihood
  python_path: /mnt/Data/projects/class_jwst_popIII/cobaya/likelihood
  data_file: /mnt/Data/projects/class_jwst_popIII/cobaya/likelihood/Lya_data.json
```

If you clone or move the repo, update both to the new `cobaya/likelihood` location too.

## ΛCDM

| Run                         | low-l | high-l | lensing | DESI DR2 | DES-Dovekie | Lya (JWST) |
|-----------------------------|:----:|:-----:|:-------:|:----:|:-----------:|:----------:|
| `lcdm_planck`               | ✓    | ✓     | ✓       |      |             |            |
| `lcdm_planck_jwst`          |      | ✓     | ✓       |      |             | ✓          |
| `lcdm_planck_desi_des`      |      | ✓     | ✓       | ✓    | ✓           |            |
| `lcdm_planck_desi_des_jwst` |      | ✓     | ✓       | ✓    | ✓           | ✓          |

## CPL (w0waCDM)

| Run                        | low-l | high-l | lensing | DESI DR2 | DES-Dovekie | Lya (JWST) |
|----------------------------|:----:|:-----:|:-------:|:----:|:-----------:|:----------:|
| `cpl_planck`               | ✓    | ✓     | ✓       |      |             |            |
| `cpl_planck_jwst`          |      | ✓     | ✓       |      |             | ✓          |
| `cpl_planck_desi_des`      |      | ✓     | ✓       | ✓    | ✓           |            |
| `cpl_planck_desi_des_jwst` |      | ✓     | ✓       | ✓    | ✓           | ✓          |
