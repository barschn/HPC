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
	.text
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$96, %rsp
	.cfi_def_cfa_offset 128
	movq	8(%rsi), %rdi
	movl	$10, %edx
	movl	$0, %esi
	call	strtol
	movq	%rax, %rbp
	movl	%eax, 28(%rsp)
	movl	$1, %esi
	leaq	48(%rsp), %rdi
	call	timespec_get
	movslq	%ebp, %rbp
	testq	%rbp, %rbp
	je	.L2
	movl	$0, %ebx
	movabsq	$499999999500000000, %r12
.L4:
	movl	$1, %esi
	leaq	80(%rsp), %rdi
	call	timespec_get
	movl	$1000000000, %edx
.L3:
	subq	$1, %rdx
	jne	.L3
	movl	$1, %esi
	leaq	64(%rsp), %rdi
	call	timespec_get
	movq	%r12, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	pxor	%xmm1, %xmm1
	cvtsi2sdq	72(%rsp), %xmm1
	mulsd	.LC2(%rip), %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	64(%rsp), %xmm0
	addsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	88(%rsp), %xmm0
	mulsd	.LC2(%rip), %xmm0
	pxor	%xmm2, %xmm2
	cvtsi2sdq	80(%rsp), %xmm2
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, (%rsp)
	fldl	(%rsp)
	leaq	-16(%rsp), %rsp
	.cfi_def_cfa_offset 144
	fstpt	(%rsp)
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	addq	$1, %rbx
	addq	$16, %rsp
	.cfi_def_cfa_offset 128
	cmpq	%rbp, %rbx
	jne	.L4
.L2:
	movl	$1, %esi
	leaq	32(%rsp), %rdi
	call	timespec_get
	pxor	%xmm1, %xmm1
	cvtsi2sdq	40(%rsp), %xmm1
	movsd	.LC2(%rip), %xmm2
	mulsd	%xmm2, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	32(%rsp), %xmm0
	addsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	56(%rsp), %xmm0
	mulsd	%xmm2, %xmm0
	pxor	%xmm2, %xmm2
	cvtsi2sdq	48(%rsp), %xmm2
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, (%rsp)
	fldl	(%rsp)
	fld	%st(0)
	fstpt	(%rsp)
	leaq	-16(%rsp), %rsp
	.cfi_def_cfa_offset 144
	fstpt	(%rsp)
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	fildl	44(%rsp)
	fldt	16(%rsp)
	fdivp	%st, %st(1)
	leaq	-16(%rsp), %rsp
	.cfi_def_cfa_offset 160
	fstpt	(%rsp)
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	addq	$32, %rsp
	.cfi_def_cfa_offset 128
	movl	$0, %edi
	call	exit
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
