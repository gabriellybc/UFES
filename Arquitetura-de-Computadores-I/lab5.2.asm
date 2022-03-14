.data
msgErro: 	.asciiz "ERRO: O NUMERO DEVE SER MAIOR DO QUE ZERO!\n"
quebra:		.asciiz "\n"
zero:		.float 	0.0
um:		.float 	1.0

.text
prog:
li $v0, 5 #lendo numero
syscall
add $t0, $v0, $0
		
bltz $t0, erro #verifica se o numero < zero

#convertendo para float o numero digitado
mtc1 $t0, $f0
cvt.s.w $f0, $f0 

#iniciando variaveis
l.s $f1, um
l.s $f2, zero
l.s $f3, um
l.s $f4, um
 
 	
FactorialSingle:
c.eq.s $f0, $f1 #compara o numero digitado com o valor 1
bc1t fim #se for verdadeiro, ele sai
c.eq.s $f0, $f2 # se o numero digitado == zero pula para o fim
bc1t fim
add.s $f1, $f1, $f4 #i = i+1
mul.s $f3, $f3, $f1 # fat = i*(i+1)
j FactorialSingle


fim:
mov.s $f12, $f3 #imprimindo PF
li $v0, 2
syscall

la $a0 quebra
li  $v0, 4         
syscall

#convertendo para inteiro
cvt.w.s $f12, $f12
mfc1 $t1, $f12

#imorimindo inteiro
li  $v0, 1           
add $a0, $t1, $0  
syscall

li $v0, 10
syscall
	
	
erro:
la $a0 msgErro
j prog
	