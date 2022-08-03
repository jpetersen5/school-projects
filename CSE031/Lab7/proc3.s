# PROGRAM INFO
# Sets 3 initial variables, x y and z
# z = x + y + z + FOO(x,y,z)
#	FOO(m,n,o) = bar(m+n,n+o,o+m) + bar(m-o,n-m,2*n)
#		bar(a,b,c) = (c-a<<b)
# TOTAL: z = x + y + z + ((z+x) - (x+y) << (y+z)) + ((2*x) - (x-z) << (y-x))
# Registers: x -> $s0, y -> $s1, z -> $s2

		.data
x:		.word 2
y:		.word 3
z:		.word 4

		.text
MAIN: 		la 	$t0, x
		lw 	$s0, 0($t0)	# s0 = x
		la 	$t0, y
		lw 	$s1, 0($t0)	# s1 = y
		la 	$t0, z
		lw 	$s2, 0($t0)	# s2 = z
		# prepare to call FOO
		add 	$a0, $zero, $s0	# foo arg 1 m
		add 	$a1, $zero, $s1	# foo arg 2 n
		add 	$a2, $zero, $s2	# foo arg 3 o
		jal 	FOO
		# z = x + y + z + foo(x, y, z)
		add 	$s2, $s2, $s0	# z = z + x
		add 	$s2, $s2, $s1	# z = z + y
		add 	$s2, $s2, $v0	# z = z + foo result
		# print results
		addi 	$a0, $s2, 0 	# set print arg to z
		li 	$v0, 1
		syscall
		j 	END


FOO:		addi 	$sp, $sp -4	# backup return address
		sw 	$ra, 0($sp)
		# setup for calling bar(m + n, n + o, o + m)
		addi 	$sp, $sp -4	# backup x
		sw 	$s0, 0($sp)
		add 	$t0, $a0, $a1	# bar arg 1 = m + n
		add 	$t1, $a1, $a2	# bar arg 2 = n + o
		add 	$t2, $a2, $a0	# bar arg 3 = o + m
		addi 	$sp, $sp -4	# backup foo arg 1
		sw 	$a0, 0($sp)
		addi 	$sp, $sp -4	# backup foo arg 2
		sw 	$a1, 0($sp)
		addi 	$sp, $sp -4	# backup foo arg 3
		sw 	$a2, 0($sp)
		add 	$a0, $zero, $t0	# set bar arg 1 a
		add 	$a1, $zero, $t1	# set bar arg 2 b
		add 	$a2, $zero, $t2	# set bar arg 3 c
		jal 	BAR
		add 	$s0, $zero, $v0	# p = bar(m + n, n + o, o + m)
		lw 	$a2, 0($sp)	# restore foo arg 3
		addi 	$sp, $sp 4
		lw 	$a1, 0($sp)	# restore foo arg 2
		addi 	$sp, $sp 4
		lw 	$a0, 0($sp)	# restore foo arg 1
		addi 	$sp, $sp 4
		# setup for calling bar(m - o, n - m, 2 * n)
		addi 	$sp, $sp -4	# backup y
		sw 	$s1, 0($sp)
		sub 	$t0, $a0, $a2	# bar arg 1 = m - o
		sub 	$t1, $a1, $a0	# bar arg 2 = n - m
		mul 	$t2, $a1, 2	# bar arg 3 = 2 * n
		addi 	$sp, $sp -4	# backup foo arg 1
		sw 	$a0, 0($sp)
		addi 	$sp, $sp -4	# backup foo arg 2
		sw 	$a1, 0($sp)
		addi 	$sp, $sp -4	# backup foo arg 3
		sw	$a2, 0($sp)
		add 	$a0, $zero, $t0	# set bar arg 1 a
		add 	$a1, $zero, $t1	# set bar arg 2 b
		add 	$a2, $zero, $t2	# set bar arg 3 c
		jal 	BAR
		add 	$s1, $zero, $v0	# q = bar(m - o, n - m, 2 * n)
		lw 	$a2, 0($sp)	# restore foo arg 3
		addi 	$sp, $sp 4
		lw 	$a1, 0($sp)	# restore foo arg 2
		addi 	$sp, $sp 4
		lw 	$a0, 0($sp)	# restore foo arg 1
		addi 	$sp, $sp 4
		# restore and return
		add 	$v0, $s0, $s1	# return value = p + q
		lw 	$s1, 0($sp)	# restore y
		addi 	$sp, $sp 4
		lw 	$s0, 0($sp)	# restore x
		addi 	$sp, $sp 4
		lw 	$ra, 0($sp)	# restore return address
		addi 	$sp, $sp 4
		jr 	$ra


BAR:		sub 	$v0, $a2, $a0	# c - a
		sllv 	$v0, $v0, $a1	# bitshift c - a left by b bits
		jr 	$ra


END:		li	$v0, 10
		syscall			# end program
