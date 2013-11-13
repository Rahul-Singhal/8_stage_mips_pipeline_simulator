.data
##checked for correct parsing
##and, andi,add, addi, sub, or, ori,beq,mult,move,slt,slti,sll,sllv,sra,srav,srl,srlv


val:  .word  10, -14, 30   
str:  .ascii  "Hello, world"
str1:  .asciiz  "Hello, world"
num:  .byte  'a', 'b'
arr:  .space 100

.text
main4:
	jal printMessage
	jal printMessage
	li $v0,10
	exit
	#syscall


printMessage:
	la $a0,str1
	li $v0,4
	#syscall
	jr $ra
