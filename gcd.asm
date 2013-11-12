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
 	la $t1,anmol
 	li $t0,3
 	jal sum
 	move $a0,$v0
 	li $v0,1
 	syscall
 	li $v0,10
 	syscall
 	exit
 
 sum:    addi $sp, $sp, -8       # Adjust sp
        addi $t0, $a0, -1       # Compute size - 1
        sw   $t0, 0($sp)        # Save size - 1 to stack
        sw   $ra, 4($sp)        # Save return address
        bne  $a0, $zero, ELSE   # branch ! ( size == 0 )
        li   $v0, 0             # Set return value to 0
        addi $sp, $sp, 8        # Adjust sp
        jr $ra                  # Return

ELSE:   move  $a1, $t0          # update second arg  
        jal   sum 
        lw    $t0, 0($sp)       # Restore size - 1 from stack
        li    $t7, 4            # t7 = 4 
        mult  $t1,$t0, $t7           # Multiple size - 1 by 4 
        add   $t1, $t1, $a0     # Compute & arr[ size - 1 ]
        lw    $t2, 0($t1)       # t2 = arr[ size - 1 ]
        add   $v0, $v0, $t2     # retval = $v0 + arr[size - 1]
        lw    $ra, 4($sp)       # restore return address from stack         
        addi $sp, $sp, 8        # Adjust sp
        jr $ra 