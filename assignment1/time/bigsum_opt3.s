	.file	"bigsum.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Result: %ld\n"
.LC1:
	.string	"Took %Lf10 secs\n"
.LC3:
	.string	"Total time %Lf10 secs\n"
.LC4:
	.string	"Average time %Lf10 secs\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	$10, %edx
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$96, %rsp
	.cfi_def_cfa_offset 128
	movq	8(%rsi), %rdi
	xorl	%esi, %esi
	call	strtol
	movl	$1, %esi
	leaq	64(%rsp), %rdi
	movq	%rax, %rbp
	movl	%eax, 28(%rsp)
	call	timespec_get
	movslq	%ebp, %rbp
	testq	%rbp, %rbp
	je	.L10
	movsd	.LC2(%rip), %xmm6
	xorl	%ebx, %ebx
	movabsq	$499999999500000000, %r12
	movsd	%xmm6, 16(%rsp)
.L3:
	leaq	32(%rsp), %rdi
	movl	$1, %esi
	addq	$1, %rbx
	call	timespec_get
	leaq	48(%rsp), %rdi
	movl	$1, %esi
	call	timespec_get
	movq	%r12, %rsi
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	pxor	%xmm1, %xmm1
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	cvtsi2sdq	56(%rsp), %xmm1
	movsd	16(%rsp), %xmm3
	pxor	%xmm2, %xmm2
	subq	$16, %rsp
	.cfi_def_cfa_offset 144
	cvtsi2sdq	64(%rsp), %xmm0
	movl	$.LC1, %edi
	cvtsi2sdq	48(%rsp), %xmm2
	mulsd	%xmm3, %xmm1
	addsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	56(%rsp), %xmm0
	mulsd	%xmm3, %xmm0
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, 16(%rsp)
	fldl	16(%rsp)
	fstpt	(%rsp)
	call	printf
	popq	%rax
	.cfi_def_cfa_offset 136
	popq	%rdx
	.cfi_def_cfa_offset 128
	cmpq	%rbx, %rbp
	jne	.L3
.L2:
	movl	$1, %esi
	leaq	80(%rsp), %rdi
	call	timespec_get
	pxor	%xmm1, %xmm1
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	cvtsi2sdq	88(%rsp), %xmm1
	movsd	16(%rsp), %xmm4
	pxor	%xmm2, %xmm2
	subq	$16, %rsp
	.cfi_def_cfa_offset 144
	cvtsi2sdq	96(%rsp), %xmm0
	movl	$.LC3, %edi
	cvtsi2sdq	80(%rsp), %xmm2
	mulsd	%xmm4, %xmm1
	addsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	88(%rsp), %xmm0
	mulsd	%xmm4, %xmm0
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, 16(%rsp)
	fldl	16(%rsp)
	fld	%st(0)
	fstpt	(%rsp)
	fstpt	16(%rsp)
	call	printf
	fildl	44(%rsp)
	movl	$.LC4, %edi
	xorl	%eax, %eax
	subq	$16, %rsp
	.cfi_def_cfa_offset 160
	fldt	32(%rsp)
	fdivp	%st, %st(1)
	fstpt	(%rsp)
	call	printf
	addq	$32, %rsp
	.cfi_def_cfa_offset 128
	xorl	%edi, %edi
	call	exit
.L10:
	movsd	.LC2(%rip), %xmm5
	movsd	%xmm5, 16(%rsp)
	jmp	.L2
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	3894859413
	.long	1041313291
	.ident	"GCC: (GNU) 8.1.1 20180712 (Red Hat 8.1.1-5)"
	.section	.note.GNU-stack,"",@progbits
