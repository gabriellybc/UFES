# -*- coding: utf-8 -*-
"""
Created on Sat Apr 17 00:24:11 2021

@author: Gabrielly e Catarina
"""
# ---------------------------------------------------
from tkinter import *

# ---------------------------------------------------
# Variaveis para o posicionador
# ---------------------------------------------------
xOld = 0
yOld = 0
ClickState = 0
# ---------------------------------------------------
Master = Tk()

def f_calcula():
    try:
        vi = float(entry_vi.get())
        r1 = float(entry_r1.get())
        r2 = float(entry_r2.get())
        if r1 >= 0 and r2 >= 0:
            vo = vi *(r2/(r1+r2))
            label_vo["text"] = round(vo, 2)
        else:
            label_vo["text"] = "Erro!"
    except:
        label_vo["text"] = "Erro!"
        


# Função do mouse para o posicionador
def mouse_btn1(event):
    global ClickState, xOld, yOld
    ClickState = not ClickState
    if ClickState:
        xOld = event.x
        yOld = event.y
        Master.title("Posicionador: Passo 2: Clique na posição 'Inf.Dir'")
    else:
        my_width = str(event.x - xOld)
        my_height = str(event.y - yOld)
        str1 = "place(width=" + my_width
        str2 = ", height=" + my_height
        str3 = ", x=" + str(xOld)
        str4 = ", y=" + str(yOld) +")"
        print(str1 + str2 + str3 + str4)
        Master.title("Posicionador: Passo1: Clique na posição 'Sup.Esq'")
        
back_image = PhotoImage(file="desafio_002.png")
label_fundo = Label(Master, image=back_image)
label_fundo.place(x=0, y=0)

bt_calculo = Button(Master, text='Calcula', font='Arial 20 bold', bg='#3F48CC',  fg ="white", command=f_calcula)
bt_calculo.place(width=165, height=65, x=312, y=522)

entry_vi = Entry(Master, font = "Arial 20")
entry_vi.place(width=96, height=41, x=87, y=115)
entry_vi.insert(END, 10)

entry_r1 = Entry(Master, font = "Arial 20")
entry_r1.place(width=97, height=42, x=403, y=165)
entry_r1.insert(END, 10)

entry_r2 = Entry(Master, font = "Arial 20")
entry_r2.place(width=96, height=40, x=406, y=345)
entry_r2.insert(END, 10)

label_vo = Label(Master, text="5", font="Arial 20")
label_vo.place(width=118, height=40, x=586, y=255)

label_titulo = Label(Master, text="Desafio 02", font="Arial 20 bold", fg ="white", bg="#3F48CC")
label_titulo.place(width=781, height=37, x=7, y=4)

               
# Evento do mouse pára o posicionador
Master.bind('<Button-1>', mouse_btn1)



#Configurações da tela Master
Master.geometry("815x635+100+100")
Master.title("Posicionador Passo 1: Clique na posição 'Sup.Esq'")
Master.iconbitmap(default='tela1.ico')
mainloop()    
