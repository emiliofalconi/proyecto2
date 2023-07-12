#include "menu.h"
#include "trie.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void minusculas(char *str) {
  /*
   * Convierte una cadena de caracteres a minúsculas.
   *
   * Parámetros:
   *     - str: Puntero a la cadena de caracteres a convertir.
   */
  for (int i = 0; str[i] != '\0'; i++) {
    str[i] = tolower(str[i]);
  }
}

void limpiarPantalla() {
  /*
   * Limpia la pantalla y muestra el menú iterativo.
   */
  printf("\033[2J\033[H");
  printf("Menu Iterativo: \n");
  printf("[h] Ayuda || [l] Cargar archivo || [s] Palabra || [p] Prefijo || [q] "
         "Salir\n\n");
}

void mostrarAyuda() {
  /*
   * Muestra la guía de uso del programa.
   */
  limpiarPantalla();
  printf("Uso: programa.c\n");
  printf("[h] Ayuda:\n");
  printf("    Muestra esta guia de uso.\n");
  printf("[l] Cargar archivo:\n");
  printf("    Permite cargar el archivo de texto.\n");
  printf("[s] Palabra:\n");
  printf("    Busca una palabra en el diccionario.\n");
  printf("[p] Prefijo:\n");
  printf("    Buscar todas las palabras que empiecen con.\n");
  printf("[q] Salir:\n");
  printf("    Permite salir del programa.\n");
}

void buscarPalabra(Node *trie) {
  /*
   * Busca una palabra en el diccionario.
   *
   * Parámetros:
   *     - trie: Puntero al nodo raíz del trie que representa el diccionario.
   */
  limpiarPantalla();
  char palabra[200];
  printf("Palabra a buscar: ");
  scanf("%s", palabra);
  minusculas(palabra);

  char *significado = buscarSignificado(trie, palabra);
  if (strcmp(significado, "") != 0) {
    printf("• %s\n    %s\n\n", palabra, significado);
  } else {
    printf("Palabra no encontrada en el diccionario\n");
  }
}

void buscarPalabraPorPrefijo(Node *trie) {
  /*
   * Busca todas las palabras que empiezan con un prefijo dado.
   *
   * Parámetros:
   *     - trie: Puntero al nodo raíz del trie que representa el diccionario.
   */
  limpiarPantalla();
  char palabra[200];
  printf("Prefijo por el cual buscar: ");
  scanf("%s", palabra);
  minusculas(palabra);
  buscarPorPrefijo(trie, palabra);
}

void cargarDiccionario(Node **trie) {
  /*
   * Carga el diccionario desde un archivo de texto.
   *
   * Parámetros:
   *     - trie: Doble puntero al nodo raíz del trie que representa el
   * diccionario.
   */
  limpiarPantalla();
  char archivo[100];
  printf("Ingrese el nombre del archivo: ");
  scanf("%s", archivo);
  crearDiccionario(trie, archivo);
  printf("El archivo ha sido cargado con exito!.\n");
}
