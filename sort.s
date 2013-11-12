#t0 Dummy count
#t1 stores the array address
#t2 stores count permanently
#t3 pointer to start of the array
#t4 

.data
array : .word 0
msg1: .asciiz "Please enter count: \n"
msg2: .asciiz "count = "
msg3: .asciiz "Please enter the elements to be sorted: \n"
msg4: .ascii " "
msg5: .asciiz "Median element is "
msg6: .asciiz "\n"
msg7: .asciiz "Median element(ignoring duplicates) is "
msg8: .asciiz "Sorted List: \n"
narray : .word 0


.text

main:
li $v0, 4
la $a0, msg1
syscall
la $a0, msg2
syscall
li $v0, 5
syscall
move $t0, $v0
move $t2, $v0
li $v0, 4
la $a0, msg3
syscall

la $t1, array

input:
beqz $t0, initialise
li $v0, 5
syscall
sw $v0, ($t1)
addi $t1, $t1, 4
addi $t0, $t0, -1
b input

initialise:
move $t0, $t2
addi $t0, $t0, -1
la $t1, array
la $t3, ($t1) 
la $t4, ($t1)

sort:
beq $t3, $t4, increment
lw $t5, ($t4)
lw $t6, ($t3)
bgt $t6, $t5, swap
addi $t3, $t3, 4
b sort

 
increment:
beqz $t0, print
la $t3, ($t1)
addi $t4, $t4, 4
addi $t0, $t0, -1
b sort

#noswap:
#addi $t3, $t3, 4
#b sort

swap:
sw $t6, ($t4)
sw $t5, ($t3)
addi $t3, $t3, 4
b sort

li $v0, 4
la $a0, msg8
syscall

print:
li $v0, 4
la $a0, msg8
syscall

p:
beq $t0,$t2, next
lw $t7, ($t1)
move $a0, $t7
li $v0, 1
syscall

li $v0, 4
la $a0, msg4
syscall

addi $t1, $t1, 4
addi $t0, $t0, 1
b p

next:
li $v0, 4
la $a0, msg6
syscall
la $t1, array

move $t0, $t2
lw $t3, ($t1)
addi $t1, $t1, 4
la $t7, narray
sw $t3, ($t7)
addi $t0, $t0, -1
li $t4, 0
addi $t4, $t4, 1


loop:
beqz $t0,check
lw $t3, ($t1)
lw $t5, ($t7)
bne $t3, $t5, new
addi $t1,$t1, 4
addi $t0, $t0, -1
b loop

new:
addi $t7, $t7, 4
addi $t4, $t4, 1
sw $t3, ($t7)
addi $t1,$t1, 4
addi $t0, $t0, -1
b loop


check:
andi $t5, $t4, 1
beq $t5, 1, odd
bne $t5, 0, even


odd:
beq $t4, $t2, oprint11
bne $t4, $t2, oprint22

oprint11:
la $t7, narray
addi $t5, $t4, 1
srl $t5, $t5,1 
addi $t5, $t5, -1

oprint1:
beqz $t5, p1
addi $t7, $t7, 4
addi $t5, $t5, -1
b oprint1

p1:
li $v0, 4
la $a0, msg5
syscall
li $v0, 1
lw $a0, ($t7)
syscall
li $v0, 4
la $a0, msg6
b exit

oprint22:

la $t7, narray
addi $t5, $t4, 1
srl $t5, $t5,1 
addi $t5, $t5, -1


oprint2:
beqz $t5, p2
addi $t7, $t7, 4
addi $t5, $t5, -1
b oprint2

p2:
li $v0, 4
la $a0, msg7
syscall
li $v0, 1
lw $a0, ($t7)
syscall
li $v0, 4
la $a0, msg6
b exit

even:
beq $t4, $t2, eprint11
bne $t4, $t2, eprint22

eprint11:
la $t7, narray
move $t5, $t4
srl $t5, $t5,1 
addi $t5, $t5, -1

eprint1:
beqz $t5, p1
addi $t7, $t7, 4
addi $t5, $t5, -1
b eprint1

ep1:
li $v0, 4
la $a0, msg5
syscall
li $v0, 1
lw $t8, ($t7)
move $a0, $t8
syscall
li $v0, 4
la $a0, msg6
b exit

eprint22:
srl $t5, $t5,1 

eprint2:
beqz $t5, p2
addi $t7, $t7, 4
addi $t5, $t5, -1
b eprint2

ep2:
li $v0, 4
la $a0, msg7
syscall
li $v0, 1
lw $t8, ($t7)
move $a0, $t8
syscall
li $v0, 4
la $a0, msg6
b exit

exit:
li $v0, 10
syscall

