<p align="center">
  <a href="https://github.com/luizfelmach/ardudino">
    <img width="200px" alt="ardudino" src="./assets/banner.png">
  </a>
</p>

<div align="center">

  ![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
  ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)

</div>


## Conteúdo
- [Conteúdo](#conteúdo)
- [Resumo](#resumo)
- [Descrição](#descrição)
- [Como compilar](#como-compilar)
- [Detalhes](#detalhes)
- [Componentes](#componentes)
- [Circuito](#circuito)
- [Resultado](#resultado)
- [Autores](#autores)

## Resumo

O projeto consiste em um **mini emulador** de jogo controlado por um Arduino. O Arduino irá controlar uma tela OLED I2C no qual conterá um jogo baseado no Dino do navegador Chrome (T-Rex Running).

## Descrição

No jogo, você controla o Dinossauro e o seu objetivo é sobreviver por mais tempo e não encostar nos cactos plantados e nem nos passaros que estão voando e indo em sua direção. Para isso, é necessário fazer um movimento para baixo, para fugir dos passáros e um movimento para cima, para pular dos cactos.

O acelerometro pega esses movimentos e envia para o Arduino por meio de conexão I2C. Este é responsavel por fazer toda a lógica do jogo funcionar, processando as informações recebidas, ele também manda por conexão I2C o que deve aparecer na tela do display OLED que é o visor do jogo e mostra o dinossauro, os objetos vindo em sua direção e a pontuação da sua partida.

O jogo ainda contém uma tela de final do jogo que a parece quando você encosta em um cacto ou passaro e perde o jogo. Para iniciar uma nova partida, fazer um movimento para a lateral.

## Como compilar

O projeto foi inteiramente construído utilizando [PlatformIO](https://platformio.org/). Para utilizar, faça [download](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) da extensão para o vscode. O PlaformIO, a partir do arquivo de configuração ***platformio.ini***, faz a instalação das dependências necessárias para compilar. 

```toml
; platformio.ini

[env:uno]
platform = "atmelavr"
board = "uno"
framework = "arduino"
lib_deps = "olikraus/U8glib@^1.19.1" ; dependência necessária
```

Com tudo configurado, basta clicar no botão **build** do platformIO e fazer o **upload** para o Arduino.

## Detalhes

Para desenvolver esse projeto, ele foi modurarizado da seguinte forma:

```
|--lib
|  |
|  |--acelerometro
|  |  |- acelerometro.cpp
|  |  |- acelerometro.hpp
|  |
|  |--bitmaps
|  |  |- bitmaps.cpp
|  |  |- bitmaps.hpp
|  |
|  |--cacto
|  |  |- cacto.cpp
|  |  |- cacto.hpp
|  |
|  |--chao
|  |  |- chao.cpp
|  |  |- chao.hpp
|  |
|  |--constantes
|  |  |- constantes.hpp
|  |
|  |--dino
|  |  |- dino.cpp
|  |  |- dino.hpp
|  |
|  |--jogo
|  |  |- jogo.cpp
|  |  |- jogo.hpp
|  |
|  |--passaro
|  |  |- passaro.cpp
|  |  |- passaro.hpp
| 
|- platformio.ini
|--src
   |- main.c
```

## Componentes

- Display i2c (Tela Oled 1.3’’ 128x64)
- Arduino Uno
- Acelerômetro (MPU)

## Circuito

<p align="center">
  <img width="500px" src="./assets/schematic.png" />
</p>

## Resultado

<div align="center">

  [![ardudino](https://img.youtube.com/vi/EXHThd38dGE/0.jpg)](https://youtu.be/EXHThd38dGE)

</div>

## Autores

- **[@luizfelmach](https://github.com/luizfelmach)**
- **[@gabriellybc](https://github.com/gabriellybc)**
- **[@carpesfelipe](https://github.com/carpesfelipe)**
