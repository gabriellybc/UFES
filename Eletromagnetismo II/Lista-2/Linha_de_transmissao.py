# -*- coding: utf-8 -*-
"""
Created on Tue Apr 20 17:43:03 2021

Linha_de_transmissao

@author: Gabrielly
"""
# -------------------------------- Imports ------------------------------------
import numpy as np
import math
import cmath

# --------------------------------- Funções -----------------------------------

def Impedancia_Caracteristica(R, L, G, C, frequencia): 
    #      Impedancia caracteristica Zo da linha
    #
    #  Entrada:
    #          R         - Resistência por unidade de comprimento [Ohm/m]
    #          L         - Indutância por unidade de comprimento [H/m]
    #          frequencia - Freq. de operação da linha [Hz]
    #          G          - Condutância por unidade de comprimento [S/m]
    #          C          - Capacitancia por unidade de comprimento [F/m]
    #  Saida:
    #          Zo          - Impedância caracteristica Zo da linha [Ohm]
    
    meiow = np.pi*frequencia
    N = R + 2j*meiow*L
    D = G + 2j*meiow*C
    div = N/D
    Zo =  (div)**0.5
    return Zo

def Constante_propagacao(R, L, G, C, frequencia): 
    #      Constante de propagação
    #
    #  Entrada:
    #          R         - Resistência por unidade de comprimento [Ohm/m]
    #          L         - Indutância por unidade de comprimento [H/m]
    #          frequencia - Freq. de operação da linha [Hz]
    #          G          - Condutância por unidade de comprimento [S/m]
    #          C          - Capacitancia por unidade de comprimento [F/m]
    #  Saida:
    #          Y          - Constante de propagação [1/m]
    
    meiow = np.pi*frequencia
    termo1 = R + 2j*meiow*L
    termo2 = G + 2j*meiow*C
    mult = termo1*termo2
    Y =  (mult)**0.5
    return Y
   

def Velocidade_onda(frequencia, B):
    #      Velocidade da onda
    #
    #  Entrada:
    #          frequencia - Freq. de operação da linha [Hz]
    #          B          - Constante de fase [rad/m]
    #  Saida:
    #          u          - Impedância caracteristica Zo da linha [m/s]
    w = 2*np.pi*frequencia
    u = w/B
    return u

def Coeficiente_reflexao_tensao(Zc, Zo):
    #      Coeficiente de reflexão da tensão
    #
    #  Entrada:
    #          Zo          - Impedância caracteristica Zo da linha [Ohm]
    #          Zc          - Impedância da carga [Ohm]
    #  Saida:
    #          T          - Coeficiente de reflexão da tensão
    N = Zc - Zo
    D = Zc + Zo
    Tc = N/D
    return Tc

def Relacao_onda_estacionaria(Tc):
    #      Relação de onda estacionária
    #
    #  Entrada:
    #          T          - Coeficiente de reflexão da tensão
    #  Saida:
    #          s          - Relação de onda estacionária
    N = 1 + abs(Tc)
    D = 1 - abs(Tc)
    s = N/D
    return s

def Impedancia_entrada_ComPerdas(Zc, Zo, Y, l):
    #      Impedancia de entrada linhas com perdas
    #
    #  Entrada:
    #          Zo          - Impedância caracteristica Zo da linha [Ohm]
    #          Zc          - Impedância da carga [Ohm]
    #          Y          - Constante de propagação [1/m]
    #          l          - Comprimento [m]
    #  Saida:
    #          Zent          - Impedancia de entrada
    N = Zc + Zo*cmath.tanh(Y*l)
    D = Zo + Zc*cmath.tanh(Y*l)
    div = N/D
    Zent = Zo*div
    return Zent

def Impedancia_entrada_SemPerdas(Zc, Zo, Bl):
    #      Impedancia de entrada linhas com perdas
    #
    #  Entrada:
    #          Zo          - Impedância caracteristica Zo da linha [Ohm]
    #          Zc          - Impedância da carga [Ohm]
    #          B          - Constante de fase [rad/m]
    #          l          - Comprimento [m]
    #  Saida:
    #          Zent          - Impedancia de entrada
    j = 1j 
    N = Zc + j*Zo*math.tan(Bl)
    D = Zo + j*Zc*math.tan(Bl)
    div = N/D
    Zent = Zo*div
    return Zent
    
# -----------------------------------------------------------------------------

'''
#Questão 11.5
R = 40
G = 400E-6
L = 0.2E-6
C = 0.5E-9
f = 10E6

Zo = Impedancia_Caracteristica(R, L, G, C, f)
Y = Constante_propagacao(R, L, G, C, f)
u = Velocidade_onda(f, Y.imag)
l = 30/(Y.real*8.686)
print('Zo: ', Zo, '\n', 'u: ', u, '\n', 'l: ', l, '\n')

#Questão 11.16
Zo = 65 + 38j 
Y = 0.7 + 2.5J
l = 0.8

Zent = Zo*cmath.tanh(Y*l)
print('Zent: ',Zent)

#Questão 11.17
Zo = 50
Zc = 120
Bl = 60

Tc = Coeficiente_reflexao_tensao(Zc, Zo)
s = Relacao_onda_estacionaria(Tc)
Zent = Impedancia_entrada_SemPerdas(Zc, Zo, Bl)
print('Tc: ', Tc, '\n s: ', s, '\nZent: ', Zent)

#Questão 11.22
ZcC = 60 -35j
ZoC = 75
BlC = np.pi
ZentC = Impedancia_entrada_SemPerdas(ZcC, ZoC, BlC)

ZoB = 100
ZcB = ZentC
BlB = 90*(np.pi/180)
ZentB = Impedancia_entrada_SemPerdas(ZcB, ZoB, BlB)

ZoA = 50
ZcA = ZentB
BlA = (5*np.pi)/4
ZentA = Impedancia_entrada_SemPerdas(ZcA, ZoA, BlA)

print('\nZentC: ', ZentC, '\nZentB: ', ZentB, '\nZentA: ', ZentA)

#Questão 11.24
N = 2*np.pi*300E106
D = 0.8*3*10E8
B = N/D
l = 4.2/2
Bl = B*l
Zo = 50
Zc = 80 - 60j

Zent = Impedancia_entrada_SemPerdas(Zc, Zo, Bl)
Tc = Coeficiente_reflexao_tensao(Zc, Zo)

print('\nZent: ', Zent, '\nTc: ', Tc)

#Questão 11.34 
Vs = 2 + 1j
Is = 10E-3
Zo = 75
Bl = 0.4*np.pi
Zent = Vs/Is
Z = Zent/Zo
Zc = 75/Z

Tc = Coeficiente_reflexao_tensao(Zc, Zo)
s = Relacao_onda_estacionaria(Tc)

print('\nZent: ', Zent, '\nZ: ', Z, '\nZc: ', Zc, '\ns: ', s)

#Questão 11.35
Zo = 50
Zc = 75
Zo2 = 30
Bl2 = np.pi/2
div = (Zo/Zc)**0.5
#Zo1 = Zo2*div

Zo1 = (Zc*(Zo**3))**(1/4)
Zo2 = (Zo1*(Zc**2))**(1/3)

print('\nZo1: ', Zo1, '\nZo2: ', Zo2)
'''