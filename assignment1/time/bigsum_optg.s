	.file	"bigsum.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Result: %d\n"
.LC2:
	.string	"Took %Lf10 secs\n"
.LC3:
	.string	"Total time %Lf10 secs\n"
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
	subq	$80, %rsp
	.cfi_def_cfa_offset 112
	movq	8(%rsi), %rdi
	movl	$10, %edx
	movl	$0, %esi
	call	strtol
	movl	%eax, %r12d
	movl	$1, %esi
	leaq	32(%rsp), %rdi
	call	timespec_get
	movl	$0, %ebp
	jmp	.L2
.L8:
	movl	$1, %esi
	leaq	48(%rsp), %rdi
	call	timespec_get
	movl	%ebx, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	pxor	%xmm1, %xmm1
	cvtsi2sdq	56(%rsp), %xmm1
	movsd	.LC1(%rip), %xmm2
	movapd	%xmm1, %xmm3
	mulsd	%xmm2, %xmm3
	pxor	%xmm1, %xmm1
	cvtsi2sdq	48(%rsp), %xmm1
	addsd	%xmm3, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	72(%rsp), %xmm0
	mulsd	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdq	64(%rsp), %xmm0
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, 8(%rsp)
	fldl	8(%rsp)
	leaq	-16(%rsp), %rsp
	.cfi_def_cfa_offset 128
	fstpt	(%rsp)
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	addq	$1, %rbp
	addq	$16, %rsp
	.cfi_def_cfa_offset 112
.L2:
	movslq	%r12d, %rax
	cmpq	%rbp, %rax
	jbe	.L7
	movl	$1, %esi
	leaq	64(%rsp), %rdi
	call	timespec_get
	movl	$0, %eax
	movl	$0, %ebx
.L3:
	cmpq	$999999999, %rax
	ja	.L8
	addl	%eax, %ebx
	addq	$1, %rax
	jmp	.L3
.L7:
	movl	$1, %esi
	leaq	16(%rsp), %rdi
	call	timespec_get
	pxor	%xmm0, %xmm0
	cvtsi2sdq	24(%rsp), %xmm0
	movsd	.LC1(%rip), %xmm2
	mulsd	%xmm2, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	16(%rsp), %xmm1
	addsd	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	40(%rsp), %xmm0
	mulsd	%xmm0, %xmm2
	pxor	%xmm0, %xmm0
	cvtsi2sdq	32(%rsp), %xmm0
	addsd	%xmm2, %xmm0
	subsd	%xmm0, %xmm1
	movsd	%xmm1, 8(%rsp)
	fldl	8(%rsp)
	leaq	-16(%rsp), %rsp
	.cfi_def_cfa_offset 128
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
.LC1:
	.long	3894859413
	.long	1041313291
	.ident	"GCC: (GNU) 8.1.1 20180712 (Red Hat 8.1.1-5)"
	.section	.note.GNU-stack,"",@progbits
