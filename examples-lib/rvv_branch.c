#include <riscv_vector.h>

void branch(double *a, double *b, double *c, int n, double constant) {
  // set vlmax and initialize variables
  size_t vlmax = vsetvlmax_e64m1();
  vfloat64m1_t vec_zero = vfmv_v_f_f64m1(0, vlmax);
  vfloat64m1_t vec_constant = vfmv_v_f_f64m1(constant, vlmax);
  for (size_t vl; n > 0; n -= vl, a += vl, b += vl, c += vl) {
    vl = vsetvl_e64m1(n);

    vfloat64m1_t vec_a = vle64_v_f64m1(a, vl);
    vfloat64m1_t vec_b = vle64_v_f64m1(b, vl);

    vbool64_t mask = vmfne_vv_f64m1_b64(vec_b, vec_zero, vl);

    vfloat64m1_t vec_c =
        vfdiv_vv_f64m1_m(mask, /*maskedoff=*/vec_constant, vec_a, vec_b, vl);
    vse64_v_f64m1(c, vec_c, vl);
  }
}
