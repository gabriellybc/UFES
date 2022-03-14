.data
msgErro: 	.asciiz "ERRO: O NUMERO DEVE SER MAIOR DO QUE ZERO!\n"
quebra:		.asciiz "\n"
zero:		.word 	0x00
um:		.word 	0x01

.text
prog:
li $v0, 5 #lendo numero
syscall
add $t0, $v0, $0
		
bltz $t0, erro #verifica se o numero < zero

#iniciando variaveis
lw $t1, um
lw $t2, zero
lw $t3, um
lw $t4, um
 
 	
FactorialSingle:
#convertendo para float o numero digitado
beq $t0, $t1, fim #compara o numero digitado com o valor 1, se for verdadeiro, ele sai
beq $t0, $t2, fim # se o numero digitado == zero pula para o fim
add $t1, $t1, $t4 #i = i+1
mul $t3, $t3, $t1 # fat = i*(i+1)
j FactorialSingle


fim:
#imorimindo inteiro
li  $v0, 1           
add $a0, $t3, $0  
syscall

li $v0, 10
syscall
	
	
erro:
la $a0 msgErro
j prog
	
