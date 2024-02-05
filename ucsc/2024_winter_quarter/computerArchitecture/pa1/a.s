	.file	"a.c"
	.option pic
	.text
	.align	1
	.globl	array_total
	.type	array_total, @function
array_total:
	addi	sp,sp,-48
	sd	s0,40(sp)
	addi	s0,sp,48
	sd	a0,-40(s0)
	sd	a1,-48(s0)
	sd	zero,-32(s0)
	sd	zero,-24(s0)
	j	.L2
.L3:
	ld	a5,-24(s0)
	slli	a5,a5,3
	ld	a4,-40(s0)
	add	a5,a4,a5
	ld	a5,0(a5)
	ld	a4,-32(s0)
	add	a5,a4,a5
	sd	a5,-32(s0)
	ld	a5,-24(s0)
	addi	a5,a5,1
	sd	a5,-24(s0)
.L2:
	ld	a4,-24(s0)
	ld	a5,-48(s0)
	blt	a4,a5,.L3
	ld	a5,-32(s0)
	mv	a0,a5
	ld	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	array_total, .-array_total
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
