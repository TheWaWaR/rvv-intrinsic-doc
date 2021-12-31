#include <riscv_vector.h>


void matmul(double **a, double **b, double **c, int n, int m, int o) {
  size_t vlmax = vsetvlmax_e64m1();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      double *ptr_a = &a[i][0];
      double *ptr_b = &b[j][0];
      int k = o;
      vfloat64m1_t vec_s = vfmv_v_f_f64m1(0, vlmax);
      vfloat64m1_t vec_zero = vfmv_v_f_f64m1(0, vlmax);
      for (size_t vl; k > 0; k -= vl, ptr_a += vl, ptr_b += vl) {
        vl = vsetvl_e64m1(k);

        vfloat64m1_t vec_a = vle64_v_f64m1(ptr_a, vl);
        vfloat64m1_t vec_b = vle64_v_f64m1(ptr_b, vl);

        vec_s = vfmacc_vv_f64m1(vec_s, vec_a, vec_b, vl);
      }

      vfloat64m1_t vec_sum;
      vec_sum = vfredsum_vs_f64m1_f64m1(vec_zero, vec_s, vec_zero, vlmax);
      double sum = vfmv_f_s_f64m1_f64(vec_sum);
      c[i][j] = sum;
    }
  }
}
