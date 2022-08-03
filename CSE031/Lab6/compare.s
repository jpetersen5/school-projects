	.data
n:	.word 25
str1: .asciiz "Less than\n"
str2: .asciiz "Less than or equal to\n"
str3: .asciiz "Greater than\n"
str4: .asciiz "Greater than or equal to\n"

	.text
main:	li	$v0, 5		# set syscall code to read int input
	syscall			# read int input
	la	$t0, n
	lw	$t0, ($t0)	# load value stored at n to $t0
#	slt	$t1, $v0, $t0	# compare if input int (at $v0) is less than n (at $t0)
	slt	$t1, $t0, $v0	# compare if n (at $t0) is less than input int (at $v0)
	li	$v0, 4		# set syscall code to print string (placed here to save on redundancy)
#	bne	$t1, $zero, lesser # if true, branch to "lesser"
	bne	$t1, $zero, greater # if true, branch to "greater"

#greater: la	$a0, str4	# load str4 to argument
#	syscall			# print str4
#	j finish		# go to end of program

#lesser: la	$a0, str1	# load str1 to argument
#	syscall			# print str1

lesser: la	$a0, str2	# load str2 to argument
	syscall			# print str2
	j finish		# go to end of program

greater: la	$a0, str3	# load str3 to argument
	syscall			# print str3

finish: li	$v0, 10		# set syscall code to end program
	syscall			# end program