	.file	"rvv_strncpy.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_c2p0_v1p0_zvamo1p0_zvlsseg1p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	strncpy_vec
	.type	strncpy_vec, @function
strncpy_vec:
	beq	a2,zero,.L1
.L10:
	vsetvli	a5,a2,e8,m1
	vsetvli	a5,a5,e8,m1
	vle8ff.v	v2,0(a1)
	csrr	a5, vl
	vsetvli	a4,a5,e8,m1
	vmseq.vi	v1,v2,0
	vmsif.m	v0,v1
	vsetvli	a4,a5,e8,m1
	vse8.v	v2,0(a0),v0.t
	sub	a3,a2,a5
	add	a4,a0,a5
	add	a1,a1,a5
	vfirst.m	a5,v1
	bge	a5,zero,.L9
	mv	a2,a3
	mv	a0,a4
	bne	a2,zero,.L10
.L1:
	ret
.L9:
	sub	a2,a2,a5
	add	a0,a0,a5
	li	a5,-1
	vsetvli	a5,a5,e8,m1
	vsetvli	a5,a5,e8,m1
	vmv.v.i	v1,0
.L4:
	vsetvli	a5,a2,e8,m1
	vsetvli	a4,a5,e8,m1
	vse8.v	v1,0(a0)
	sub	a2,a2,a5
	add	a0,a0,a5
	bne	a2,zero,.L4
	ret
	.size	strncpy_vec, .-strncpy_vec
	.ident	"GCC: (GNU) 10.1.0"
