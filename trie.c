#include "trie.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *crearNodo() {
  /*
   * Crea un nuevo nodo del Trie.
   *
   * Retorna:
   *     - Puntero al nodo creado.
   */
  Node *node = NULL;

  node = (Node *)malloc(sizeof(Node));
  if (node == NULL) {
    printf("No se pudo crear el Trie\n");
  }
  node->finalDePalabra = 0;
  for (int i = 0; i < 26; i++) {
    node->children[i] = NULL;
  }
  return node;
}

void insertar(Node **trie, const char *palabra, const char *significado) {
  /*
   * Inserta una palabra y su significado en el Trie.
   *
   * Parámetros:
   *     - trie: Doble puntero al nodo raíz del Trie.
   *     - palabra: Puntero a la cadena de caracteres que representa la palabra.
   *     - significado: Puntero a la cadena de caracteres que representa el
   * significado de la palabra.
   */
  if (trie == NULL || *trie == NULL) {
    *trie = crearNodo();
  }

  Node *temp = *trie;
  int len = strlen(palabra);
  for (int i = 0; i < len; i++) {
    int index = palabra[i] - 'a';
    if (temp->children[index] == NULL) {
      temp->children[index] = crearNodo();
    }

    temp = temp->children[index];
  }
  temp->finalDePalabra = 1;
  strcpy(temp->significado, significado);
}

char *buscarSignificado(Node *trie, const char *palabra) {
  /*
   * Obtiene el significado de una palabra en el Trie.
   *
   * Parámetros:
   *     - trie: Puntero al nodo raíz del Trie.
   *     - palabra: Puntero a la cadena de caracteres que representa la palabra
   * a buscar.
   *
   * Retorna:
   *     - Puntero a la cadena de caracteres que representa el significado de la
   * palabra.
   */
  if (trie == NULL) {
    return "";
  }

  Node *temp = trie;
  int len = strlen(palabra);
  for (int i = 0; i < len; i++) {
    int index = palabra[i] - 'a';
    temp = temp->children[index];

    if (temp == NULL) {
      return "";
    }
  }

  if (temp->finalDePalabra) {
    return temp->significado;
  }
  return "";
}

void imprimirPalabrasConPrefijo(Node *trie, const char *prefijo) {
  /*
   * Imprime todas las palabras del Trie que tienen un prefijo dado.
   *
   * Parámetros:
   *     - trie: Puntero al nodo raíz del Trie.
   *     - prefijo: Puntero a la cadena de caracteres que representa el prefijo
   *       a buscar.
   */
  if (trie == NULL) {
    return;
  }
  if (trie->finalDePalabra) {
    printf("%s: %s\n", prefijo, trie->significado);
  }
  for (int i = 0; i < 26; i++) {
    if (trie->children[i] != NULL) {
      char letra = 'a' + i;
      char *nuevoPrefijo = (char *)malloc((strlen(prefijo) + 2) * sizeof(char));
      sprintf(nuevoPrefijo, "%s%c", prefijo, letra);
      imprimirPalabrasConPrefijo(trie->children[i], nuevoPrefijo);
      free(nuevoPrefijo);
    }
  }
}

void buscarPorPrefijo(Node *trie, const char *prefijo) {
  /*
   * Busca todas las palabras del Trie que tienen un prefijo dado y las imprime.
   *
   * Parámetros:
   *     - trie: Puntero al nodo raíz del Trie.
   *     - prefijo: Puntero a la cadena de caracteres que representa el prefijo
   * a buscar.
   */
  Node *temp = trie;
  int len = strlen(prefijo);

  for (int i = 0; i < len; i++) {
    int indice = prefijo[i] - 'a';
    if (temp->children[indice] == NULL) {
      printf("No se han encontrado palabras con el prefijo '%s'\n", prefijo);
      return;
    }
    temp = temp->children[indice];
  }
  imprimirPalabrasConPrefijo(temp, (char *)prefijo);
}

void crearDiccionario(Node **trie, const char *filename) {
  /*
   * Crea un diccionario a partir de un archivo de texto.
   *
   * Parámetros:
   *     - trie: Doble puntero al nodo raíz del Trie.
   *     - filename: Puntero a la cadena de caracteres que representa el nombre
   * del archivo de texto.
   */
  FILE *archivo = fopen(filename, "r");
  if (archivo == NULL) {
    printf("No se pudo abrir el archivo.\n");
    return;
  }

  int isFirstLine = 1;
  char line[600];
  char palabra[200];
  char significado[400];
  while (fgets(line, sizeof(line), archivo)) {
    if (line[0] == '+') {
      // Concatena la linea si es parte de la definicion anterior
      strncat(significado, line + 1, strlen(line) - 2);
    } else {
      if (!isFirstLine) {
        // Insertar la palabra anterior junto a su definicion
        insertar(trie, palabra, significado);
        memset(significado, 0, sizeof(significado));
      }

      // Dividir la palabra y su definicion
      sscanf(line, "%s %[^\n]", palabra, significado);
      isFirstLine = 0;
    }
  }
  insertar(trie, palabra, significado);
  fclose(archivo);
}

void printTrie(Node *trie, char *buffer, int depth) {
  /*
   * Imprime todas las palabras y sus significados almacenados en el Trie.
   * con el objetivo de debuggear.
   *
   * Parámetros:
   *     - trie: Puntero al nodo raíz del Trie.
   *     - buffer: Puntero al buffer de caracteres utilizado para almacenar
   * temporalmente las palabras durante la recursión.
   *     - depth: Entero que representa la profundidad actual en la recursión.
   */

  if (trie == NULL) {
    printf("Trie no proporcionado\n");
    return;
  }

  if (trie->finalDePalabra) {
    buffer[depth] = '\0';
    printf("Palabra %s, Significado %s\n", buffer, trie->significado);
  }

  for (int i = 0; i < 26; i++) {
    if (trie->children[i] != NULL) {
      buffer[depth] = 'a' + i;
      printTrie(trie->children[i], buffer, depth + 1);
    }
  }
}

void printT(Node *trie) {
  char buffer[100];
  printTrie(trie, buffer, 0);
}
