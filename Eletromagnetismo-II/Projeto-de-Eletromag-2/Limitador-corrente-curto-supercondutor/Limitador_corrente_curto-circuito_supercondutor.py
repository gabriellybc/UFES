# -*- coding: utf-8 -*-
"""
Created on Sat Apr 17 00:24:11 2021

@author: Catarina e Gabrielly

Projeto de um Limitador de corrente de curto-circuito supercondutor resistivo com interface gráfica 
"""
# -----------------------------------------------------------------------------
import numpy as np
import matplotlib.pyplot as plt 
from tkinter import *

janela = Tk() # Tela principal

# ---------------------------------Funções-------------------------------------

#               Função acionada pelo botão de circuito de curto-circuito
def curto_circuito():
    #  Definição das telas
    global janela
    janela.destroy()  # Destruição da janela antiga
    janela = Tk()  # Criação da nova tela
    
    #   Definição da imagem de fundo
    back_image = PhotoImage(file="curto_circuito.png")
    label_fundo = Label(janela, image=back_image)
    label_fundo.place(x=0, y=0)
    
    #   Definição do botão de voltar para o menu de seleção
    bt_voltar = Button(janela, text='Voltar', font='Arial 20 bold', bg='gray',  fg ="white", command=voltar)
    bt_voltar.place(width=103, height=44, x=229, y=431)
    
    #   Criação da label Vpico
    label_Vpico = Label(janela, text="19.50", font="Arial 20")
    label_Vpico.place(width=99, height=43, x=56, y=198)
    
    #   Criação da label R1
    label_R1 = Label(janela, text="3.33", font="Arial 20")
    label_R1.place(width=99, height=43, x=424, y=261)
    
    #   Configuração da tela
    janela.geometry("577x499+341+81")  # Geometria
    janela.wm_resizable(width = False, height=False)  # Fixa a tela em determinada geometria
    janela.title("Circuito do curto-circuito limitado pelo supercondutor")  # Titulo da tela
    janela.iconbitmap(default='Logo_Ufes.ico')  # Definição do icone da tela
    janela.mainloop()
    
#          Função acionada pelo botão de circuito de curto-circuito limitado
def curto_circuito_limitado():
    #  Definição das telas
    global janela
    janela.destroy()  # Destroi a tela antiga
    janela = Tk()  # Cria a nova tela
    
    #   Definição da imagem de fundo
    back_image = PhotoImage(file="curto_circuito_limitado.png")
    label_fundo = Label(janela, image=back_image)
    label_fundo.place(x=0, y=0)
    
    #   Definição do botão de voltar para o menu de seleção
    bt_voltar = Button(janela, text='Voltar', font='Arial 20 bold', bg='gray',  fg ="white", command=voltar)
    bt_voltar.place(width=104, height=44, x=497, y=547)
    
    #   Criação da label Vpico
    label_Vpico = Label(janela, text="19.50", font="Arial 20")
    label_Vpico.place(width=101, height=43, x=56, y=316)
    
    #   Criação da label R
    label_R = Label(janela, text="3.33", font="Arial 20")
    label_R.place(width=101, height=48, x=1024, y=426)
    
    #   Criação da label Rcontato
    label_Rcontato = Label(janela, text="0.30", font="Arial 20")
    label_Rcontato.place(width=99, height=43, x=326, y=228)
    
    #   Criação da label Rf
    label_Rf = Label(janela, text="0.70", font="Arial 20")
    label_Rf.place(width=103, height=44, x=658, y=205)
    
    #   Criação da label If
    label_If = Label(janela, text="2.70", font="Arial 20")
    label_If.place(width=106, height=43, x=655, y=278)
    
    #   Criação da label Ic
    label_Ic = Label(janela, text="2.00", font="Arial 20")
    label_Ic.place(width=105, height=44, x=658, y=344)
    
    #   Configuração da tela
    janela.geometry("1170x621+84+49")  # Geometria
    janela.wm_resizable(width = False, height=False)  # Fixa a tela em determinada geometria
    janela.title("Circuito do curto-circuito limitado pelo supercondutor")  # Titulo da tela
    janela.iconbitmap(default='Logo_Ufes.ico')# Definição do icone da tela
    janela.mainloop()
    
#                    Função acionada pelo botão de simulação
def simulacao():
    #       Simulação de Limitador de corrente de curto-circuito supercondutor resistivo 
    #   Criação do array tempo
    Nt = 2**10  # Número de pontos = 2^15 = 32.768
    t_fim = 0.1  # [s] Tempo final de análise 
    tempo = np.linspace(0,t_fim,Nt)  # [s]
    
    #   Dados de entrada do supercondutor
    Rf = 0.7  # [Ohm] Resistência que se deseja inserir 
    If = 2.7  # [A] Corrente em que a resistência alcança o valor de RF
    Ic = 2    # [A] Corrente crítica em que o supercondutor sai do estado supercondutor que tem resistência zero

    #   Dados do circuito sem o supercondutor
    R1 = 3.33  # [Ohm] Carga resistiva alimentada diretamente da rede
    Isem = np.ones(Nt)  # [A] Instanciação do array da corrente no circuito sem o supercondutor
    
    #   Dados do circuito com o supercondutor
    Rcontato = 0.3  # [Ohm] Resistência de contato do supercondutor
    R = 3.33  # [Ohm] Carga resistiva alimentada através do supercondutor
    Rsuper = np.ones(Nt)  # [Ohm] Instanciação do array da resistência do supercondutor
    Icom = np.ones(Nt)  # [A] Instanciação do array da corrente no circuito com o supercondutor
    
    #   Instanciação da fonte de tensão
    Vpico = 19.5  # [V] Tensão máxima da fonte
    v = np.ones(Nt)  # [V] Instanciação do array da fonte de tensão
    v = Vpico*np.sin(60*2*np.pi*tempo)  # [V] Senoide da fonte de tensão
    
    #   Dados no instante inicial de tempo
    Rsuper[0] = 0  # [Ohm]
    Icom[0] = v[0]/(R+Rcontato+Rsuper[0])  # [A] 

    Isubt = If - Ic  # [A]
    
    #   Estruturas para calcular a resistência no momento atual do supercondutor em função da corrente passada do circuito
    for nt in range(1,Nt):
        if np.abs(Icom[nt-1]) < Ic:
            Rsuper[nt] = 0  # [Ohm]
        elif np.abs(Icom[nt-1]) > If:
            Rsuper[nt] = Rf  # [Ohm]
        else:
            Rsuper[nt] = ((Rf*(np.abs(Icom[nt-1])-Ic))/(Isubt))  # [Ohm]
        Icom[nt] = v[nt]/(R+Rcontato+Rsuper[nt])  # [A] Despois de calcular a resistência do momento atual, a corrente do circuito com o supercondutor é encontrada

    Isem = v/R1  # [A] Calculo da corrente no circuito sem o supercondutor
    
    #   Plotando o gráfico
    plt.figure(figsize = (10, 8))
    plt.plot(tempo, Isem, color='red')
    plt.plot(tempo, Icom, color='black')
    plt.title('Simulação de curto-circuito sem e com o limitador de corrente')
    plt.xlabel('Tempo [s]')
    plt.ylabel('Corrente [A]')
    plt.legend(['Sem limitador', 'Com limitador'], loc=1)
    plt.grid()
    plt.savefig('simulacao_limitador_supercondutor.png')
    plt.show()
    
    #                       Interface gráfica  
    #  Definição das telas
    global janela
    janela.destroy()  # Destruição da janela antiga
    janela = Tk()  # Criação da nova tela
    
    #   Definição da imagem de fundo
    back_image = PhotoImage(file="simulacao_limitador_supercondutor.png")
    label_fundo = Label(janela, image=back_image)
    label_fundo.place(x=0, y=0)
    
    #   Definição do botão de voltar para o menu de seleção
    bt_voltar = Button(janela, text='Voltar', font='Arial 20 bold', bg='gray',  fg ="white", command=voltar)
    bt_voltar.place(width=100, height=37, x=310, y=582)
    
    #   Configuração da tela
    janela.geometry("723x621+342+46")  # Geometria
    janela.wm_resizable(width = False, height=False)  # Fixa a tela em determinada geometria
    janela.title("Gráfico da simulação")  # Titulo da tela
    janela.iconbitmap(default='Logo_Ufes.ico')  # Definição do icone da tela
    janela.mainloop()
    
#              Função acionada pelo botão de voltar ao menu de seleção
def voltar():
    #  Definição das telas
    global janela
    janela.destroy()  # Destruição da janela antiga
    janela = Tk()  # Criação da nova tela
    
    #   Definição da imagem de fundo
    back_image = PhotoImage(file="selecione.png")
    label_fundo = Label(janela, image=back_image)
    label_fundo.place(x=0, y=0)
    
    #   Definição do botão do circuito de curto-circuito
    bt_curto_circuito = Button(janela, text='Circuito do curto-circuito', font='Arial 20 bold', bg='red',  fg ="white", command=curto_circuito)
    bt_curto_circuito.place(width=1030, height=48, x=25, y=170)
    
    #   Definição do botão do circuito de curto-circuito com limitador de corrente
    bt_curto_circuito_limitado = Button(janela, text='Circuito do curto-circuito limitado pelo supercondutor', font='Arial 20 bold', bg='black',  fg ="white", command=curto_circuito_limitado)
    bt_curto_circuito_limitado.place(width=1028, height=47, x=27, y=228)
    
    #   Definição do botão de simulação
    bt_simulacao = Button(janela, text='Simular', font='Arial 20 bold', bg='gray',  fg ="white", command=simulacao)
    bt_simulacao.place(width=1028, height=47, x=26, y=288)
    
    #   Configuração da tela
    janela.geometry("1078x357+106+108")  # Geometria
    janela.wm_resizable(width = False, height=False)  # Fixa a tela em determinada geometria
    janela.title("Limitadores de Corrente de curto-circuito Supercondutor")  # Titulo da tela
    janela.iconbitmap(default='Logo_Ufes.ico')  # Definição do icone da tela
    janela.mainloop()

# -----------------------------------------------------------------------------

#   Definição da imagem de fundo
back_image = PhotoImage(file="selecione.png")
label_fundo = Label(janela, image=back_image)
label_fundo.place(x=0, y=0)

#   Definição do botão do circuito de curto-circuito
bt_curto_circuito = Button(janela, text='Circuito do curto-circuito', font='Arial 20 bold', bg='red',  fg ="white", command=curto_circuito)
bt_curto_circuito.place(width=1030, height=48, x=25, y=170)

#   Definição do botão do circuito de curto-circuito com limitador de corrente
bt_curto_circuito_limitado = Button(janela, text='Circuito do curto-circuito limitado pelo supercondutor', font='Arial 20 bold', bg='black',  fg ="white", command=curto_circuito_limitado)
bt_curto_circuito_limitado.place(width=1028, height=47, x=27, y=228)

#   Definição do botão de simulação
bt_simulacao = Button(janela, text='Simular', font='Arial 20 bold', bg='gray',  fg ="white", command=simulacao)
bt_simulacao.place(width=1028, height=47, x=26, y=288)

#   Configuração da tela
janela.geometry("1078x357+106+108")  # Geometria
janela.wm_resizable(width = False, height=False)  # Fixa a tela em determinada geometria
janela.title("Limitadores de Corrente de curto-circuito Supercondutor")  # Titulo da tela
janela.iconbitmap(default='Logo_Ufes.ico')  # Definição do icone da tela
janela.mainloop()