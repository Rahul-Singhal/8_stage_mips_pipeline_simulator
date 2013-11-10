.data
##checked for correct parsing
##and, andi,add, addi, sub, or, ori,beq,mult,move,slt,slti,sll,sllv,sra,srav,srl,srlv


val:  .word  10, -14, 30   
str:  .ascii  "Hello, world"
str:  .asciiz  "Hello, world"
num:  .byte  'a', 'b'
arr:  .space 100

.text
main4:
mult $t1, $t2, $t3
li,$t1,0
li $t2,0
exit
beq $t1,$t2,main4
mult $t1, $t2, $t3
