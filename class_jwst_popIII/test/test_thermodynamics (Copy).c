/** @file class.c
 * Julien Lesgourgues, 17.04.2011
 */

/* th main runs only the background and thermodynamics parts */

#include "class.h"

int main(int argc, char **argv) {

  struct precision pr;        /* for precision parameters */
  struct background ba;       /* for cosmological background */
  struct thermodynamics th;           /* for thermodynamics */
  struct perturbations pt;         /* for source functions */
  struct transfer tr;        /* for transfer functions */
  struct primordial pm;       /* for primordial spectra */
  struct harmonic hr;          /* for output spectra */
  struct fourier fo;        /* for non-linear spectra */
  struct lensing le;          /* for lensed sepctra */
  struct distortions sd;      /* for spectral distortions */
  struct output op;           /* for output files */
  ErrorMsg errmsg;            /* for error message */

  if (input_init(argc, argv,&pr,&ba,&th,&pt,&tr,&pm,&hr,&fo,&le,&sd,&op,errmsg) == _FAILURE_) {
    printf("\n\nError running input_init_from_arguments \n=>%s\n",errmsg);
    return _FAILURE_;
  }

  if (background_init(&pr,&ba) == _FAILURE_) {
    printf("\n\nError running background_init \n=>%s\n",ba.error_message);
    return _FAILURE_;
  }

  if (thermodynamics_init(&pr,&ba,&th) == _FAILURE_) {
    printf("\n\nError in thermodynamics_init \n=>%s\n",th.error_message);
    return _FAILURE_;
  }

  /********************************************/
  /***** output thermodynamics quantities *****/
  /********************************************/

  int i;
  double tau;
  double z;
  int last_index;
  double pvecback[30];
  double pvecthermo[30];

  printf("# %12s %14s %14s %14s\n", "z", "x_e", "x_HI", "dkappa");

  /* fine-sampling near zpop to expose interpolation issues */

  printf("# --- fine sampling near zpop ---\n");
  for (z = 40.; z <= 50.; z += 0.05) {

    background_at_z(&ba,z,normal_info,inter_normal,&last_index,pvecback);
    thermodynamics_at_z(&ba,&th,z,inter_normal,&last_index,pvecback,pvecthermo);
    background_tau_of_z(&ba,z,&tau);

    if (pvecthermo[th.index_th_xe] < 0.)
      fprintf(stderr, "WARNING: x_e < 0 at z=%.4f  x_e=%.6e  x_HI=%.6e  dkappa=%.6e\n",
              z, pvecthermo[th.index_th_xe], pvecthermo[th.index_th_x_HI], pvecthermo[th.index_th_dkappa]);

    printf("%14.4e %14.4e %14.4e %14.4e\n",
           z,
           pvecthermo[th.index_th_xe],
           pvecthermo[th.index_th_x_HI],
           pvecthermo[th.index_th_dkappa]
           /* ,pvecthermo[th.index_th_ddkappa]    */
           /* ,pvecthermo[th.index_th_dddkappa]   */
           /* ,pvecthermo[th.index_th_exp_m_kappa]*/
           /* ,pvecthermo[th.index_th_g]          */
           /* ,pvecthermo[th.index_th_dg]         */
           /* ,pvecthermo[th.index_th_ddg]        */
           /* ,pvecthermo[th.index_th_Tb]         */
           /* ,pvecthermo[th.index_th_cb2]        */
           /* ,pvecthermo[th.index_th_kappa_b]    */
           /* ,pvecthermo[th.index_th_rate]       */
           );
  }

  /* first, quantities stored in table */

  printf("# --- table rows (z <= 50) ---\n");
  for (i=0; i < th.tt_size; i++) {

    if (th.z_table[i] > 50.) continue;

    background_tau_of_z(&ba,th.z_table[i],&tau);

    printf("%14.4e %14.4e %14.4e %14.4e\n",
	   th.z_table[i],
	   th.thermodynamics_table[i*th.th_size+th.index_th_xe],
	   th.thermodynamics_table[i*th.th_size+th.index_th_x_HI],
	   th.thermodynamics_table[i*th.th_size+th.index_th_dkappa]
	   /* ,th.thermodynamics_table[i*th.th_size+th.index_th_ddkappa]    */
	   /* ,th.thermodynamics_table[i*th.th_size+th.index_th_dddkappa]   */
	   /* ,th.thermodynamics_table[i*th.th_size+th.index_th_exp_m_kappa]*/
	   /* ,th.thermodynamics_table[i*th.th_size+th.index_th_g]          */
	   /* ,th.thermodynamics_table[i*th.th_size+th.index_th_dg]         */
	   /* ,th.thermodynamics_table[i*th.th_size+th.index_th_ddg]        */
	   /* ,th.thermodynamics_table[i*th.th_size+th.index_th_Tb]         */
	   /* ,th.thermodynamics_table[i*th.th_size+th.index_th_cb2]        */
	   /* ,th.thermodynamics_table[i*th.th_size+th.index_th_kappa_b]    */
	   /* ,th.thermodynamics_table[i*th.th_size+th.index_th_rate]       */
	   );
  }

  

  /* the function thermodynamics_at_z knows how to extrapolate at
     redshifts above the maximum redshift in the table. Here we add to
     the previous output a few more points at higher redshift. */

  for (z = th.z_table[th.tt_size-1]; z < 1000*th.z_table[th.tt_size-1]; z *= 2.) {

    background_at_z(&ba,z,normal_info,inter_normal,&last_index,pvecback);

    thermodynamics_at_z(&ba,&th,z,inter_normal,&last_index,pvecback,pvecthermo);

    printf("%14.4e %14.4e %14.4e %14.4e\n",
	   z,
	   pvecthermo[th.index_th_xe],
	   pvecthermo[th.index_th_x_HI],
	   pvecthermo[th.index_th_dkappa]
	   /* ,pvecthermo[th.index_th_ddkappa]    */
	   /* ,pvecthermo[th.index_th_dddkappa]   */
	   /* ,pvecthermo[th.index_th_exp_m_kappa]*/
	   /* ,pvecthermo[th.index_th_g]          */
	   /* ,pvecthermo[th.index_th_dg]         */
	   /* ,pvecthermo[th.index_th_ddg]        */
	   /* ,pvecthermo[th.index_th_Tb]         */
	   /* ,pvecthermo[th.index_th_cb2]        */
	   /* ,pvecthermo[th.index_th_kappa_b]    */
	   /* ,pvecthermo[th.index_th_rate]       */
	   );

  }

  /****** all calculations done, now free the structures ******/

  if (thermodynamics_free(&th) == _FAILURE_) {
    printf("\n\nError in thermodynamics_free \n=>%s\n",th.error_message);
    return _FAILURE_;
  }

  if (background_free(&ba) == _FAILURE_) {
    printf("\n\nError in background_free \n=>%s\n",ba.error_message);
    return _FAILURE_;
  }

  return _SUCCESS_;

}
