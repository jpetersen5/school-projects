        .data
enter:	.asciiz "Please enter an integer: "

        .text
main: 	addi 	$sp, $sp, -4	# Moving stack pointer to make room for storing local variables (push the stack frame)
	li	$v0, 4		# set syscall code to print string
	la	$a0, enter	# set argument to string enter
	syscall			# print enter string
	li	$v0, 5		# set syscall code to read input int
	syscall			# recieve first input
	add 	$a0, $zero, $v0 # set recursion argument to input int
	jal 	recursion	# Call recursion(x)
	
	add 	$a0, $zero, $v0	# set print arg to return value
	li 	$v0, 1		# set syscall arg to print int
	syscall
	j 	end		# Jump to end of program

# Implementing recursion
recursion: addi	$sp, $sp, -12	# Push stack frame for local storage
	sw $ra, 0($sp)		# store return address
	subi 	$t0, $a0, 10	# temp sub 10 to check if (m == 10)
	bne 	$t0, $zero, not_ten
	addi	$v0, $zero, 2	# m == 10, return 2
	j 	end_recur
			
not_ten: subi	$t0, $t0, 1	# temp sub another 1 to check if (m == 11)
	bne 	$t0, $zero, not_eleven
	addi	$v0, $zero, 1	# m == 11, return 1
	j 	end_recur		

not_eleven: sw 	$a0, 4($sp)	# store original argument to stack
	addi	$a0, $a0, 2
	jal 	recursion	# Call recursion(m + 2)
	sw	$v0, 8($sp)	# store return from recursion call
	lw	$a0, 4($sp)	# load original argument from stack
	addi	$a0, $a0, 1
	jal 	recursion	# Call recursion(m + 1)
	lw	$t1, 8($sp)	# load first recursion call return
	lw	$a0, 4($sp)	# load m
	add	$v0, $v0, $t1	# return = recursion(m + 2) + recursion(m + 1)
	add	$v0, $v0, $a0	# return = return + m
	j 	end_recur

# End of recursion function	
end_recur:
	lw	$ra, 0($sp)
	addi 	$sp, $sp, 12	# Pop stack frame 
	jr 	$ra

# Terminating the program
end:	addi 	$sp, $sp 4	# Moving stack pointer back (pop the stack frame)
	li 	$v0, 10 
	syscall