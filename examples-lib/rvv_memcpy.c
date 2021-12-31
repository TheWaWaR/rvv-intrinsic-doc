#include <riscv_vector.h>

void memcpy_vec(void *dst, void *src, size_t n) {
  // copy data byte by byte
  for (size_t vl; n > 0; n -= vl, src += vl, dst += vl) {
    vl = vsetvl_e8m8(n);
    vuint8m8_t vec_src = vle8_v_u8m8(src, vl);
    vse8_v_u8m8(dst, vec_src, vl);
  }
}
