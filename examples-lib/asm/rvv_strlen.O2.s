	.file	"rvv_srlen.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_c2p0_v1p0_zvamo1p0_zvlsseg1p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	strlen_vec
	.type	strlen_vec, @function
strlen_vec:
  ;; vlmax (AVL = -1)
	li	a3,-1
  ;; vlmax = vsetvl -1 e8m8
	vsetvli	a3,a3,e8,m8
  ;; copy_src = src => {a5:copy_src}
	mv	a5,a0
.L2:
  ;; vsetvl vlmax e8m8
  ;; vint8m8_t vec_str = vle8ff_v_i8m8(copy_src, &vl, vlmax) => {a4:vl, a3:vlmax}
  ;; {v8:vec_str, a4:vl}
	vsetvli	a4,a3,e8,m8
	vle8ff.v	v8,0(a5)
	csrr	a4, vl

  ;; {a2:vl}
	vsetvli	a2,a4,e8,m8
  ;; a2 = copy_str
	mv	a2,a5
  ;; vbool1_t string_terminate = vmseq_vx_i8m8_b1(vec_str, 0, vl);
  ;;    => {a4:vl, v8:vec_str, v1: string_terminate}
	vmseq.vi	v1,v8,0
  ;; copy_src += vl;
	add	a5,a5,a4
  ;; first_set_bit = vfirst_m_b1(string_terminate, vl) => {a4: first_set_bit}
	vfirst.m	a4,v1
  ;; if first_set_bit < 0 then loop {}
	blt	a4,zero,.L2
  ;; copy_src += first_set_bit;
	add	a4,a2,a4
  ;; return (copy_src - src)
	sub	a0,a4,a0
	ret
	.size	strlen_vec, .-strlen_vec
	.ident	"GCC: (GNU) 10.1.0"
