
	main:
	
	add $t4 , $t2 , 2   #add with immediate
	addi $t1 , $t2 , 789
	and $t1 , $t2 , $t3
	andi $t1 , $t2 , 6
	or $t1 , $t2 , $t3
	ori $t1 , $t2 , 8
	xor $t1 , $t2 , $t3
	xori $t1 , $t2 , 10
	yo :
	la $v0,5
	li $ra, 8
	not $s1, $s2

	there:
	syscall
	move $t4, $t7


	
	