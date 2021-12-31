	.file	"rvv_strcmp.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_c2p0_v1p0_zvamo1p0_zvlsseg1p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	strcmp_vec
	.type	strcmp_vec, @function
strcmp_vec:
	li	a4,-1
	vsetvli	a4,a4,e8,m2
.L2:
	vsetvli	a5,a4,e8,m2
	vle8ff.v	v2,0(a0)
	csrr	a5, vl
	vsetvli	a3,a4,e8,m2
	vle8ff.v	v6,0(a1)
	csrr	a3, vl
	vsetvli	a3,a5,e8,m2
	vmseq.vi	v1,v2,0
	vsetvli	a3,a5,e8,m2
	mv	a2,a0
	mv	a3,a1
	add	a0,a0,a5
	add	a1,a1,a5
	vmsne.vv	v4,v2,v6
	vmor.mm	v1,v1,v4
	vfirst.m	a5,v1
	blt	a5,zero,.L2
	add	a2,a2,a5
	add	a5,a3,a5
	lbu	a0,0(a2)
	lbu	a5,0(a5)
	subw	a0,a0,a5
	ret
	.size	strcmp_vec, .-strcmp_vec
	.ident	"GCC: (GNU) 10.1.0"
