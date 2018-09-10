	.file	"bigsum.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Result: %d\n"
.LC1:
	.string	"Took %Lf10 secs\n"
.LC3:
	.string	"Total time %Lf10 secs\n"
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
	subq	$80, %rsp
	.cfi_def_cfa_offset 112
	movq	8(%rsi), %rdi
	xorl	%esi, %esi
	call	strtol
	movl	$1, %esi
	leaq	48(%rsp), %rdi
	movslq	%eax, %rbx
	call	timespec_get
.L2:
	movl	$1, %esi
	cmpq	%rbp, %rbx
	jbe	.L8
	leaq	16(%rsp), %rdi
	xorl	%r12d, %r12d
	call	timespec_get
	xorl	%eax, %eax
.L3:
	addl	%eax, %r12d
	incq	%rax
	cmpq	$1000000000, %rax
	jne	.L3
	leaq	32(%rsp), %rdi
	movl	$1, %esi
	incq	%rbp
	call	timespec_get
	movl	%r12d, %esi
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	cvtsi2sdq	40(%rsp), %xmm1
	movl	$.LC1, %edi
	xorl	%eax, %eax
	movsd	.LC2(%rip), %xmm2
	cvtsi2sdq	32(%rsp), %xmm0
	mulsd	%xmm2, %xmm1
	addsd	%xmm0, %xmm1
	cvtsi2sdq	24(%rsp), %xmm0
	mulsd	%xmm2, %xmm0
	cvtsi2sdq	16(%rsp), %xmm2
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, 8(%rsp)
	fldl	8(%rsp)
	pushq	%rdx
	.cfi_def_cfa_offset 120
	pushq	%rdx
	.cfi_def_cfa_offset 128
	fstpt	(%rsp)
	call	printf
	popq	%rcx
	.cfi_def_cfa_offset 120
	popq	%rsi
	.cfi_def_cfa_offset 112
	jmp	.L2
.L8:
	leaq	64(%rsp), %rdi
	call	timespec_get
	cvtsi2sdq	72(%rsp), %xmm1
	movl	$.LC3, %edi
	movsd	.LC2(%rip), %xmm2
	cvtsi2sdq	64(%rsp), %xmm0
	mulsd	%xmm2, %xmm1
	addsd	%xmm0, %xmm1
	cvtsi2sdq	56(%rsp), %xmm0
	mulsd	%xmm2, %xmm0
	cvtsi2sdq	48(%rsp), %xmm2
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, 8(%rsp)
	fldl	8(%rsp)
	pushq	%rax
	.cfi_def_cfa_offset 120
	pushq	%rax
	.cfi_def_cfa_offset 128
	xorl	%eax, %eax
	fstpt	(%rsp)
	call	printf
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
