// Representar um grafo orientado e pesado através da definição de 
// uma lista ligada de listas ligadas

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 50

typedef struct registo3
{ int codigo;
  struct registo3 * seguinte;
} * Meios;

// Representação de um grafo orientado e pesado
typedef struct registo2
{char vertice[TAM]; // geocódigo what3words
 float peso;
 struct registo2 * seguinte;
} * Adjacente;

typedef struct registo1
{char vertice[TAM]; // geocódigo what3words
 Adjacente adjacentes;
 Meios meios; // Lista ligada com os códigos dos meios de transporte existente
	      // neste geocódigo
 struct registo1 * seguinte;
} * Grafo;

// Protótipos

// Criar um novo vértice
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarVertice(Grafo *g, char novoId[]);
// Criar uma nova aresta
// Devolve 1 em caso de sucesso ou 0 caso contrário
Grafo criarAresta(Grafo g, char vOrigem[], char vDestino[], float peso);
int existeVertice(Grafo g, char vertice[]);
void listarAdjacentes(Grafo g, char vertice[]);
// Inserir meio de transporte na localização com geocódigo passado por parâmetro
int inserirMeio(Grafo g, char geocodigo[], int codigoMeio);
// Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro
void listarMeios(Grafo g, char geocodigo[]);

Grafo encontrarVerticePorIndice(Grafo g, unsigned int indice);

void copiarVerticesInvertido(Grafo* destino, Grafo origem);

int encontrarIndiceVertice(Grafo g, char* geocode);

int encontrarIndiceAdjacente(Adjacente adj, char* geocode);

