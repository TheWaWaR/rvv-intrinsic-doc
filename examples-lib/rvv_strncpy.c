#include <riscv_vector.h>

// reference https://github.com/riscv/riscv-v-spec/blob/master/example/strncpy.s
char *strncpy_vec(char *dst, char *src, size_t count) {
  size_t new_vl;
  long first_set_bit = -1;

  while (first_set_bit < 0) {
    if (count == 0)
      return dst;
    size_t vl = vsetvl_e8m1(count);

    vint8m1_t vec_src = vle8ff_v_i8m1(src, &new_vl, vl);

    vbool8_t string_terminate = vmseq_vx_i8m1_b8(vec_src, 0, new_vl);
    vbool8_t mask = vmsif_m_b8(string_terminate, new_vl);

    vse8_v_i8m1_m(mask, dst, vec_src, new_vl);

    count -= new_vl;
    src += new_vl;
    dst += new_vl;

    first_set_bit = vfirst_m_b8(string_terminate, new_vl);
  }

  size_t tail = new_vl - first_set_bit;
  count += tail;
  dst -= tail;
  size_t vlmax = vsetvlmax_e8m1();
  vint8m1_t vec_zero = vmv_v_x_i8m1(0, vlmax);
  do {
    size_t vl = vsetvl_e8m1(count);
    vse8_v_i8m1(dst, vec_zero, vl);
    count -= vl;
    dst += vl;
  } while (count > 0);

  return dst;
}
