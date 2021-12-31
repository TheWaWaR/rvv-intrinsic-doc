#include <riscv_vector.h>

// reference https://github.com/riscv/riscv-v-spec/blob/master/example/strcmp.s
int strcmp_vec(const char *src1, const char *src2) {
  size_t vlmax = vsetvlmax_e8m2();
  long first_set_bit = -1;
  size_t vl, vl1;
  while (first_set_bit < 0) {
    vint8m2_t vec_src1 = vle8ff_v_i8m2(src1, &vl, vlmax);
    vint8m2_t vec_src2 = vle8ff_v_i8m2(src2, &vl1, vlmax);

    vbool4_t string_terminate = vmseq_vx_i8m2_b4(vec_src1, 0, vl);
    vbool4_t no_equal = vmsne_vv_i8m2_b4(vec_src1, vec_src2, vl);
    vbool4_t vec_terminate = vmor_mm_b4(string_terminate, no_equal, vl);

    first_set_bit = vfirst_m_b4(vec_terminate, vl);
    src1 += vl;
    src2 += vl;
  }
  src1 -= vl - first_set_bit;
  src2 -= vl - first_set_bit;
  return *src1 - *src2;
}
