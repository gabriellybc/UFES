.data
msg1: .asciiz "Digite um valor inteiro: "
x: .float 1.5674
 
.text
# print message on shell
li $s0, 0x00400000  	# save return adress in $s0
L1: li $v0, 4 	# system call for print_str
la $a0, msg1 		# address of string to print
syscall
 
# now get an integer from the user
li $v0, 5 		# system call for read_int
syscall 			# the integer is placed in $v0
 
# do some computation here with the number
addu $t0, $v0, $0 	# move the number to $t0
sll $t0, $t0, 6 	# change <digit> with the last digit of your UFES id (matricula) 
# print the result in shell
li $v0, 1 		# system call for print_int
addu $a0, $t0, $0 	# move number to be printed in $a0
syscall

l.s $f0, x
add.s $f2, $f0, $f0
 
# restore now the return address in $ra and return from main
addu $ra, $0, $s0 	# return address back in $ra
jr $ra 			# return to the main label