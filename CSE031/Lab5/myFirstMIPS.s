


	.text
main:	add 	$t0, $s0, $zero	# $t0 = $s0
	subi 	$t1, $t0, 1	# $t1 = $t0 - 1
	add 	$t2, $t1, $t0	# $t2 = $t1 + $t0
	subi 	$t3, $t2, 3	# $t3 = $t2 - 3
	add 	$t4, $t3, $t2	# $t4 = $t3 + $t2
	subi 	$t5, $t4, 5	# $t5 = $t4 - 5
	add 	$t6, $t5, $t4	# $t6 = $t5 + $t4
	subi 	$t7, $t6, 7	# $t7 = $t6 - 7

finish:	li	$v0, 10		# set syscall instruction to 10 - finish program
	syscall
	
