	.file	"bigsum.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Result: %ld\n"
.LC1:
	.string	"Took %.15Lf secs\n"
.LC3:
	.string	"Total time %.15Lf secs\n"
.LC4:
	.string	"Average time %.15Lf secs\n"
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB5:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	$10, %edx
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	xorl	%ebp, %ebp
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
	movslq	%eax, %r12
	call	timespec_get
	movq	%r12, %rbx
.L2:
	movl	$1, %esi
	cmpq	%rbp, %r12
	jbe	.L6
	leaq	32(%rsp), %rdi
	incq	%rbp
	call	timespec_get
	leaq	48(%rsp), %rdi
	movl	$1, %esi
	call	timespec_get
	movl	$.LC0, %edi
	xorl	%eax, %eax
	movabsq	$499999999500000000, %rsi
	call	printf
	cvtsi2sdq	56(%rsp), %xmm1
	movl	$.LC1, %edi
	xorl	%eax, %eax
	mulsd	.LC2(%rip), %xmm1
	cvtsi2sdq	48(%rsp), %xmm0
	cvtsi2sdq	32(%rsp), %xmm2
	addsd	%xmm0, %xmm1
	cvtsi2sdq	40(%rsp), %xmm0
	mulsd	.LC2(%rip), %xmm0
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, 8(%rsp)
	fldl	8(%rsp)
	pushq	%rcx
	.cfi_def_cfa_offset 136
	pushq	%rcx
	.cfi_def_cfa_offset 144
	fstpt	(%rsp)
	call	printf
	popq	%rsi
	.cfi_def_cfa_offset 136
	popq	%rdi
	.cfi_def_cfa_offset 128
	jmp	.L2
.L6:
	leaq	80(%rsp), %rdi
	call	timespec_get
	cvtsi2sdq	88(%rsp), %xmm1
	movl	$.LC3, %edi
	mulsd	.LC2(%rip), %xmm1
	cvtsi2sdq	80(%rsp), %xmm0
	cvtsi2sdq	64(%rsp), %xmm2
	addsd	%xmm0, %xmm1
	cvtsi2sdq	72(%rsp), %xmm0
	mulsd	.LC2(%rip), %xmm0
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, 8(%rsp)
	fldl	8(%rsp)
	pushq	%rax
	.cfi_def_cfa_offset 136
	pushq	%rax
	.cfi_def_cfa_offset 144
	xorl	%eax, %eax
	fld	%st(0)
	fstpt	(%rsp)
	fstpt	32(%rsp)
	call	printf
	fldt	32(%rsp)
	movl	$.LC4, %edi
	xorl	%eax, %eax
	movl	%ebx, 24(%rsp)
	fidivl	24(%rsp)
	pushq	%rdx
	.cfi_def_cfa_offset 152
	pushq	%rdx
	.cfi_def_cfa_offset 160
	fstpt	(%rsp)
	call	printf
	addq	$32, %rsp
	.cfi_def_cfa_offset 128
	xorl	%edi, %edi
	call	exit
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	3894859413
	.long	1041313291
	.ident	"GCC: (GNU) 8.1.1 20180712 (Red Hat 8.1.1-5)"
	.section	.note.GNU-stack,"",@progbits
