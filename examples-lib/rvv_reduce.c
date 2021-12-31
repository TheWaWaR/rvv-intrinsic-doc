#include <riscv_vector.h>

void reduce(double *a, double *b, double *result_sum, int *result_count,
              int n) {
  int count = 0;
  // set vlmax and initialize variables
  size_t vlmax = vsetvlmax_e64m1();
  vfloat64m1_t vec_zero = vfmv_v_f_f64m1(0, vlmax);
  vfloat64m1_t vec_s = vfmv_v_f_f64m1(0, vlmax);
  vfloat64m1_t vec_one = vfmv_v_f_f64m1(1, vlmax);
  for (size_t vl; n > 0; n -= vl, a += vl, b += vl) {
    vl = vsetvl_e64m1(n);

    vfloat64m1_t vec_a = vle64_v_f64m1(a, vl);
    vfloat64m1_t vec_b = vle64_v_f64m1(b, vl);

    vbool64_t mask = vmfne_vv_f64m1_b64(vec_a, vec_zero, vl);

    vec_s = vfmacc_vv_f64m1_m(mask, vec_s, vec_a, vec_b, vl);
    count = count + vpopc_m_b64(mask, vl);
  }
  vfloat64m1_t vec_sum;
  vec_sum = vfredsum_vs_f64m1_f64m1(vec_zero, vec_s, vec_zero, vlmax);
  double sum = vfmv_f_s_f64m1_f64(vec_sum);

  *result_sum = sum;
  *result_count = count;
}
