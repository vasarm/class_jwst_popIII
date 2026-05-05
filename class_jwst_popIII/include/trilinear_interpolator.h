/**
 * @file trilinear_interpolator.h
 *
 * Trilinear interpolation on a uniform 3D grid.
 */

#ifndef __TRILINEAR_INTERPOLATOR__
#define __TRILINEAR_INTERPOLATOR__

#include "common.h"

/**
 * Descriptor for a uniform 3D grid.
 *
 * The value table is owned by the caller; this struct only holds a pointer.
 * Flat storage order: table[i0 * n1*n2 + i1 * n2 + i2].
 */
struct trilinear_grid {
  /* axis 0 */
  double x0_min, x0_max, dx0;
  int    n0;
  /* axis 1 */
  double x1_min, x1_max, dx1;
  int    n1;
  /* axis 2 */
  double x2_min, x2_max, dx2;
  int    n2;
  /* value table (caller-owned) */
  double * table;
};

#ifdef __cplusplus
extern "C" {
#endif

int trilinear_init(struct trilinear_grid * grid,
                   double x0_min, double x0_max, int n0,
                   double x1_min, double x1_max, int n1,
                   double x2_min, double x2_max, int n2,
                   double * table,
                   ErrorMsg errmsg);

int trilinear_interp(const struct trilinear_grid * grid,
                     double x0, double x1, double x2,
                     double * result,
                     ErrorMsg errmsg);

int trilinear_read_header(const char * filename,
                          int * n0,    int * n1,    int * n2,
                          double * x0_min, double * x1_min, double * x2_min,
                          double * x0_max, double * x1_max, double * x2_max,
                          ErrorMsg errmsg);

int trilinear_read_table(const char * filename,
                         int n_total,
                         double * table,
                         ErrorMsg errmsg);

#ifdef __cplusplus
}
#endif

#endif /* __TRILINEAR_INTERPOLATOR__ */
