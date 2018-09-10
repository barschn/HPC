	.file	"bigsum.c"
	.text
	.section	.rodata
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
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$144, %rsp
	movl	%edi, -116(%rbp)
	movq	%rsi, -128(%rbp)
	movl	$0, -4(%rbp)
	movq	-128(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol
	movl	%eax, -28(%rbp)
	leaq	-96(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	timespec_get
	movq	$0, -16(%rbp)
	jmp	.L2
.L5:
	leaq	-64(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	timespec_get
	movq	$0, -24(%rbp)
	jmp	.L3
.L4:
	movq	-24(%rbp), %rax
	movl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	addq	$1, -24(%rbp)
.L3:
	cmpq	$999999999, -24(%rbp)
	jbe	.L4
	leaq	-80(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	timespec_get
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movq	-80(%rbp), %rax
	cvtsi2sdq	%rax, %xmm1
	movq	-72(%rbp), %rax
	cvtsi2sdq	%rax, %xmm2
	movsd	.LC1(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movq	-64(%rbp), %rax
	cvtsi2sdq	%rax, %xmm2
	movq	-56(%rbp), %rax
	cvtsi2sdq	%rax, %xmm3
	movsd	.LC1(%rip), %xmm1
	mulsd	%xmm3, %xmm1
	addsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	movsd	%xmm0, -136(%rbp)
	fldl	-136(%rbp)
	fstpt	-48(%rbp)
	pushq	-40(%rbp)
	pushq	-48(%rbp)
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	addq	$16, %rsp
	movl	$0, -4(%rbp)
	addq	$1, -16(%rbp)
.L2:
	movl	-28(%rbp), %eax
	cltq
	cmpq	%rax, -16(%rbp)
	jb	.L5
	leaq	-112(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	timespec_get
	movq	-112(%rbp), %rax
	cvtsi2sdq	%rax, %xmm1
	movq	-104(%rbp), %rax
	cvtsi2sdq	%rax, %xmm2
	movsd	.LC1(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movq	-96(%rbp), %rax
	cvtsi2sdq	%rax, %xmm2
	movq	-88(%rbp), %rax
	cvtsi2sdq	%rax, %xmm3
	movsd	.LC1(%rip), %xmm1
	mulsd	%xmm3, %xmm1
	addsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	movsd	%xmm0, -136(%rbp)
	fldl	-136(%rbp)
	fstpt	-48(%rbp)
	pushq	-40(%rbp)
	pushq	-48(%rbp)
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	addq	$16, %rsp
	movl	$0, %edi
	call	exit
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC1:
	.long	3894859413
	.long	1041313291
	.ident	"GCC: (GNU) 8.1.1 20180712 (Red Hat 8.1.1-5)"
	.section	.note.GNU-stack,"",@progbits
