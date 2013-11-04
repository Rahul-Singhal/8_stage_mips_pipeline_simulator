.data
	label1:	  .ascii "hey there dellilah"
	label2:	  .asciiz "hey there dellilahz"
	label3:	  .word 1,2,3,4,5,6,7,8,9,10
	label4:   .byte 'a', 'b', 'c' , 'd'
	label5:	  .space 40


.text
	main:
		add $t1, $t1, $t1
		add $t1, $t1, $t1

	notMain:
		add $t1, $t1, $t1
		add $t1, $t1, $t1
		beq $t2, $t3, main
		lw  $t1, 45($t3)
		lw  $t1, (label1)
		j notMain
		mult $t1, $t2 $t3
		mult $t1, $t2, 4
		lb $t1, 32($t6)
		lb $t1, ($t6)
		sb $t1, 32($t6)
		sb $t1, ($t6)



