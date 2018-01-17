/* 
 Madrid, 21 de febrero de 2017.
 Autores: Carlos Luis Hojas García-Plaza y Rafael Hidalgo Alejo. Pareja 02.
 PROGRAMACIÓN II - ESCUELA POLITÉCNICA SUPERIOR DE LA UNIVERSIDAD AUTÓNOMA DE MADRID
 PRÁCTICA 1 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "types.h"
#define DIM 100

//Presentamos la estructura de un nodo, que constará de una cadena de caracteres donde se almacenará su nombre y de un entero para guardar su ID.

struct _Node {
    char name[DIM];
    int id;
};

//Inicializamos un nodo con esta función, esto es, le damos memoria dinámica con malloc.

Node * node_ini() {
    //Manera alternativa, más larga:
    /*Node *n=(Node*)malloc(sizeof(Node));
    if(n==NULL){
        return NULL;
    }
     return n;
     */

    return (Node*) malloc(sizeof (Node));
}

//Función que se encarga de liberar un nodo.

void node_destroy(Node * n) {
    if (n == NULL) return;
    free(n);
}

//Nos proporiona el ID de un nodo dado.

int node_getId(const Node * n) {
    int id;
    if (n == NULL) {
        return -1;
    }
    id = n->id;

    return id;
}

//Nos proporciona el nombre de un nodo. Para ello, lo copiamos en una cadena de caracteres (name) a la que damos memoria dinámica y la devolvemos.

char* node_getName(const Node * n) {
    char *name = NULL;
    if (n == NULL) return NULL;
    name = (char*) malloc(50 * sizeof (char));
    strcpy(name, n->name);

    return name;
}

//Añade el nombre a un nodo. Utilizamos la función strcpy para copiar lo introducido como argumento al nombre del nodo.

Node *node_setName(Node * n, const char* name) {
    if (name == NULL || n == NULL) return NULL;

    strcpy(n->name, name);

    return n;
}

//Añade un ID a un nodo.

Node * node_setId(Node * n, const int id) {
    if (n == NULL) {
        return NULL;
    }
    n->id = id;
    return n;
}

//Nos devuelve TRUE si dos nodos son iguales y FALSE si son distintos. Para eso, comparamos sus id's y sus nombres.

Bool node_equals(const Node * n1, const Node * n2) {
    if (n1 == NULL || n2 == NULL) {
        return FALSE;
    }
    if ((n1->id == n2->id) && (!strcmp(n1->name, n2->name))) return TRUE;
    return FALSE;
}

//Función que se encarga de copiar un nodo determinado. Para ello, creamos e inicializamos un segundo nodo y copiamos los parámetros del primero en el segundo.

Node * node_copy(const Node * src) {
    Node *n2 = NULL;
    if (src == NULL) return NULL;
    n2 = node_ini();
    n2->id = src->id;
    strcpy(n2->name, src->name);
    return n2;
}

//Imprime un nodo en un fichero, esto es, su ID y su nombre, y nos devuelve el número de caracteres que han sido escritos.

int node_print(FILE *pf, const Node * n) {
    int c;
    if (pf == NULL || n == NULL) {
        return 0;
    }

    c = fprintf(pf, "[%d, %s]", n->id, n->name);

    return c;
}
//FIN