	.text

/* Switch from current_thread to next_thread. Make next_thread
 * the current_thread, and set next_thread to 0.
 * Use eax as a temporary register; it is caller saved.
 */
	.globl thread_switch
thread_switch:
	/* YOUR CODE HERE */
	// 保存当前线程状态至 current_thread
	pushal

	// 保存当前线程的 esp。esp 保存的，就是在调用 thread_switch 时，压入的下一条需要执行的指令地址(eip)
	movl current_thread, %eax
	movl %esp, (%eax)

	// 使 current_thread 指向 next_thread
	movl next_thread, %eax
	movl %eax, current_thread
	
	// 恢复 next_thread (经过上面换完，就是 current_thread 了) 的状态
	movl current_thread, %eax
	movl (%eax), %esp
	popal

	movl $0x0, next_thread
	ret				/* pop return address from stack */
