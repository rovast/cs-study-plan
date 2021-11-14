
combine.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <vec_length>:
   0:	48 8b 07             	mov    (%rdi),%rax
   3:	c3                   	retq   

0000000000000004 <get_vec_element>:
   4:	48 85 f6             	test   %rsi,%rsi
   7:	78 16                	js     1f <get_vec_element+0x1b>
   9:	48 39 37             	cmp    %rsi,(%rdi)
   c:	7e 17                	jle    25 <get_vec_element+0x21>
   e:	48 8b 47 08          	mov    0x8(%rdi),%rax
  12:	48 8b 04 f0          	mov    (%rax,%rsi,8),%rax
  16:	48 89 02             	mov    %rax,(%rdx)
  19:	b8 01 00 00 00       	mov    $0x1,%eax
  1e:	c3                   	retq   
  1f:	b8 00 00 00 00       	mov    $0x0,%eax
  24:	c3                   	retq   
  25:	b8 00 00 00 00       	mov    $0x0,%eax
  2a:	c3                   	retq   

000000000000002b <combine1>:
  2b:	41 54                	push   %r12
  2d:	55                   	push   %rbp
  2e:	53                   	push   %rbx
  2f:	48 83 ec 10          	sub    $0x10,%rsp
  33:	49 89 fc             	mov    %rdi,%r12
  36:	48 89 f5             	mov    %rsi,%rbp
  39:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  40:	00 00 
  42:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  47:	31 c0                	xor    %eax,%eax
  49:	48 c7 06 00 00 00 00 	movq   $0x0,(%rsi)
  50:	bb 00 00 00 00       	mov    $0x0,%ebx
  55:	eb 1a                	jmp    71 <combine1+0x46>
  57:	48 89 e2             	mov    %rsp,%rdx
  5a:	48 89 de             	mov    %rbx,%rsi
  5d:	4c 89 e7             	mov    %r12,%rdi
  60:	e8 00 00 00 00       	callq  65 <combine1+0x3a>
  65:	48 8b 04 24          	mov    (%rsp),%rax
  69:	48 01 45 00          	add    %rax,0x0(%rbp)
  6d:	48 83 c3 01          	add    $0x1,%rbx
  71:	4c 89 e7             	mov    %r12,%rdi
  74:	e8 00 00 00 00       	callq  79 <combine1+0x4e>
  79:	48 39 d8             	cmp    %rbx,%rax
  7c:	7f d9                	jg     57 <combine1+0x2c>
  7e:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  83:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  8a:	00 00 
  8c:	75 09                	jne    97 <combine1+0x6c>
  8e:	48 83 c4 10          	add    $0x10,%rsp
  92:	5b                   	pop    %rbx
  93:	5d                   	pop    %rbp
  94:	41 5c                	pop    %r12
  96:	c3                   	retq   
  97:	e8 00 00 00 00       	callq  9c <combine2>

000000000000009c <combine2>:
  9c:	41 55                	push   %r13
  9e:	41 54                	push   %r12
  a0:	55                   	push   %rbp
  a1:	53                   	push   %rbx
  a2:	48 83 ec 18          	sub    $0x18,%rsp
  a6:	49 89 fd             	mov    %rdi,%r13
  a9:	48 89 f5             	mov    %rsi,%rbp
  ac:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  b3:	00 00 
  b5:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  ba:	31 c0                	xor    %eax,%eax
  bc:	e8 00 00 00 00       	callq  c1 <combine2+0x25>
  c1:	49 89 c4             	mov    %rax,%r12
  c4:	48 c7 45 00 00 00 00 	movq   $0x0,0x0(%rbp)
  cb:	00 
  cc:	bb 00 00 00 00       	mov    $0x0,%ebx
  d1:	eb 1a                	jmp    ed <combine2+0x51>
  d3:	48 89 e2             	mov    %rsp,%rdx
  d6:	48 89 de             	mov    %rbx,%rsi
  d9:	4c 89 ef             	mov    %r13,%rdi
  dc:	e8 00 00 00 00       	callq  e1 <combine2+0x45>
  e1:	48 8b 04 24          	mov    (%rsp),%rax
  e5:	48 01 45 00          	add    %rax,0x0(%rbp)
  e9:	48 83 c3 01          	add    $0x1,%rbx
  ed:	4c 39 e3             	cmp    %r12,%rbx
  f0:	7c e1                	jl     d3 <combine2+0x37>
  f2:	48 8b 44 24 08       	mov    0x8(%rsp),%rax
  f7:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  fe:	00 00 
 100:	75 0b                	jne    10d <combine2+0x71>
 102:	48 83 c4 18          	add    $0x18,%rsp
 106:	5b                   	pop    %rbx
 107:	5d                   	pop    %rbp
 108:	41 5c                	pop    %r12
 10a:	41 5d                	pop    %r13
 10c:	c3                   	retq   
 10d:	e8 00 00 00 00       	callq  112 <combine2+0x76>
