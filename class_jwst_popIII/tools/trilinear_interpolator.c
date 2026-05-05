/**
 * @file trilinear_interpolator.c
 *
 * Trilinear interpolation on a uniform 3D grid.
 *
 * The grid axes are defined at init time (min, max, number of points).
 * Values are stored in a flat C-order array:
 *   table[i*n1*n2 + j*n2 + k]  with i along axis 0, j along axis 1, k along axis 2.
 *
 * Queries outside the grid are clamped to the boundary (no extrapolation).
 */

#include "trilinear_interpolator.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Initialise a trilinear_grid from caller-supplied bounds and sizes.
 *
 * @param grid     Output: pointer to grid struct to fill
 * @param x0_min   Axis-0 minimum
 * @param x0_max   Axis-0 maximum
 * @param n0       Number of points along axis 0  (>= 2)
 * @param x1_min   Axis-1 minimum
 * @param x1_max   Axis-1 maximum
 * @param n1       Number of points along axis 1  (>= 2)
 * @param x2_min   Axis-2 minimum
 * @param x2_max   Axis-2 maximum
 * @param n2       Number of points along axis 2  (>= 2)
 * @param table    Flat array of n0*n1*n2 values in C order [i0][i1][i2]
 *                 (the struct stores a pointer; the caller owns the memory)
 * @param errmsg   Output: error message buffer
 * @return _SUCCESS_ or _FAILURE_
 */
int trilinear_init(struct trilinear_grid * grid,
                   double x0_min, double x0_max, int n0,
                   double x1_min, double x1_max, int n1,
                   double x2_min, double x2_max, int n2,
                   double * table,
                   ErrorMsg errmsg) {

  class_test(n0 < 2 || n1 < 2 || n2 < 2,
             errmsg,
             "trilinear_init: each axis must have at least 2 points (got %d,%d,%d)",
             n0, n1, n2);

  class_test(x0_max <= x0_min || x1_max <= x1_min || x2_max <= x2_min,
             errmsg,
             "trilinear_init: axis max must be strictly greater than min");

  class_test(table == NULL,
             errmsg,
             "trilinear_init: table pointer is NULL");

  grid->x0_min = x0_min;  grid->x0_max = x0_max;  grid->n0 = n0;
  grid->x1_min = x1_min;  grid->x1_max = x1_max;  grid->n1 = n1;
  grid->x2_min = x2_min;  grid->x2_max = x2_max;  grid->n2 = n2;

  grid->dx0 = (x0_max - x0_min) / (n0 - 1);
  grid->dx1 = (x1_max - x1_min) / (n1 - 1);
  grid->dx2 = (x2_max - x2_min) / (n2 - 1);

  grid->table = table;

  return _SUCCESS_;
}

/**
 * Evaluate the interpolated value at (x0, x1, x2).
 *
 * Points outside [min, max] on any axis are clamped to the boundary.
 *
 * @param grid   Input: initialised grid struct
 * @param x0     Query coordinate along axis 0
 * @param x1     Query coordinate along axis 1
 * @param x2     Query coordinate along axis 2
 * @param result Output: interpolated value
 * @param errmsg Output: error message buffer
 * @return _SUCCESS_ or _FAILURE_
 */
int trilinear_interp(const struct trilinear_grid * grid,
                     double x0, double x1, double x2,
                     double * result,
                     ErrorMsg errmsg) {

  class_test(grid->table == NULL,
             errmsg,
             "trilinear_interp: grid has not been initialised (table is NULL)");

  /* --- axis 0 --- */
  double f0 = (x0 - grid->x0_min) / grid->dx0;
  int    i0 = (int)f0;
  if (i0 < 0)             i0 = 0;
  if (i0 > grid->n0 - 2) i0 = grid->n0 - 2;
  double u = f0 - i0;
  if (u < 0.) u = 0.;
  if (u > 1.) u = 1.;

  /* --- axis 1 --- */
  double f1 = (x1 - grid->x1_min) / grid->dx1;
  int    i1 = (int)f1;
  if (i1 < 0)             i1 = 0;
  if (i1 > grid->n1 - 2) i1 = grid->n1 - 2;
  double v = f1 - i1;
  if (v < 0.) v = 0.;
  if (v > 1.) v = 1.;

  /* --- axis 2 --- */
  double f2 = (x2 - grid->x2_min) / grid->dx2;
  int    i2 = (int)f2;
  if (i2 < 0)             i2 = 0;
  if (i2 > grid->n2 - 2) i2 = grid->n2 - 2;
  double w = f2 - i2;
  if (w < 0.) w = 0.;
  if (w > 1.) w = 1.;

  /* --- flat-index helper: table[i][j][k] = table[i*n1*n2 + j*n2 + k] --- */
  int n1n2 = grid->n1 * grid->n2;
  int n2   = grid->n2;

#define VAL(i,j,k) grid->table[(i)*n1n2 + (j)*n2 + (k)]

  /* --- trilinear interpolation --- */
  *result =
    (1.-u)*(1.-v)*(1.-w) * VAL(i0,   i1,   i2  ) +
       u  *(1.-v)*(1.-w) * VAL(i0+1, i1,   i2  ) +
    (1.-u)*    v *(1.-w) * VAL(i0,   i1+1, i2  ) +
       u  *    v *(1.-w) * VAL(i0+1, i1+1, i2  ) +
    (1.-u)*(1.-v)*   w   * VAL(i0,   i1,   i2+1) +
       u  *(1.-v)*   w   * VAL(i0+1, i1,   i2+1) +
    (1.-u)*    v *   w   * VAL(i0,   i1+1, i2+1) +
       u  *    v *   w   * VAL(i0+1, i1+1, i2+1);

#undef VAL

  return _SUCCESS_;
}

/**
 * Read the 3-line header of the data file:
 *
 *   n0    n1    n2
 *   x0_min  x1_min  x2_min
 *   x0_max  x1_max  x2_max
 *   x0  x1  x2  val
 *   ...
 *
 * Call this first, then class_alloc, then trilinear_read_table.
 *
 * @param filename  Input:  path to the data file
 * @param n0        Output: number of points along axis 0
 * @param n1        Output: number of points along axis 1
 * @param n2        Output: number of points along axis 2
 * @param x0_min    Output: axis 0 minimum
 * @param x1_min    Output: axis 1 minimum
 * @param x2_min    Output: axis 2 minimum
 * @param x0_max    Output: axis 0 maximum
 * @param x1_max    Output: axis 1 maximum
 * @param x2_max    Output: axis 2 maximum
 * @param errmsg    Output: error message buffer
 * @return _SUCCESS_ or _FAILURE_
 */
int trilinear_read_header(const char * filename,
                          int * n0,    int * n1,    int * n2,
                          double * x0_min, double * x1_min, double * x2_min,
                          double * x0_max, double * x1_max, double * x2_max,
                          ErrorMsg errmsg) {

  FILE * input_file;
  int status;

  input_file = fopen(filename, "r");
  class_test(input_file == NULL,
             errmsg,
             "trilinear_read_header: could not open file '%s'", filename);

  status = fscanf(input_file, "%d %d %d", n0, n1, n2);
  if (status != 3) {
    fclose(input_file);
    class_stop(errmsg, "trilinear_read_header: row 1 of '%s' must be 'n0 n1 n2'", filename);
  }

  if (*n0 < 2 || *n1 < 2 || *n2 < 2) {
    fclose(input_file);
    class_stop(errmsg, "trilinear_read_header: grid dimensions must be >= 2 (got %d %d %d)",
               *n0, *n1, *n2);
  }

  status = fscanf(input_file, "%lf %lf %lf", x0_min, x1_min, x2_min);
  if (status != 3) {
    fclose(input_file);
    class_stop(errmsg, "trilinear_read_header: row 2 of '%s' must be 'x0_min x1_min x2_min'", filename);
  }

  status = fscanf(input_file, "%lf %lf %lf", x0_max, x1_max, x2_max);
  if (status != 3) {
    fclose(input_file);
    class_stop(errmsg, "trilinear_read_header: row 3 of '%s' must be 'x0_max x1_max x2_max'", filename);
  }

  fclose(input_file);
  return _SUCCESS_;
}

/**
 * Read the data rows of a table file (skipping the header) into a
 * pre-allocated flat array.
 *
 * File format:
 *   n0  n1  n2            <- row 1: grid dimensions
 *   x0_min x1_min x2_min  <- row 2: axis minima
 *   x0_max x1_max x2_max  <- row 3: axis maxima
 *   val                   <- one value per line, C-order (n0*n1*n2 rows)
 *   ...
 *
 * @param filename  Input:  path to the data file
 * @param n_total   Input:  number of data rows to read (n0*n1*n2)
 * @param table     Output: pre-allocated array of size n_total
 * @param errmsg    Output: error message buffer
 * @return _SUCCESS_ or _FAILURE_
 */
int trilinear_read_table(const char * filename,
                         int n_total,
                         double * table,
                         ErrorMsg errmsg) {

  FILE * input_file;
  int row, status, dummy0, dummy1, dummy2;
  double dtmp;

  input_file = fopen(filename, "r");
  class_test(input_file == NULL,
             errmsg,
             "trilinear_read_table: could not open file '%s'", filename);

  /* skip 3 header lines: dimensions, mins, maxs */
  fscanf(input_file, "%d %d %d", &dummy0, &dummy1, &dummy2);
  fscanf(input_file, "%lf %lf %lf", &dtmp, &dtmp, &dtmp);
  fscanf(input_file, "%lf %lf %lf", &dtmp, &dtmp, &dtmp);

  /* read one value per row */
  for (row = 0; row < n_total; row++) {
    status = fscanf(input_file, "%lf", &table[row]);
    if (status != 1) {
      fclose(input_file);
      class_stop(errmsg,
                 "trilinear_read_table: read error at row %d of '%s' (expected %d rows)",
                 row, filename, n_total);
    }
  }

  fclose(input_file);
  return _SUCCESS_;
}
