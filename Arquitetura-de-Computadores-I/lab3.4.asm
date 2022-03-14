.text
# now get an integer from the user
li $v0, 5 		# system call for read_int
syscall 			# the integer is placed in $v0
addu $t0, $v0, $0 	# move the number to $t0

li $v0, 5 		# system call for read_int
syscall 			# the integer is placed in $v0
addu $t1, $v0, $0 	# move the number to $t0

mult $t0, $t1

mfhi $a0
syscall 
li $v0 1
mflo $a0
syscall 