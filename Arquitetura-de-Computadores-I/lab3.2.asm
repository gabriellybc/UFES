.data 
a: .word 
b: .word 

.text 
li $v0, 5
syscall 
add $t0, $v0, $0

li $v0, 5
syscall
add $t1, $v0, $0

add $t2, $t0, $t1

li $v0, 1
add $a0, $t2, $0
syscall