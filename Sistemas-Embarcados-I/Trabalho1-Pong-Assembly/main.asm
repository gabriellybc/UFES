; Arquivo principal do programa para o jogo
; Primeiro trabalho da disciplina de Sistemas Embarcados 1 da UFES
; Desenvolvido por Gabrielly Barcelos Cariman
; No segundo semestre de 2022
; Link do GitHub: https://github.com/gabriellybc/sistemas-embarcados-1

; Para rodar esse jogo no seu computador você precisa ter instalado o programa DOSBOX, que pode ser baixado em https://www.dosbox.com/download.php?main=1
; Adicone o arquivo do jogo na pasta do DOSBOX que sera usada para montar o seu Drive
; Um exemplo pode ser:
;  - criar uma pasta C:\frasm
;  - abrir o DOSBOX e digitar o comando "mount c c:\frasm"
;  - copiar o arquivo do jogo para a pasta c:\frasm
;  - digitar o comando "make.bat"
;  - digitar o comando "main.exe" para rodar o jogo

; Importando as funcoes necessarias para o jogo
extern line, full_circle, circle, cursor, caracter, plot_xy 
global cor

; Inicio da parte de codigo
segment code

; Parte responsevel por pegar as interrupções do teclado e salvar em tecla_digitada
keyint:
        PUSH    AX
        PUSH    BX
        PUSH    DS
        MOV     AX,data
        MOV     DS,AX
		MOV	 	AX,0
        IN      AL, kb_data
        INC     WORD[p_i]
        AND     WORD[p_i],7
        MOV     BX,[p_i]
        MOV     BYTE[tecla_digitada],AL
        IN      AL, kb_ctl
        OR      AL, 80h
        OUT     kb_ctl, AL
        AND     AL, 7Fh
        OUT     kb_ctl, AL
        MOV     AL, eoi
        OUT     pictrl, AL
        POP     DS
        POP     BX
        POP     AX
        IRET

; Parte responsavel por fazer o delay da tela
delay:
	PUSH CX
	MOV CX, word[velocidade] ; Carrega velocidade em cx (contador para loop)
	del2:
		PUSH CX ; Coloca cx na pilha para usa-lo em outro loop
		MOV CX, 0800h
	del1:
		LOOP del1 ; No loop del1, cx é decrementado até que volte a ser zero
		POP CX ; Recupera cx da pilha
		LOOP del2 ; No loop del2, cx é decrementado até que seja zero
	POP CX ; Recupera cx da pilha
	RET

; Parte responsavel por desenhar a margem do jogo onde o circulo fica se movimentando
margem: ; Faz a margem da tela
	MOV		byte [cor],branco_intenso	
	MOV		AX,180                   	
	PUSH	AX
	MOV		AX,y2_barra                  	
	PUSH	AX
	MOV		AX,180                  	
	PUSH	AX
	MOV		AX,410                  	
	PUSH	AX
	CALL	line
		
	MOV		byte [cor],branco_intenso	
	MOV		AX,180                   	
	PUSH	AX
	MOV		AX,410                  	
	PUSH	AX
	MOV		AX,x2_margem                  	
	PUSH	AX
	MOV		AX,410                  	
	PUSH	AX
	CALL	line
	
	MOV		byte [cor],branco_intenso	
	MOV		AX,x2_margem                   	
	PUSH	AX
	MOV		AX,410                  	
	PUSH	AX
	MOV		AX,x2_margem                  	
	PUSH	AX
	MOV		AX,y2_barra                  	
	PUSH	AX
	CALL	line
	RET

; Parte responsavel por desenhar o circulo no inicio do jogo, usando x_circulo e y_circulo para pwgar a posição do circulo
circulo: ;desenha circulos 
		PUSH	AX
		; Apaga o circulo anterior
		MOV		byte [cor],rosa				
		MOV		AX,word[x_circulo] 						
		PUSH	AX						
		MOV		AX,word[y_circulo]						
		PUSH	AX
		MOV		AX,raio						
		PUSH	AX
		CALL	circle
		POP 	AX
		RET

; Parte responsavel por limpar a tela depois do menu inicial, antes do jogo começar, e depois do jogo acabar e aparecer o menu final
limpa_tela: ;desenha circulos 
		PUSH	AX
		; Apaga o circulo anterior
		MOV		byte [cor],preto			
		MOV		AX,430			
		PUSH	AX						
		MOV		AX,240					
		PUSH	AX
		MOV		AX,240						
		PUSH	AX
		CALL	full_circle
		POP 	AX
		RET

; Parte resposevel por escrever o menu inicial com os niveis de jogo disponiveis (facil, medio e dificil)
inicio: ;escrever a mensagem de inicio do jogo
	facil: 
			MOV 	CX,22						;número de caracteres
			MOV    	BX,0			
			MOV    	DH,10						;linha 0-29
			MOV     DL,26						;coluna 0-79
			MOV		byte [cor],verde
	l4:
			CALL	cursor
			MOV     AL,[BX+msg_facil]
			CALL	caracter
			INC		BX							;proximo caracter
			INC		DL							;avanca a coluna
			LOOP    l4
			
	medio: 
			MOV 	CX,22						;número de caracteres
			MOV    	BX,0			
			MOV    	DH,12						;linha 0-29
			MOV     DL,26						;coluna 0-79
			MOV		byte [cor],amarelo
	l5:
			CALL	cursor
			MOV     AL,[BX+msg_medio]
			CALL	caracter
			INC		BX							;proximo caracter
			INC		DL							;avanca a coluna
			LOOP    l5

	dificil: 
			MOV 	CX,24						;número de caracteres
			MOV    	BX,0			
			MOV    	DH,14						;linha 0-29
			MOV     DL,26						;coluna 0-79
			MOV		byte [cor],vermelho
	l6:
			CALL	cursor
			MOV     AL,[BX+msg_dificil]
			CALL	caracter
			INC		BX							;proximo caracter
			INC		DL							;avanca a coluna
			LOOP    l6

	iniciar: 
			MOV 	CX,24						;número de caracteres
			MOV    	BX,0			
			MOV    	DH,16						;linha 0-29
			MOV     DL,26						;coluna 0-79
			MOV		byte [cor],cinza
	l10:
			CALL	cursor
			MOV     AL,[BX+msg_inicio]
			CALL	caracter
			INC		BX							;proximo caracter
			INC		DL							;avanca a coluna
			LOOP    l10
			RET

; Parte responsavel por desenhar a barra que ira se movimentar ao longo do jogo
barra: ; Faz a barra do meio da tela
		PUSH	AX
		MOV		byte [cor],azul	
		MOV		AX,word[x1_barra]                   	
		PUSH	AX
		MOV		AX,y1_barra                  	
		PUSH	AX
		MOV		AX,word[x2_barra]                 	
		PUSH	AX
		MOV		AX,y1_barra                   	
		PUSH	AX
		CALL	line
			
		MOV		byte [cor],azul	
		MOV		AX,word[x2_barra]                   	
		PUSH	AX
		MOV		AX,y1_barra                   	
		PUSH	AX
		MOV		AX,word[x2_barra]                  	
		PUSH	AX
		MOV		AX,y2_barra                  	
		PUSH	AX
		CALL	line
		
		MOV		byte [cor],azul	
		MOV		AX,word[x2_barra]                   	
		PUSH	AX
		MOV		AX,y2_barra                  	
		PUSH	AX
		MOV		AX,word[x1_barra]                  	
		PUSH	AX
		MOV		AX,y2_barra                  	
		PUSH	AX
		CALL	line

		MOV		byte [cor],azul	
		MOV		AX,word[x1_barra]                   	
		PUSH	AX
		MOV		AX,y2_barra                  	
		PUSH	AX
		MOV		AX,word[x1_barra]                  	
		PUSH	AX
		MOV		AX,y1_barra                   	
		PUSH	AX
		CALL	line
		POP 	AX
		RET

; Parte resposevel por escrever o menu final com as opcoes de reiniciar o jogo ou sair do jogo
final: ;escrever a mensagem de game over
	game_over: 
			MOV 	CX,9						;número de caracteres
			MOV    	BX,0			
			MOV    	DH,10						;linha 0-29
			MOV     DL,26						;coluna 0-79
			MOV		byte [cor],vermelho
	l7:
			CALL	cursor
			MOV     AL,[BX+msg_game_over]
			CALL	caracter
			INC		BX							;proximo caracter
			INC		DL							;avanca a coluna
			LOOP    l7
			
	reinicio: 
			MOV 	CX,25						;número de caracteres
			MOV    	BX,0			
			MOV    	DH,12						;linha 0-29
			MOV     DL,26						;coluna 0-79
			MOV		byte [cor],cyan
	l8:
			CALL	cursor
			MOV     AL,[BX+msg_reinicio]
			CALL	caracter
			INC		BX							;proximo caracter
			INC		DL							;avanca a coluna
			LOOP    l8

	sair: 
			MOV 	CX,21						;número de caracteres
			MOV    	BX,0			
			MOV    	DH,14						;linha 0-29
			MOV     DL,26						;coluna 0-79
			MOV		byte [cor],magenta
	l9:
			CALL	cursor
			MOV     AL,[BX+msg_sair]
			CALL	caracter
			INC		BX							;proximo caracter
			INC		DL							;avanca a coluna
			LOOP    l9
			RET
	
; Inicio do programa
..start:
	; inicializa_registradores:
	MOV     AX,data			;Inicializa os registradores
	MOV 	DS,AX
	MOV 	AX,stack
	MOV 	SS,AX
	MOV 	SP,stacktop

	; salvar_modo_corrente_video:
	;Salvar modo corrente de video(vendo como esta o modo de video da maquina)
	MOV  	AH,0Fh
	INT  	10h
	MOV  	[modo_anterior],AL
		
	; modo_video_para_grafico:
	;Alterar modo de video para grafico 640x480 16 cores
	MOV     AL,12h
	MOV     AH,0
	INT     10h

	; inicializa_interrupcao:
	; Inicializa Interrupção
	CLI
	XOR     AX, AX
	MOV     ES, AX
	MOV     AX, [ES:int9*4];carregou AX com offset anterior
	MOV     [offset_dos], AX        ; offset_dos guarda o end. para qual ip de int 9 estava apontando anteriormente
	MOV     AX, [ES:int9*4+2]     ; cs_dos guarda o end. anterior de CS
	MOV     [cs_dos], AX		
	MOV     [ES:int9*4+2], CS
	MOV     WORD [ES:int9*4],keyint
	STI
	
	; Parte responsavel por pegar a letra digitada pelo usuario e armazenar na variavel tecla_digitada que ira definir o nivel do jogo
	define_nivel:
		MOV    	BX,0
		CALL 	inicio
		MOV		BL, BYTE[tecla_digitada]
		CMP 	BL,tecla_f
		JE		nivel_facil
		CMP 	BL,tecla_m
		JE		nivel_medio
		CMP 	BL,tecla_d
		JE		nivel_dificil
		CMP 	BL,tecla_enter
		JE		game
		JMP		define_nivel
	
	; Parte responsavel por fechar e sair do jogo
	fim1:
		CLI
		XOR     AX, AX
		MOV     ES, AX
		MOV     AX, [cs_dos]
		MOV     [ES:int9*4+2], AX
		MOV     AX, [offset_dos]
		MOV     [ES:int9*4], AX 
		STI
		MOV     AH, 4Ch
		int     21h
		RET
	
	; Partes responsaveis por alterar a velocidade do jogo de acordo com o nivel escolhido
	nivel_facil:
		MOV		DX,100
		MOV		word[velocidade],DX
		JMP		define_nivel
	nivel_medio:
		MOV		DX,100
		MOV		word[velocidade],DX
		JMP		define_nivel
	nivel_dificil:
		MOV		DX,23
		MOV		word[velocidade],DX
		JMP		define_nivel
	
	; Parte responsavel por iniciar o jogo e desenhar as condições iniciais do jogo
	game:
		CALL 	limpa_tela
		CALL 	margem
		CALL 	barra
		CALL 	circulo
		; Parte responsavel por todas as movitações do jogo
		inicio_game:
			CALL	delay
			; x_circulo_fim:
			; Parte responvel por armazenar o movimento futuro do circulo na direção x em x_circulo e verificar se ele não esta saindo das margens
			 	MOV		AX,2
				CMP		AX,5
				MOV		DX,word[x_circulo]
				MOV		AX,word[x2_margem]
				ADD		AX,150
				CMP		DX,AX
				JGE		direita_circulo
				MOV		AX,2
				CMP		AX,0
				MOV		AX,word[x1_margem]
				ADD		AX,-10
				CMP		DX,AX
				JLE		esquerda_circulo

			; Parte responvel por armazenar o movimento futuro do circulo na direção y em y_circulo e verificar se ele não esta saindo das margens
			y_circulo_fim:
				MOV		AX,2
				CMP		AX,5
				MOV		DX,word[y_circulo]
				MOV		AX,word[y2_margem]
				ADD		AX,2700
				CMP		DX,AX
				JGE		cima_circulo
				MOV		AX,2
				CMP		AX,0
				MOV		AX,word[x1_margem]
				; ADD		AX,-9999
				CMP		DX,AX
				JLE		baixo_circulo
			
			; Parte responvel por mover o circulo na direção x e y usando o movimento armazenado em x_circulo e y_circulo
			circulo_movimento:
				CALL	mover_circulo

			; movendo_barra:
			; Parte responvel por mover a barra para a direita ou esquerda de acordo com a tecla digitada pelo usuario
			barra_define_movimento:
				MOV    	BX,0
				MOV		BL, BYTE[tecla_digitada]
				CMP 	BL,tecla_d
				JE		direita_barra
				CMP 	BL,tecla_a
				JE		esquerda_barra
			
			; Parte responvel por armazenar o movimento futuro da barra na direção x em x_barra
			barra_movimento:
				JMP		mover_barra
			
			; Parte responvel por fechar e sair do jogo quando o usuario digita a tecla q
			sair_com_q:
				MOV    	BX,0
				MOV		BL, BYTE[tecla_digitada]
				CMP 	BL,tecla_q
				JE		fim2
			JMP		inicio_game

	; Partes responseiveis por alterar o movimento do circulo caso ele esteja saindo das margens
	; O movimento novo do circulo é armazenado em mover_circulo_x e mover_circulo_y
	esquerda_circulo:
		MOV		DX,raio
		MOV		word[mover_circulo_x],DX
		JMP		y_circulo_fim
	direita_circulo:
		MOV		DX,raio
		NEG		DX
		MOV		word[mover_circulo_x],DX
		JMP		y_circulo_fim
	cima_circulo:
		MOV		DX,raio
		NEG		DX
		MOV		word[mover_circulo_y],DX
		JMP		circulo_movimento
	baixo_circulo:
		MOV		DX,raio
		MOV		word[mover_circulo_y],DX
		JMP		circulo_movimento
	
	; Partes responseiveis por alterar o movimento da barra
	; O movimento novo da barra é armazenado em move_barra
	esquerda_barra:
		MOV		DX,30
		NEG		DX
		MOV		word[move_barra],DX
		JMP		barra_movimento
	direita_barra:
		MOV		DX,30
		MOV		word[move_barra],DX
		JMP		barra_movimento
		
	; atualiza_tela: ; Atualização da tela
	; Parte responsavel por atualizar a tela no final
	MOV    	AH,08h
	INT     21h
	MOV  	AH,0   						; set video mode
	MOV  	AL,[modo_anterior]   		; modo anterior
	INT  	10h
	MOV     AX,4c00h
	INT     21h

	; Parte responsavel por fechar e sair do jogo
	fim2:
			CLI
			XOR     AX, AX
			MOV     ES, AX
			MOV     AX, [cs_dos]
			MOV     [ES:int9*4+2], AX
			MOV     AX, [offset_dos]
			MOV     [ES:int9*4], AX 
			STI
			MOV     AH, 4Ch
			int     21h
			RET

	; Parte responsavel por desenhar o circulo novo:
	; Desenhando um circulo preto no lugar do antigo
	; E um circulo novo rosa na nova posição que é a posição de x_circulo e y_circulo mais mover_circulo_x e mover_circulo_y
	mover_circulo: ;desenha circulos 
		PUSH	AX
		PUSH	BX
		; Apaga o circulo anterior
		MOV		byte [cor],preto				
		MOV		AX,word[x_circulo] 						
		PUSH	AX						
		MOV		AX,word[y_circulo]						
		PUSH	AX
		MOV		AX,raio						
		PUSH	AX
		CALL	circle
		; Desenha o novo circulo
		MOV		byte [cor],rosa
		MOV		BX,word[mover_circulo_x]	
		ADD		word[x_circulo],BX			
		MOV		AX,word[x_circulo]
		PUSH	AX
		MOV		BX,word[mover_circulo_y]	
		ADD		word[y_circulo],BX
		MOV		AX,word[y_circulo]
		PUSH	AX
		MOV		AX,raio
		PUSH	AX
		CALL	circle
		POP 	BX
		POP 	AX
		JMP		barra_define_movimento

	; Parte responsavel por desenhar a barra nova:
	; Desenhando uma barra preta no lugar da antiga
	; E uma barra nova azul na nova posição que é a posição de x1_barra e x1_barra mais move_barra
	mover_barra: ; Faz a barra mover na tela
		PUSH	AX
		PUSH	BX
		; Apaga a barra
		MOV		byte [cor],preto	
		MOV		AX,word[x1_barra]                   	
		PUSH	AX
		MOV		AX,y1_barra                   	
		PUSH	AX
		MOV		AX,word[x2_barra]                  	
		PUSH	AX
		MOV		AX,y1_barra                   	
		PUSH	AX
		CALL	line
			
		MOV		byte [cor],preto	
		MOV		AX,word[x2_barra]                   	
		PUSH	AX
		MOV		AX,y1_barra                   	
		PUSH	AX
		MOV		AX,word[x2_barra]                  	
		PUSH	AX
		MOV		AX,y2_barra                  	
		PUSH	AX
		CALL	line
		
		MOV		byte [cor],preto	
		MOV		AX,word[x2_barra]                   	
		PUSH	AX
		MOV		AX,y2_barra                  	
		PUSH	AX
		MOV		AX,word[x1_barra]                  	
		PUSH	AX
		MOV		AX,y2_barra                  	
		PUSH	AX
		CALL	line

		MOV		byte [cor],preto	
		MOV		AX,word[x1_barra]                   	
		PUSH	AX
		MOV		AX,y2_barra                  	
		PUSH	AX
		MOV		AX,word[x1_barra]                  	
		PUSH	AX
		MOV		AX,y1_barra                   	
		PUSH	AX
		CALL	line

		; Faz a barra se mover e desenha ela
		MOV		BX,word[move_barra]
		ADD		word[x1_barra],BX
		ADD		word[x2_barra],BX
		; Verifica se a barra chegou ao final
		MOV		BX,word[x1_barra]
		MOV		DX,word[x1_margem]
		ADD		DX,-100
		CMP		BX,DX
		JLE		para_barra

		MOV		byte [cor],azul	
		MOV		AX,word[x1_barra]                   	
		PUSH	AX
		MOV		AX,y1_barra                   	
		PUSH	AX
		MOV		AX,word[x2_barra]                  	
		PUSH	AX
		MOV		AX,y1_barra                   	
		PUSH	AX
		CALL	line
			
		MOV		byte [cor],azul	
		MOV		AX,word[x2_barra]                   	
		PUSH	AX
		MOV		AX,y1_barra                   	
		PUSH	AX
		MOV		AX,word[x2_barra]                  	
		PUSH	AX
		MOV		AX,y2_barra                  	
		PUSH	AX
		CALL	line
		
		MOV		byte [cor],azul	
		MOV		AX,word[x2_barra]                   	
		PUSH	AX
		MOV		AX,y2_barra                  	
		PUSH	AX
		MOV		AX,word[x1_barra]                  	
		PUSH	AX
		MOV		AX,y2_barra                  	
		PUSH	AX
		CALL	line

		MOV		byte [cor],azul	
		MOV		AX,word[x1_barra]                   	
		PUSH	AX
		MOV		AX,y2_barra                  	
		PUSH	AX
		MOV		AX,word[x1_barra]                  	
		PUSH	AX
		MOV		AX,y1_barra                   	
		PUSH	AX
		CALL	line

		MOV		BX,0
		MOV		word[move_barra],BX

		POP		BX
		POP		AX
		JMP		sair_com_q
		; Verifica se a barra chegou ao final do lado esquerdo da tela
		para_barra:
			MOV		BX,word[move_barra]
			NEG		BX
			ADD		word[x1_barra],BX
			ADD		word[x2_barra],BX
			JMP		sair_com_q

	; ; Partes responseiveis por fazer o jump intermediario do codigo
	; ; Porque o codigo estava muito grande e nao cabia no limite de bytes suportado
	; ; Por isso eh necessario fazer um pulo intermediario para o codigo continuar
	; fim3:
	; 	JMP		fim1
	; inicio_game1:
	; 	JMP		inicio_game
	; define_nivel1:
	; 	JMP		define_nivel
	
	; ; Parte responsavel por pegar a letra digitada pelo usuario e armazenar na variavel tecla_digitada que ira definir para onde o jogador ira depois de perder o game
	; define_final:
	; 	MOV    	BX,0
	; 	CALL 	final
	; 	MOV		BL, BYTE[tecla_digitada]
	; 	CMP 	BL,tecla_q
	; 	JE		fim3
	; 	CMP 	BL,tecla_a
	; 	JE		define_nivel1
	; 	JMP		define_final

	; ; Parte responvel por pausar o jogo quando o usuario digita a tecla s
	; pausar_com_s:
	; 	MOV    	BX,0
	; 	MOV		BL, BYTE[tecla_digitada]
	; 	CMP 	BL,tecla_s
	; 	JE		pausado
	; 	JMP		inicio_game1
	; ; Parte responvel por despausar o jogo quando o usuario digita a tecla s
	; pausado:
	; 	MOV    	BX,0
	; 	MOV		BL, BYTE[tecla_digitada]
	; 	CMP 	BL,tecla_s
	; 	JE		inicio_game1
	; 	JMP		pausado

	; ; Parte responvel por verificar se o jogador perdeu o jogo
	; morte:
	; 	MOV		AX,2
	; 	CMP		AX,5
	; 	MOV		DX,word[x_circulo]
	; 	MOV		AX,word[x2_barra]
	; 	CMP		DX,AX
	; 	JGE		define_final
	; 	MOV		AX,2
	; 	CMP		AX,0
	; 	MOV		AX,word[x1_barra]
	; 	CMP		DX,AX
	; 	JLE		define_final
	; 	JMP		inicio_game1
		

;*******************************************************************

segment data

cor		db		branco_intenso

;	I R G B COR
;	0 0 0 0 preto
;	0 0 0 1 azul
;	0 0 1 0 verde
;	0 0 1 1 cyan
;	0 1 0 0 vermelho
;	0 1 0 1 magenta
;	0 1 1 0 marrom
;	0 1 1 1 branco
;	1 0 0 0 cinza
;	1 0 0 1 azul claro
;	1 0 1 0 verde claro
;	1 0 1 1 cyan claro
;	1 1 0 0 rosa
;	1 1 0 1 magenta claro
;	1 1 1 0 amarelo
;	1 1 1 1 branco intenso

preto		    equ		0
azul		    equ		1
verde		    equ		2
cyan		    equ		3
vermelho	    equ		4
magenta		    equ		5
marrom		    equ		6
branco		    equ		7
cinza		    equ		8
azul_claro	    equ		9
verde_claro	    equ		10
cyan_claro	    equ		11
rosa		    equ		12
magenta_claro	equ		13
amarelo		    equ		14
branco_intenso	equ		15

raio 			equ 	10

y1_barra	    equ		180
y2_barra	    equ		190

x1_margem	    equ		10
x2_margem	    equ		630
y1_margem	    equ		40
y2_margem	    equ		470

tecla_enter		equ 	1Ch
tecla_a			equ 	1Eh
tecla_d			equ 	20h
tecla_s 		equ 	1Fh
tecla_f 		equ 	21h
tecla_m 		equ 	32h
tecla_q 		equ 	10h

kb_data			equ 	60h  ;PORTA DE LEITURA DE TECLADO
kb_ctl 			equ 	61h  ;PORTA DE RESET PARA PEDIR NOVA INTERRUPCAO
int9    		equ 	9h
pictrl  		equ 	20h
eoi     		equ 	20h


modo_anterior	db		0
linha   	    dw  	0
coluna  	    dw  	0
deltax		    dw		0
deltay		    dw		0

msg_facil    	db  	'Pressione f para Facil $'
msg_medio    	db  	'Pressione m para Medio $'
msg_dificil    	db  	'Pressione d para Dificil $' 
msg_inicio    	db  	'Inicie com a tecla ENTER $' 

msg_game_over   db  	'Game Over $'
msg_reinicio   	db  	'Pressione r para Reinicio $'
msg_sair    	db  	'Pressione q para Sair $' 

x_circulo	    dw		315
y_circulo	    dw		255
mover_circulo_x	dw		10	
mover_circulo_y	dw		10

x1_barra	    dw		285
x2_barra	    dw		345
move_barra		dw		10

velocidade 		dw 		3

cs_dos  		dw  	1
offset_dos  	dw 		1
tecla_digitada 	db  	32h 
p_i     		dw  	0   ;ponteiro p/ interrupcao (qnd pressiona tecla)  
p_t     		dw  	0   ;ponterio p/ interrupcao ( qnd solta tecla)    


;*************************************************************************
segment stack stack
		DW 		512
stacktop:
