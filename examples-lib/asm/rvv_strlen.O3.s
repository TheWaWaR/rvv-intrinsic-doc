	.file	"rvv_strlen.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_c2p0_v1p0_zvamo1p0_zvlsseg1p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	strlen_vec
	.type	strlen_vec, @function
strlen_vec:
	li	a3,-1
	vsetvli	a3,a3,e8,m8
	mv	a5,a0
.L2:
	vsetvli	a4,a3,e8,m8
	vle8ff.v	v8,0(a5)
	csrr	a4, vl
	vsetvli	a2,a4,e8,m8
	mv	a2,a5
	vmseq.vi	v1,v8,0
	add	a5,a5,a4
	vfirst.m	a4,v1
	blt	a4,zero,.L2
	add	a4,a2,a4
	sub	a0,a4,a0
	ret
	.size	strlen_vec, .-strlen_vec
	.ident	"GCC: (GNU) 10.1.0"
