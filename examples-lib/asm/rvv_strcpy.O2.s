	.file	"rvv_strcpy.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_c2p0_v1p0_zvamo1p0_zvlsseg1p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	strcpy_vec
	.type	strcpy_vec, @function
strcpy_vec:
	li	a4,-1
	vsetvli	a4,a4,e8,m8
.L2:
	vsetvli	a5,a4,e8,m8
	vle8ff.v	v8,0(a1)
	csrr	a5, vl
	vsetvli	a3,a5,e8,m8
	vmseq.vi	v1,v8,0
	vmsif.m	v0,v1
	vsetvli	a3,a5,e8,m8
	vse8.v	v8,0(a0),v0.t
	add	a1,a1,a5
	add	a0,a0,a5
	vfirst.m	a5,v1
	blt	a5,zero,.L2
	ret
	.size	strcpy_vec, .-strcpy_vec
	.ident	"GCC: (GNU) 10.1.0"
