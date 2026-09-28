

Lya_data.json consits of different jwst measurements.
Each measurement includes:
 * redshift z
 * error in reshift [z-d1, z+d2]
 * value pairs of [x_HI, P(x_HI)]

## Greig et al. (2024, arXiv:2404.12585) x_HI PDFs

The `greig_z*` entries are digitized from the "Combined" PDF(x_HI) curves in
Greig et al. 2024 (`cobaya/articles/data/ref06_greig_2404.12585.pdf`), one
entry per redshift bin shown in the paper's figures. Each bin's `z` is the
bin center and `d1`/`d2` are the (symmetric) distances to the bin edges, i.e.
the bin spans `[z-d1, z+d2]`:

| dataset key   | redshift bin      | z (center) | d1   | d2   |
|---------------|--------------------|-----------:|-----:|-----:|
| greig_z5p80   | 5.75 < z < 5.85    | 5.80       | 0.05 | 0.05 |
| greig_z5p95   | 5.90 < z < 6.00    | 5.95       | 0.05 | 0.05 |
| greig_z6p05   | 6.00 < z < 6.10    | 6.05       | 0.05 | 0.05 |
| greig_z6p15   | 6.10 < z < 6.20    | 6.15       | 0.05 | 0.05 |
| greig_z6p35   | 6.30 < z < 6.40    | 6.35       | 0.05 | 0.05 |
| greig_z6p55   | 6.50 < z < 6.60    | 6.55       | 0.05 | 0.05 |

Note there is no `6.20 < z < 6.30` panel in the source article (the figure
skips directly from `6.10-6.20` to `6.30-6.40`).

These six entries replace an earlier, coarser `greig_z6p25` entry (a single
hand-digitized curve spanning the whole `z=[5.75, 6.75]` range as one point
with `d1=d2=0.5`); using both together would double-count the same
measurement, so `greig_z6p25` was removed from `Lya_data.json` and
`raw_data/greig_z6p25.txt` when the six per-bin entries were added.

### Digitized x_HI, PDF(x_HI) data points per bin
The exact points stored in each `greig_z*` entry's `xy` list (same values as `raw_data/greig_z*.txt`):

**`greig_z5p80`** (5.75 < z < 5.85, z=5.8)

| x_HI | PDF(x_HI) |
|---:|---:|
| 0.0000 | 0.0000 |
| 0.0173 | 0.1681 |
| 0.0614 | 0.1915 |
| 0.1310 | 0.1950 |
| 0.1924 | 0.1670 |
| 0.3699 | 0.0419 |
| 0.4200 | 0.0206 |
| 0.4706 | 0.0079 |
| 0.5194 | 0.0030 |
| 0.5713 | 0.0013 |
| 0.5981 | 0.0012 |
| 0.9555 | 0.0003 |

**`greig_z5p95`** (5.90 < z < 6.00, z=5.95)

| x_HI | PDF(x_HI) |
|---:|---:|
| 0.0000 | 0.0000 |
| 0.0161 | 0.1812 |
| 0.0607 | 0.1945 |
| 0.1298 | 0.1926 |
| 0.1910 | 0.1633 |
| 0.3701 | 0.0399 |
| 0.4205 | 0.0180 |
| 0.4703 | 0.0064 |
| 0.5228 | 0.0021 |
| 0.5778 | 0.0008 |
| 0.9563 | 0.0003 |

**`greig_z6p05`** (6.00 < z < 6.10, z=6.05)

| x_HI | PDF(x_HI) |
|---:|---:|
| 0.0000 | 0.0000 |
| 0.0182 | 0.1616 |
| 0.0612 | 0.1926 |
| 0.1302 | 0.2041 |
| 0.1904 | 0.1750 |
| 0.3699 | 0.0372 |
| 0.4202 | 0.0158 |
| 0.4706 | 0.0049 |
| 0.5219 | 0.0013 |
| 0.5748 | 0.0009 |
| 0.9556 | 0.0003 |

**`greig_z6p15`** (6.10 < z < 6.20, z=6.15)

| x_HI | PDF(x_HI) |
|---:|---:|
| 0.0000 | 0.0000 |
| 0.0177 | 0.1096 |
| 0.0602 | 0.1357 |
| 0.1313 | 0.1561 |
| 0.1900 | 0.1630 |
| 0.2507 | 0.1458 |
| 0.3099 | 0.1233 |
| 0.4200 | 0.0449 |
| 0.4709 | 0.0222 |
| 0.5165 | 0.0107 |
| 0.5737 | 0.0031 |
| 0.5991 | 0.0010 |
| 0.9557 | 0.0004 |

**`greig_z6p35`** (6.30 < z < 6.40, z=6.35)

| x_HI | PDF(x_HI) |
|---:|---:|
| 0.0000 | 0.0000 |
| 0.0182 | 0.0097 |
| 0.1916 | 0.1402 |
| 0.2518 | 0.1618 |
| 0.3110 | 0.1593 |
| 0.3707 | 0.1349 |
| 0.5217 | 0.0411 |
| 0.5991 | 0.0118 |
| 0.6406 | 0.0058 |
| 0.7029 | 0.0017 |
| 0.7398 | 0.0010 |
| 0.9563 | 0.0005 |

**`greig_z6p55`** (6.50 < z < 6.60, z=6.55)

| x_HI | PDF(x_HI) |
|---:|---:|
| 0.0000 | 0.0000 |
| 0.0161 | 0.1997 |
| 0.0607 | 0.2183 |
| 0.1298 | 0.2065 |
| 0.3115 | 0.0600 |
| 0.3712 | 0.0268 |
| 0.4195 | 0.0110 |
| 0.4703 | 0.0035 |
| 0.5482 | 0.0013 |
| 0.9563 | 0.0003 |

## Mason et al. (2018, arXiv:1709.05356) — dropped (duplicate of Whitler+2020)

`mason_z7` was briefly renamed to `mason_z6p9` and corrected (bin
`[6.5, 7.5]`, `z=6.9`, `d1=0.4`, `d2=0.6` — the LBG sample of Pentericci et
al. 2014 spans 6.5 <~ z <~ 7.5 with median z=6.9), but has since been
**removed from `Lya_data.json`/`raw_data/`**. Whitler et al. 2020 states
explicitly that it re-analyzes the *identical* Pentericci et al. 2014 sample
("M18a used the same sample for their inference... we have used the same
data") — keeping both `mason_z6p9` and `whitler_z7` in the joint likelihood
would double-count one measurement. `whitler_z7` was kept (see below);
`mason_z6p9`/`raw_data/mason_z6p9.txt` were deleted.

## Whitler et al. (2020, arXiv:1911.03499) redshift range

Same correction Mason+2018 got before it was dropped: the underlying
Pentericci et al. 2014 LBG sample spans **6.5 <~ z <~ 7.5**, median z=6.9,
not the round `z=7.0` point estimate previously stored. Updated values:
`z=6.9`, `d1=0.4`, `d2=0.6`. Key/filename unchanged (`whitler_z7`); only the
`z`/`d1`/`d2` fields changed — the digitized posterior curve itself is
unaffected.

## Umeda et al. (2025, arXiv:2504.04683) redshift bins

`umeda_z5`, `umeda_z5p8`, `umeda_z7`, `umeda_z8p6`, `umeda_z10p4` all had
`d1=d2=0` (treated as point estimates). The real bin edges are in the
paper's Table 1 ("Fid1"–"Fid5" subsamples), and are asymmetric/nonzero for
every bin. `z` (the paper's quoted mean) is unchanged; only `d1`/`d2` were
corrected. Key/filenames unchanged; digitized curves unaffected.

| dataset key   | z (unchanged) | d1 (new) | d2 (new) |
|---------------|--------------:|---------:|---------:|
| umeda_z5      | 5.0           | 0.488    | 0.446    |
| umeda_z5p8    | 5.8           | 0.297    | 0.572    |
| umeda_z7      | 7.0           | 0.452    | 0.483    |
| umeda_z8p6    | 8.6           | 1.091    | 0.833    |
| umeda_z10p4   | 10.4          | 0.830    | 2.070    |

## Nakane et al. (2024, arXiv:2312.06804) redshift bins

`nakane_z7`, `nakane_z8`, `nakane_z11` previously used round bin-midpoint
redshifts with `d1=d2=0` (or a crude `±2.0` for the highest bin). The true
`z`/`d1`/`d2` come from directly digitizing the "This work" markers in the
paper's own Fig. 14 (`articles/extract/Nakane/nakane.csv`) — the plotted
redshift is the actual mean/median redshift of the galaxies in each
subsample, not the arithmetic bin midpoint (this matters most for the
highest-z bin: digitized z=10.13 vs. the text bin's arithmetic midpoint of
11.0). Key/filenames unchanged; digitized x_HI posterior curves unaffected.

| dataset key | z (new) | d1 (new) | d2 (new) |
|-------------|--------:|---------:|---------:|
| nakane_z7   | 7.117   | 0.180    | 0.260    |
| nakane_z8   | 7.740   | 0.333    | 0.348    |
| nakane_z11  | 10.131  | 1.511    | 3.068    |

## Kageura et al. (2025, arXiv:2501.05834) redshift bins

`kaguera_z6`, `kaguera_z7`, `kaguera_z8p5`, `kaguera_z12` used round bin
labels with `d1=d2=0` (or `±0.5`/`±2.0`). True bin centers/widths are from
the paper's Table 4. Key/filenames unchanged (repo spells Kageura as
"kaguera" throughout); digitized curves unaffected.

| dataset key   | z (new) | d1 (new) | d2 (new) |
|---------------|--------:|---------:|---------:|
| kaguera_z6    | 5.90    | 0.40     | 0.49     |
| kaguera_z7    | 6.96    | 0.42     | 0.53     |
| kaguera_z8p5  | 8.41    | 0.90     | 1.02     |
| kaguera_z12   | 11.00   | 1.38     | 3.18     |

## Bruton et al. (2023, arXiv:2303.03419) redshift

`bruton_z10p6` used `z=10.6`, `d1=d2=0`. GN-z11's spectroscopic redshift
(Bunker et al. 2023, as quoted in Bruton et al. 2023, p.2) is
`z = 10.603 ± 0.0013`. Updated: `z=10.603`, `d1=0.0013`, `d2=0.0013`. The
x_HI side is unaffected — the paper gives only an upper limit (x_HI < 0.88,
95% CL) with no hidden central value. Note: this dataset is a single galaxy
(GN-z11) reusing the sole published JADES/NIRSpec Lyα EW measurement of that
object (Bunker et al. 2023) — not an independent observation.

## Mason et al. (2019, arXiv:1901.11045) — new dataset, KLASS+BoRG combined

`mason2019_z7p9` is a new addition (not one of the original Fig. S2
references). It combines two sub-samples: **KLASS** (VLT/KMOS, 6 lensed
clusters, 29 galaxies, precise fiducial z=7.9±0.6) and **BoRG** (Treu et al.
2013, 8 blank-field HST-grism z~8 LBGs) — 37 galaxies total. Quoted limits:
KLASS alone x_HI > 0.76 (68%); BoRG alone x_HI > 0.34 (68%); combined
x_HI > 0.76 (68%) / > 0.46 (95%). The paper gives no explicit redshift error
for the *combined* curve (only the KLASS-only subsample's z=7.9±0.6 is
stated precisely), so `d1=d2=0.6` is an approximation carried over from the
KLASS-only value. The `xy` curve is digitized from the paper's Fig. 6
"KLASS+BoRG" combined posterior (`articles/extract/Mason1901/Mason1901.csv`).

### Digitized x_HI, PDF(x_HI) data points (same values as `raw_data/mason2019_z7p9.txt`)

| x_HI | PDF(x_HI) |
|---:|---:|
| 0.0047 | 0.0187 |
| 0.0912 | 0.0281 |
| 0.1306 | 0.0374 |
| 0.1607 | 0.0468 |
| 0.1889 | 0.0608 |
| 0.2415 | 0.0748 |
| 0.2735 | 0.0935 |
| 0.3017 | 0.1169 |
| 0.3336 | 0.1450 |
| 0.3656 | 0.1777 |
| 0.3872 | 0.2105 |
| 0.4201 | 0.2713 |
| 0.4539 | 0.3321 |
| 0.4915 | 0.4116 |
| 0.5160 | 0.4771 |
| 0.5479 | 0.5800 |
| 0.5761 | 0.6642 |
| 0.6100 | 0.8326 |
| 0.6363 | 0.9401 |
| 0.6673 | 1.1600 |
| 0.6833 | 1.2161 |
| 0.7209 | 1.4406 |
| 0.7350 | 1.5248 |
| 0.7500 | 1.6464 |
| 0.7679 | 1.8054 |
| 0.8017 | 2.1001 |
| 0.8158 | 2.1983 |
| 0.8412 | 2.4275 |
| 0.8562 | 2.4977 |
| 0.8750 | 2.6754 |
| 0.8825 | 2.7128 |
| 0.9135 | 3.0402 |
| 0.9398 | 3.2881 |
| 0.9483 | 3.3209 |
| 0.9615 | 3.4799 |
| 0.9746 | 3.8167 |
| 0.9850 | 4.1908 |
| 1.0000 | 4.8924 |

## Not included: Hoag et al. (2019, arXiv:1901.09001), Curtis-Lake et al. (2023)

Both PDFs are present in `articles/data/` but were deliberately **not**
added as datasets. See `articles/data/xHI_true_vs_existing.md` §3 and
`articles/data/dataset_overlap_decision.md` for the overlap analysis behind
these calls.
