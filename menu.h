#ifndef MENU
#define MENU

#include "trie.h"

void limpiarPantalla();
void mostrarAyuda();
void buscarPalabra(Node* trie);
void buscarPalabraPorPrefijo(Node *trie);
void cargarDiccionario(Node** trie);
#endif
