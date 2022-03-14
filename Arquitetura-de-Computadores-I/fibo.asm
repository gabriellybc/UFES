.data 
num: .word 10 
res: .word 0 
Vout: .space 400 
.text 
#carregando registradores com valores aleatorios 
la $s1, Vout 
lw $a0, num 
li $t0, 1 
li $t1, 1 
li $t2, 1 
loop: 
ble $a0, $t0, end 
sw $t2, 8($s1)
nop
nop 
addi $s1, $s1, 4 
addi $t0, $t0, 1  
addi $14, $0, -2 
move $t3, $t2 
add $t2, $t2, $t1
nop
nop 
move $t1, $t3 
b loop 
end: 
sw $t2, 8($s1)
nop
nop 
sw $t2, res 
