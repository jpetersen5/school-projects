.data 

orig: .space 100	# In terms of bytes (25 elements * 4 bytes each)
sorted: .space 100

str0: .asciiz "Enter the number of assignments (between 1 and 25): "
str1: .asciiz "Enter score: "
str2: .asciiz "Original scores: "
str3: .asciiz "Sorted scores (in descending order): "
str4: .asciiz "Enter the number of (lowest) scores to drop: "
str5: .asciiz "Average (rounded up) with dropped scores removed: "


.text 

# This is the main program.
# It first asks user to enter the number of assignments.
# It then asks user to input the scores, one at a time.
# It then calls selSort to perform selection sort.
# It then calls printArray twice to print out contents of the original and sorted scores.
# It then asks user to enter the number of (lowest) scores to drop.
# It then calls calcSum on the sorted array with the adjusted length (to account for dropped scores).
# It then prints out average score with the specified number of (lowest) scores dropped from the calculation.
main: 
	addi $sp, $sp -4
	sw $ra, 0($sp)
	li $v0, 4 
	la $a0, str0 
	syscall 
	li $v0, 5	# Read the number of scores from user
	syscall
	move $s0, $v0	# $s0 = numScores
	move $t0, $0
	la $s1, orig	# $s1 = orig
	la $s2, sorted	# $s2 = sorted
loop_in:
	li $v0, 4 
	la $a0, str1 
	syscall 
	sll $t1, $t0, 2
	add $t1, $t1, $s1
	li $v0, 5	# Read elements from user
	syscall
	sw $v0, 0($t1)
	addi $t0, $t0, 1
	bne $t0, $s0, loop_in
	
	move $a0, $s0
	jal selSort	# Call selSort to perform selection sort in original array
	
	li $v0, 4 
	la $a0, str2 
	syscall
	move $a0, $s1	# More efficient than la $a0, orig
	move $a1, $s0
	jal printArray	# Print original scores
	li $v0, 4 
	la $a0, str3 
	syscall 
	move $a0, $s2	# More efficient than la $a0, sorted
	jal printArray	# Print sorted scores
	
	li $v0, 4 
	la $a0, str4 
	syscall 
	li $v0, 5	# Read the number of (lowest) scores to drop
	syscall
	move $a1, $v0
	sub $a1, $s0, $a1	# numScores - drop
	move $a0, $s2
	jal calcSum	# Call calcSum to RECURSIVELY compute the sum of scores that are not dropped
	
	# Your code here to compute average and print it
	li $v0, 4
	la $a0, str5
	syscall
	div $a0, $v1, $a1
	li $v0, 1
	syscall
	
	lw $ra, 0($sp)
	addi $sp, $sp 4
	li $v0, 10 
	syscall
	
	
# printList takes in an array and its size as arguments. 
# It prints all the elements in one line with a newline at the end.
printArray:
	# Your implementation of printList here	
	move $t2, $a0
	move $t0, $0
pLoop:	sll $t1, $t0, 2		# pLoop prints lists
	add $t1, $t1, $t2
	li $v0, 1
	lw $a0, 0($t1)		# print arr[i]
	syscall
	li $v0, 11
	addi $a0, $0, 32	# space character
	syscall
	addi $t0, $t0, 1
	bne $t0, $a1, pLoop
	addi $a0, $0, 10	# LF character (new line)
	syscall
	jr $ra
	
	
# selSort takes in the number of scores as argument. 
# It performs SELECTION sort in descending order and populates the sorted array
selSort:
	# Your implementation of selSort here
	move $t0, $0
sLoop1:	sll $t1, $t0, 2		# sLoop1 fills sorted list
	add $t2, $t1, $s2	# sorted[i]
	add $t1, $t1, $s1	# orig[i]
	lw $v0, 0($t1)
	sw $v0, 0($t2)		# orig[i] = sorted[i]
	addi $t0, $t0, 1
	bne $t0, $a0, sLoop1
# sLoop2 finds max element with another loop then swaps
	move $t0, $0		# i = 0
	addi $t1, $a0, -1	# len - 1
sLoop2:	move $t2, $t0		# maxIndex = i
	addi $t3, $t0, 1	# j = i + 1
sLoop3: sll $t4, $t3, 2	
	add $t4, $t4, $s2	# sorted[j]
	lw $t5, 0($t4)
	sll $t4, $t2, 2	
	add $t4, $t4, $s2	# sorted[maxIndex]
	lw $t6, 0($t4)
	slt $t4, $t6, $t5
	beq $t4, $0, end3	# if (sorted[j] > sorted[maxIndex])
	move $t2, $t3		# maxIndex = j
end3:	addi $t3, $t3, 1	# j++
	bne $t3, $a0, sLoop3	# j < len
	sll $t3, $t2, 2	
	add $t3, $t3, $s2
	lw $t4, 0($t3)		# temp = sorted[maxIndex]
	sll $t5, $t0, 2	
	add $t5, $t5, $s2
	lw $t6, 0($t5)
	sw $t6, 0($t3)		# sorted[maxIndex] = sorted[i]
	sw $t4, 0($t5)		# sorted[i] = temp
	addi $t0, $t0, 1	# i++
	bne $t0, $t1, sLoop2	# i < len - 1
	jr $ra
	
	
# calcSum takes in an array and its size as arguments.
# It RECURSIVELY computes and returns the sum of elements in the array.
# Note: you MUST NOT use iterative approach in this function.
calcSum:
	# Your implementation of calcSum here
	addi $sp, $sp, -8	# Push stack frame for local storage
	sw $ra, 0($sp)		# store return address
	bne $a1, $0, notZero	# if len == 0
	move $v1, $0		# return 0
	j endCalc
notZero: sub $a1, $a1, 1	# len - 1
	sw $a1, 4($sp)		# store len
	jal calcSum
	lw $a1, 4($sp)
	move $t0, $a1
	sll $t1, $t0, 2	
	add $t1, $t1, $a0
	lw $v0, 0($t1)		# arr[len - 1]
	add $v1, $v1, $v0	# return = calcsum + arr[len - 1]
endCalc: addi $a1, $a1, 1	# return len to original value
	lw $ra, 0($sp)
	addi $sp, $sp, 8	# Pop stack frame
	jr $ra
	
