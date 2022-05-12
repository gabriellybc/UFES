#include <iostream>
#include <string>
#include "Leitura.h"
#include "Eleicao.h"

using namespace std;

int main(const int argc, const char *argv[])
{
    Leitura leitura;
    Eleicao eleicao;

    leitura.run(argc, argv, eleicao);
    
    return 0;
}