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
	subq	$80, %rsp
	.cfi_def_cfa_offset 112
	movq	8(%rsi), %rdi
	xorl	%esi, %esi
	call	strtol
	movl	$1, %esi
	leaq	48(%rsp), %rdi
	movq	%rax, %r12
	call	timespec_get
	movslq	%r12d, %r12
	testq	%r12, %r12
	je	.L12
	movsd	.LC2(%rip), %xmm6
	xorl	%ebp, %ebp
	movsd	%xmm6, 8(%rsp)
.L4:
	movl	$1, %esi
	leaq	16(%rsp), %rdi
	xorl	%ebx, %ebx
	call	timespec_get
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L3:
	addl	%edx, %ebx
	addq	$1, %rdx
	cmpq	$1000000000, %rdx
	jne	.L3
	leaq	32(%rsp), %rdi
	movl	$1, %esi
	addq	$1, %rbp
	call	timespec_get
	movl	%ebx, %esi
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	printf
	pxor	%xmm1, %xmm1
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	cvtsi2sdq	40(%rsp), %xmm1
	movsd	8(%rsp), %xmm3
	pxor	%xmm2, %xmm2
	subq	$16, %rsp
	.cfi_def_cfa_offset 128
	cvtsi2sdq	48(%rsp), %xmm0
	movl	$.LC1, %edi
	cvtsi2sdq	32(%rsp), %xmm2
	mulsd	%xmm3, %xmm1
	addsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	40(%rsp), %xmm0
	mulsd	%xmm3, %xmm0
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, 16(%rsp)
	fldl	16(%rsp)
	fstpt	(%rsp)
	call	printf
	popq	%rax
	.cfi_def_cfa_offset 120
	popq	%rdx
	.cfi_def_cfa_offset 112
	cmpq	%rbp, %r12
	jne	.L4
.L2:
	leaq	64(%rsp), %rdi
	movl	$1, %esi
	call	timespec_get
	pxor	%xmm1, %xmm1
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	cvtsi2sdq	72(%rsp), %xmm1
	movsd	8(%rsp), %xmm4
	pxor	%xmm2, %xmm2
	subq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 128
	cvtsi2sdq	80(%rsp), %xmm0
	movl	$.LC3, %edi
	cvtsi2sdq	64(%rsp), %xmm2
	mulsd	%xmm4, %xmm1
	addsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	72(%rsp), %xmm0
	mulsd	%xmm4, %xmm0
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, 16(%rsp)
	fldl	16(%rsp)
	fstpt	(%rsp)
	call	printf
	xorl	%edi, %edi
	call	exit
.L12:
	.cfi_restore_state
	movsd	.LC2(%rip), %xmm5
	movsd	%xmm5, 8(%rsp)
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
