# -*- coding: utf-8 -*-
"""
Spyder Editor

Este é um arquivo de script temporário.
"""

# -----------------------------------------------------------------------------
#Prog: Projeto de mag2
#Finalidade: Simulação de um Limitador de Corrente de Falta Supercondutor
#Data: 16/04/2021
#Dev: G.B.Cariman e C.S.
# -----------------------------------------------------------------------------
from tkinter import *
tela1 = Tk() #É a tela mestre, ela chama as outras coisas...
# -----------------------------------------------------------------------------
# Declarações Globais: Variaveis e constantes
# -----------------------------------------------------------------------------
var1=StringVar()

# -----------------------------------------------------------------------------
# Funções
# -----------------------------------------------------------------------------
def fbt1():
    print("Botão1")
    var1.set("Texto final")

def mouseBtnEsquerdo(evento): #É o clique do botão que mostra localização
  tela1.title('uLab'+" x: "+str(evento.x)+' y: '+str(evento.x))
  print(tela1.geometry())
  #Label1.place(x=evento.x, y=evento.y)



# -----------------------------------------------------------------------------
# Widgwts
# -----------------------------------------------------------------------------
FundoTela1 = PhotoImage(file="desafio_002.png") #Definiu a imagem de fundo
LabelFundo = Label(tela1, image = FundoTela1)
LabelFundo.place(x=0, y=0)

Label1 = Label(tela1, text="Welcome", width=16, height=1, font="Arial 20 bold", background="Gray")
Label1.place(x=527, y=527)

label_title = Label(tela1, textvariable=var1, padx=60, width=15, height=1, font="Arial 20 bold", bg="gray")
label_title.place(x=200, y=70)
var1.set("Texto inicial")

botao1 = Button(tela1, text="Botão1", command=fbt1)
botao1.place(x=10, y=10)
# -----------------------------------------------------------------------------
tela1.title("uLab Eletronica") #Titulo da tela
#tela1.iconbitmap(default="tela1.ico")
tela1.geometry("815x635+100+100") #tela1.geometry("LxA+DE+DT") É o tamanho e localização da tela
tela1.wm_resizable(width=False,height=False) #Trava a tela em um tamanho fixo





tela1.bind('<Button-1>', mouseBtnEsquerdo)
tela1.mainloop()
# -----------------------------------------------------------------------------
# E.O.F
# -----------------------------------------------------------------------------