		.data
x:		.word 5
y:		.word 10
m:		.word 15
b:		.word 2

		.text
MAIN:	la $t0, x
		lw $s0, 0($t0)		# s0 = x
		la $t0, y
		lw $s1, 0($t0)		# s1 = y
		
		# Prepare to call sum(x)
		add $a0, $zero, $s0	# Set a0 as input argument for SUM
		jal SUM
		add $t0, $s1, $s0
		add $s1, $t0, $v0
		addi $a0, $s1, 0 
		li $v0, 1		 
		syscall	
		j END

		
SUM: 	la $t0, m
		addi $sp, $sp -4
		sw $s0, 0($sp)		# backup s0 from MAIN
		lw $s0, 0($t0)		# s0 = m
		addi $sp, $sp -4
		sw $a0, 0($sp)		# backup a0 from MAIN
		add $a0, $s0, $a0	# Update a0 as new argument for SUB
		addi $sp, $sp -4
		sw $ra, 0($sp)		# backup return address for SUM
		jal SUB
		lw $ra, 0($sp)		# restore return address for MAIN
		addi $sp, $sp 4
		lw $a0, 0($sp)		# restore a0 from MAIN
		addi $sp, $sp 4
		add $v0, $a0, $v0
		lw $s0, 0($sp)		# restore s0 from MAIN
		addi $sp, $sp 4
		jr $ra		
		
SUB:	la $t0, b
		addi $sp, $sp -4
		sw $s0, 0($sp)		# Backup s0 from SUM
		lw $s0, 0($t0)		# s0 = b
		sub $v0, $a0, $s0
		lw $s0, 0($sp)		# Restore s0 from SUM
		addi $sp, $sp 4
		jr $ra

		
END:
