.data
dim: .word 2
a: .word 6, -6
b: .word -7, 6
r1: .space 8
r2: .double 0, 0

.text
lw $t0, dim 
la $t1, a 
la $t2, b 
la $t3, r1 
la $t4, r2 
loop:
beq $t0, $zero, endloop 

lw $t5, 0($t1)
lw $t6, 0($t2)
rem $t7, $t5, $t6
sw $t7, 0($t3) # MEM[r1 + 0] = $t3

l.d $f2, 0($t1) # $f0 = MEM[a + 0] 
l.d $f4, 0($t2) # $f0 = MEM[b + 0] 
div.d $f6, $f2, $f4
s.d $f6, 0($t4) # MEM[r2 + 0] = $f0 

addi $t0, $t0, -1 
addi $t1, $t1, 4 
addi $t2, $t2, 4 
addi $t3, $t3, 4 
addi $t4, $t4, 8
j loop 
endloop:
li $v0, 10
syscall
