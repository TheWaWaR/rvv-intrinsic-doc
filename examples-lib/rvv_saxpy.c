#include <riscv_vector.h>

// reference https://github.com/riscv/riscv-v-spec/blob/master/example/saxpy.s
void saxpy_vec(size_t n, const float a, const float *x, float *y) {
  size_t l;

  vfloat32m8_t vx, vy;

  for (; n > 0; n -= l) {
    l = vsetvl_e32m8(n);
    vx = vle32_v_f32m8(x, l);
    x += l;
    vy = vle32_v_f32m8(y, l);
    vy = vfmacc_vf_f32m8(vy, a, vx, l);
    vse32_v_f32m8 (y, vy, l);
    y += l;
  }
}
