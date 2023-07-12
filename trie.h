#ifndef TRIE_H
#define TRIE_H

typedef struct Node {
  struct Node *children[26];
  char significado[400];
  int finalDePalabra;
} Node;

Node *crearNodo();

void insertar(Node **trie, const char *palabra, const char *significado);
char *buscarSignificado(Node *trie, const char *palabra);

void crearDiccionario(Node **trie, const char *filename);
void imprimirPalabrasConPrefijo(Node *trie, const char *prefijo);
void buscarPorPrefijo(Node *trie,const char *prefijo);
void printTrie(Node *trie, char *buffer, int depth);
void printT(Node *trie);
#endif
