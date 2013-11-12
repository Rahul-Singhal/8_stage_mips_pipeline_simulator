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

li $t1, 3
la $s1, anmol
sw $t1, 8($s1)

li $t2, 3
lw $t1, 8($s1)

beq $t1,$t2, main
li $t5,6
exit
