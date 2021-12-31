#include <riscv_vector.h>

// reference https://github.com/riscv/riscv-v-spec/blob/master/example/strcpy.s
char *strcpy_vec(char *dst, const char *src) {
  size_t vlmax = vsetvlmax_e8m8();
  long first_set_bit = -1;
  size_t vl;
  while (first_set_bit < 0) {
    vint8m8_t vec_src = vle8ff_v_i8m8(src, &vl, vlmax);

    vbool1_t string_terminate = vmseq_vx_i8m8_b1(vec_src, 0, vl);
    vbool1_t mask = vmsif_m_b1(string_terminate, vl);

    vse8_v_i8m8_m(mask, dst, vec_src, vl);

    src += vl;
    dst += vl;

    first_set_bit = vfirst_m_b1(string_terminate, vl);
  }
  return dst;
}
