#include "menu.c"
#include "trie.c"
#include <stdio.h>
#include <string.h>

int main() {

  limpiarPantalla();
  Node *trie = crearNodo();

  char opcion;

  while (opcion != 'q') {
    printf("\nOpcion: ");
    scanf(" %c", &opcion);
    switch (opcion) {
    case 'l':
      cargarDiccionario(&trie);
      getchar();
      break;
    case 's':
      buscarPalabra(trie);
      getchar();
      break;
    case 'p':
      buscarPalabraPorPrefijo(trie);
      getchar();
      break;
    case 'h':
      mostrarAyuda();
      getchar();
      break;
    case 'q':
      break;
    default:
      printf("Opcion inexistente.\n");
     break;
    }
  }
  return 0;
}
