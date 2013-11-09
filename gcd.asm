.data 
astha: .asciiz "astha"
pavi: .word 10 12

.text
main:
add $t1, $t2, $t2
mult $t1, $t3, $t1
add $t1, $t1, $t1
lw $t1, ($t2)
add $t1, $t2, $t3
add $t1, $t2, $t5