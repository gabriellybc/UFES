#include "Funcoes.h"

void menu()
{
    cout << "...MENU PRINCIPAL..." << endl << endl;
    cout << "Escolha uma das opções:" << endl << endl;
    cout << "- Opções de rede social:" << endl;
    cout << "   1. Criar novo usuário" << endl;
    cout << "   2. Criar novo grupo" << endl;
    cout << "   3. Excluir grupo" << endl;
    cout << "   4. Imprimir todos os aniversariantes do mês" << endl;
    cout << "   5. Imprimir todos os usuários cadastrados" << endl;
    cout << "   6. Imprimir todos os grupos cadastrados" << endl;
    cout << "   7. Imprimir todos os grupos cadastrados por categoria" << endl;
    cout << "   8. Imprimir todas as publicações cadastradas" << endl << endl;
    cout << "- Opções de grupo:" << endl;
    cout << "   9. Adicionar participante" << endl;
    cout << "   10. Remover participante" << endl;
    cout << "   11. Imprimir participantes" << endl << endl;
    cout << "- Opções de usuário:" << endl;
    cout << "   12. Seguir usuário" << endl;
    cout << "   13. Deixar de seguir usuário" << endl;
    cout << "   14. Criar publicação" << endl;
    cout << "   15. Editar publicação" << endl;
    cout << "   16. Excluir publicação" << endl;
    cout << "   17. Imprimir publicações" << endl;
    cout << "   18. Imprimir seguidores" << endl << endl;
    cout << "- Opções de sistema:" << endl;
    cout << "   19. Imprimir quantidade de usuários cadastrados nas três redes sociais" << endl;
    cout << "   20. Salvar dados" << endl;
    cout << "   21. Carregar Dados" << endl;
    cout << "   22. Exportar Biblioteca" << endl;
    cout << "   23. Sair" << endl;
}
int selecionaRedeSocial (vector <RedeSocial*> redesSociais)
{
    int i;
    do
    {
        cout << "Escolha uma das redes sociais: " << endl;
        for(i=0; i<redesSociais.size(); i++)
        {
            cout<< "Rede Social " << i << ":" << endl;
            cout << redesSociais[i]->nome << endl;
            cout << endl;
        }
        cin >> i;
        cout << endl;
    }
    while (i<0 || i>= redesSociais.size());
    return i;
}
