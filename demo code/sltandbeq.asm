.data
##checked for correct parsing
##and, andi,add, addi, sub, or, ori,beq,mult,move,slt,slti,sll,sllv,sra,srav,srl,srlv


val:  .word  10, -14, 30   
str:  .ascii  "Hello, world"
str1:  .asciiz  "Hello, world"
num:  .byte  'a', 'b'
arr:  .space 100
anmol: .word 1 2 3 

.text

main:

li $t1,10
li $t2,11
slt $t3,$t1,$t2
li $t4,1
beq $t3,$t4,main
li $t4,1


