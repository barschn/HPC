	.file	"bigsum.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Result: %d\n"
.LC1:
	.string	"Took %Lf10 secs\n"
.LC3:
	.string	"Total time %Lf10 secs\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$88, %rsp
	.cfi_def_cfa_offset 128
	movq	8(%rsi), %rdi
	movl	$10, %edx
	movl	$0, %esi
	call	strtol
	movq	%rax, %r12
	movl	$1, %esi
	leaq	32(%rsp), %rdi
	call	timespec_get
	movslq	%r12d, %r12
	testq	%r12, %r12
	je	.L2
	movl	$0, %ebp
	movl	$0, %r13d
.L4:
	movl	$1, %esi
	leaq	64(%rsp), %rdi
	call	timespec_get
	movl	$0, %edx
	movl	%r13d, %ebx
.L3:
	addl	%edx, %ebx
	addq	$1, %rdx
	cmpq	$1000000000, %rdx
	jne	.L3
	movl	$1, %esi
	leaq	48(%rsp), %rdi
	call	timespec_get
	movl	%ebx, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	pxor	%xmm1, %xmm1
	cvtsi2sdq	56(%rsp), %xmm1
	mulsd	.LC2(%rip), %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	48(%rsp), %xmm0
	addsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	72(%rsp), %xmm0
	mulsd	.LC2(%rip), %xmm0
	pxor	%xmm2, %xmm2
	cvtsi2sdq	64(%rsp), %xmm2
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, 8(%rsp)
	fldl	8(%rsp)
	leaq	-16(%rsp), %rsp
	.cfi_def_cfa_offset 144
	fstpt	(%rsp)
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	addq	$1, %rbp
	addq	$16, %rsp
	.cfi_def_cfa_offset 128
	cmpq	%r12, %rbp
	jne	.L4
.L2:
	movl	$1, %esi
	leaq	16(%rsp), %rdi
	call	timespec_get
	pxor	%xmm1, %xmm1
	cvtsi2sdq	24(%rsp), %xmm1
	movsd	.LC2(%rip), %xmm2
	mulsd	%xmm2, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	16(%rsp), %xmm0
	addsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	40(%rsp), %xmm0
	mulsd	%xmm2, %xmm0
	pxor	%xmm2, %xmm2
	cvtsi2sdq	32(%rsp), %xmm2
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, 8(%rsp)
	fldl	8(%rsp)
	leaq	-16(%rsp), %rsp
	.cfi_def_cfa_offset 144
	fstpt	(%rsp)
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
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
