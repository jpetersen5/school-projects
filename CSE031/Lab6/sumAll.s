	.data
enter:	.asciiz "Please enter a number: "
sumE:	.asciiz "Sum of even numbers is: "
sumO:	.asciiz "Sum of odd numbers is: "
newL:	.asciiz "\n"

	.text
main:	li	$v0, 4		# set syscall code to print string
	la	$a0, enter	# set argument to string enter
	syscall			# print enter string
	li	$v0, 5		# set syscall code to read input int
	syscall			# recieve first input

loop:	beq	$v0, $zero, finish # if 0 is entered, finish program
	srl	$t2, $v0, 1	# shift bits 1 to the right
	sll	$t2, $t2, 1	# shift bits 1 to the left
	# if number is even, last bit is 0 which will not change value when
	# bit-shifted. if last bit is 1, bit-shift changes it to 0
	beq	$t2, $v0, even	# after bitshift, compare to input

odd:	add	$t1, $t1, $v0	# add to odd sum
	j main			# jump to main to restart loop with new input

even:	add	$t0, $t0, $v0	# add to even sum
	j main			# jump to main to restart loop with new input

finish:	li	$v0, 4		# set syscall code to print string
	la	$a0, sumE	# set argument to string sumE
	syscall			# print sumE string
	li	$v0, 1		# set syscall code to print int
	add	$a0, $t0, $zero # set argument to sum of evens stored at $t0
	syscall			# print sum of evens
	li	$v0, 4		# set syscall code to print string
	la	$a0, newL	# set argument to new line
	syscall			# print a new line
	la	$a0, sumO	# set argument to string sumO
	syscall			# print sumO string
	li	$v0, 1		# set syscall code to print int
	add	$a0, $t1, $zero # set argument to sum of odds stored at $t1
	syscall			# print sum of odds
	li	$v0, 10		# set syscall code to end program
	syscall			# end program