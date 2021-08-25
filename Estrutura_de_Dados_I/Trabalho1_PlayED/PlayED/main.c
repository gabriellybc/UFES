//
// Testador de PlayED
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 02/08/21.
//

#include <stdio.h>
#include "listaPessoa.h"

int main()
{
  ListaMusica *todasMusicas = inicListaMusica();
  ListaPessoa *pessoas = inicListaPessoa();

  lePessoas(pessoas);

  lePlaylists(pessoas);

  defineTodosPlaylists(pessoas, todasMusicas);

  defineAmizades(pessoas);

  reInicListaPlaylistTodos(pessoas);

  refatoraTodos(pessoas);

  // Tire o comentario abaixo para fazer o 'merge' das playlists dos mesmos cantores/bandas entre amigos

  //mergeListaPessoa(pessoas);

  Similaridades(pessoas);

  imprimeTodasPlaylistsNoArquivo(pessoas);

  liberaListaPessoa(pessoas, 1);

  liberaListaMusica(todasMusicas, 1);

  return 0;
}