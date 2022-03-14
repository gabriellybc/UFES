O script de teste funciona somente em ambientes Linux/MacOS.

Para os usuários do Windows 10, recomenda-se o uso do WSL (ver "Etapas da instalação manual" em https://docs.microsoft.com/pt-br/windows/wsl/install-win10)

Para obter e executar o script, siga os passos abaixo:

1. Abra um terminal, acesse esta pasta;
2. Execute o script: ./test.sh

O script reconhece trabalhos se forem colocados em pastas sob o mesmo diretório em que se encontra o script test.sh e se os trabalhos seguirem as instruções contidas a seguir. Note que há já uma pasta chamada "testes", que contém os arquivos de teste executados pelo script. O script já é configurado a não considerar esta pasta como uma pasta de trabalho.

O script compara a saída padrão gerada pelo trabalho do aluno com o arquivo de saída gerado pela implementação do professor. Quando diferenças são encontradas, as mesmas são mostradas na tela e implicam perda de pontos na correção automática. O aluno deve, portanto, tentar reduzir o número de diferenças ao máximo possível antes de entregar o trabalho.

Para testar o seu trabalho, crie uma pasta com um nome qualquer dentro do mesmo diretório em que se encontra o script test.sh e copie seu código-fonte para esta pasta. Além do código-fonte, crie um arquivo de build.xml do Apache Ant (http://ant.apache.org) que indique como compilar e executar seu programa, seguindo as instruções na definição do trabalho.

