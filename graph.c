/* 
 Madrid, 21 de febrero de 2017.
 Autores: Carlos Luis Hojas García-Plaza y Rafael Hidalgo Alejo. Pareja 02.
 PROGRAMACIÓN II - ESCUELA POLITÉCNICA SUPERIOR DE LA UNIVERSIDAD AUTÓNOMA DE MADRID
 PRÁCTICA 1 
 */

//Observación importante: A lo largo del código se utilizan sentencias para comprobar posibles errores y que no serán comentadas.

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Presentamos la estructura del grafo, que incluirá una matriz de enteros que representarán las aristas entre nodos, un doble puntero a los nodos que tendrá 
//el grafo y dos variables de tipo que entero que representarán el número de aristas (naristas) y el número de nodos (nnodos)

struct _Graph {
    int matrizAdy[MAX_NODES][MAX_NODES];
    Node **nodosSaved;
    int naristas;
    int nnodos;
};
//La siguiente función nos inicializa un grafo y funciona de la siguiente manera: crea un puntero a grafo y dos variables auxiliares que nos servirán para los bucles.
//A continuación reserva memoria necesaria para dicho grafo y para los punteros a nodos que contendrá el mismo. También, y como es lógico, inicializa la matriz de adyacencia 
//y el número de nodos y aristas a 0.

Graph * graph_ini() {
    Graph *g;
    int i, j;
    g = (Graph *) malloc(sizeof (Graph));
    if (g == NULL)return NULL;
    g->nodosSaved = (Node **) malloc(MAX_NODES * sizeof (Node*));
    if (g->nodosSaved == NULL) {
        free(g);
        return NULL;
    }
    for (i = 0; i < g->nnodos; i++) {
        for (j = 0; j < g->nnodos; j++) {
            g->matrizAdy[i][j] == 0;
        }
    }
    g->nnodos = 0;
    g->naristas = 0;

    return g;
}
// Libera un grafo. Para ello, libera primero los nodos que están contenidos en él y más tarde el propio grafo.

void graph_destroy(Graph *g) {
    int i;
    if (g == NULL)return;
    for (i = 0; i < g->nnodos; i++) {
        node_destroy(g->nodosSaved[i]);
    }
    free(g);
}
//Nos devuelve el número de nodos que posee un grafo.

int graph_getNnodes(const Graph * g) {
    if (g == NULL)return -1;
    return g->nnodos;
}

int* graph_getNodeIds(const Graph * g) {
    int *ids, i;
    if (g == NULL)return NULL;
    ids = (int*) malloc(g->nnodos * sizeof (int)); //crea memoria con la cantidad de nodos que tengo en el grafo.
    if (ids == NULL)return NULL;
    for (i = 0; i < g->nnodos; i++) {
        ids[i] = node_getId(g->nodosSaved[i]); //guarda en la lista de ids los ids de los nodos almacenados en el grafo.
    }
    return ids;

}
//Nos devuelve el número de aristas o enlaces que posee un grafo.

int graph_getNedges(const Graph * g) {
    if (g == NULL)return -1;
    return g->naristas;
}
//Esta función añade un nodo al grafo. Para ello, crea una copia del nodo pasado como argumento y lo "coloca" en la última posición, que estará representada por la variable nnodos.

Graph * graph_addNode(Graph * g, const Node* n) {
    if (g == NULL || n == NULL)return NULL;

    g->nodosSaved[g->nnodos] = node_copy(n);
    if (g->nodosSaved[g->nnodos] == NULL) return NULL;
    g->nnodos++;

    return g;
}
//Función privada que nos devuelve el índice del nodo que posee un ID determinado. Para ello, utilizamos un bucle for que recorre la lista de nodos.

int find_node_index(const Graph * g, int nId1) {
    int i;
    if (g == NULL)return -1;
    for (i = 0; i < g->nnodos; i++) {
        if (node_getId(g->nodosSaved[i]) == nId1) {
            return i;
        }
    }
    return -1;
}
//Añade una conexión entre dos nodos de un grafo, devolviendo NULL en caso de error y el propio grafo actualizado si todo es correcto. Utilizaremos la función
//privada implementada anteriormente. Si no hay arista entre ellos, le suma uno a naristas y coloca el enlace (un 1 en la matriz de ady.)

Graph * graph_addEdge(Graph * g, const int nId1, const int nId2) {
    int i, j;
    if (g == NULL)return NULL;
    i = find_node_index(g, nId1);
    j = find_node_index(g, nId2);
    if (g->matrizAdy[i][j] == 0) {
        g->naristas++;
    }
    g->matrizAdy[i][j] = 1;
    return g;
}
//Devuelve un puntero a la estructura Node almacenada en el grafo tal que dicho nodo tiene como id nId. Si no se encuentra o hay algún error, se devuelve NULL

Node * graph_getNode(const Graph * g, int nId) {
    int i;
    if (g == NULL)return NULL;
    for (i = 0; i < g->nnodos; i++) {
        if (nId == node_getId(g->nodosSaved[i])) {
            return g->nodosSaved[i];
        }
    }
    return NULL;
}
//Función que nos devuelve TRUE or FALSE en función de si dos nodos de un grafo están conectados. Utilizamos la función privada y comprobamos en la matriz de ady.

Bool graph_areConnected(const Graph * g, const int nId1, const int nId2) {
    int i, j;
    if (g == NULL)return FALSE;
    i = find_node_index(g, nId1);
    j = find_node_index(g, nId2);
    if (g->matrizAdy[i][j] == 1)return TRUE;
    return FALSE;
}
//Devuelve el número de conexiones que se conocen en el grafo desde un nodo, si hay algún error devuelve -1 

int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId) {
    int i, j, k = 0;
    if (g == NULL)return -1;
    i = find_node_index(g, fromId);
    for (j = 0; j < MAX_NODES; j++) {
        if (g->matrizAdy[j][i] == 1) {
            k++;
        }
    }
    return k;

}
//Devuelve una lista de enteros que se conocen en el grafo desde un nodo, utilizando la función privada que nos devuelve el índice del nodo, y si hay algún error devuelve -1

int* graph_getConnectionsFrom(const Graph * g, const int fromId) {
    int i, j, k = 0, *ids = NULL;
    if (g == NULL)return NULL;
    ids = (int*) malloc(MAX_NODES * sizeof (int));
    i = find_node_index(g, fromId);
    for (j = 0; j < MAX_NODES; j++) {
        if (g->matrizAdy[j][i] == 1) {
            ids[k] = node_getId(g->nodosSaved[j]);
            k++;
        }
    }
    return ids;
}

//Devuelve el número de conexiones que se conocen en el grafo hacia un nodo, utilizando la función privada que nos devuelve el índice del nodo, y si hay algún error devuelve -1 

int graph_getNumberOfConnectionsTo(const Graph * g, const int toId) {
    int i, j, k = 0;
    if (g == NULL)return -1;
    i = find_node_index(g, toId);
    for (j = 0; j < MAX_NODES; j++) {
        if (g->matrizAdy[i][j] == 1) {
            k++;
        }
    }
    return k;
}
//Devuelve una lista (int *ids) con los ids de los nodos conectados desde un nodo dado, si hay algún error devuelve NULL. Reservamos memoria dinámicamente para la lista de enteros.

int* graph_getConnectionsTo(const Graph * g, const int toId) {
    int i, j, k = 0, *ids = NULL;
    if (g == NULL)return NULL;
    ids = (int*) malloc(MAX_NODES * sizeof (int));
    i = find_node_index(g, toId);
    for (j = 0; j < MAX_NODES; j++) {
        if (g->matrizAdy[i][j] == 1) {
            ids[k] = node_getId(g->nodosSaved[j]);
            k++;
        }
    }
    return ids;
}
//Utilizamos la variable entera c que actúa como contador de caracteres; la i,j como auxiliares para los bucles. Vamos incrementando c en función de los caracteres escritos e imprimiendo en el 
//fichero los datos pedidos.

int graph_print(FILE *pf, const Graph * g) {
    int c = 0, i, j;
    if (g == NULL) {
        return 0;
    }
    if (pf == NULL) {
        printf("Error abriendo el archivo.");
        return 1;
    }
    fprintf(pf, "N=%d, E=%d:\n", g->nnodos, g->naristas);
    for (i = 0; i < g->nnodos; i++) {
        c += fprintf(pf, "[%d, %s]", node_getId(g->nodosSaved[i]), node_getName(g->nodosSaved[i]));
        c += fprintf(pf, "->");
        for (j = 0; j < g->nnodos; j++) {

            c += fprintf(pf, "%d ", g->matrizAdy[i][j]);
        }
        c += fprintf(pf, "\n");
    }
    return c;
}
//FIN