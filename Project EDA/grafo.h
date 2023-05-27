#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Max size of a geocode */
#define TAM 100

/** @struct registo3
* @brief This data structure holds the list of transports presents in a location
*
* @var registo3::codigo
* Member 'vertice' contains the id of the transport present in the vertex
*
* @var registo3::seguinte
* Member 'seguinte' contains the memmory address of the next transport */
typedef struct registo3
{ int codigo;
  struct registo3 * seguinte;
} * Meios;

/** @struct registo2
* @brief This data structure holds the list of adjacents
*
* @var registo2::vertice
* Member 'vertice' contains the geocode of adjacent vertex

* @var registo2::peso
* Member 'peso' contains the distance to the adjacent vertex
*
* @var registo2::seguinte
* Member 'seguinte' contains the memmory address of the next adjacent */
typedef struct registo2
{char vertice[TAM];
 float peso;
 struct registo2 * seguinte;
} * Adjacente;

/** @struct registo1
* @brief Graph data structure that represents the map
*
* @var registo1::vertice
* Member 'vertice' contains the geocode of the location that the vertex represents

* @var registo1::adjacentes
* Member 'adjacentes' contains a list of adjacent vertices
*
* @var registo1::meios
* Member 'meios' contains a list of transports presents in the location
*
* @var registo1::final_rent_time
* Member 'final_rent_time' contains the time that the rental finished
*
* @var registo1::seguinte
* Member 'seguinte' contains the memmory address of the next vertex */
typedef struct registo1
{char vertice[TAM];
 Adjacente adjacentes;
 Meios meios;
 struct registo1 * seguinte;
} * Grafo;

// Criar um novo vértice
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarVertice(Grafo *g, char novoId[]);

// Criar uma nova aresta
// Devolve 1 em caso de sucesso ou 0 caso contrário
Grafo criarAresta(Grafo g, char vOrigem[], char vDestino[], float peso);

// Verifica se vertice existe
// Devolve 1 caso exista ou 0 caso contrário
int existeVertice(Grafo g, char vertice[]);

// Listar os vértices adjacentes 
void listarAdjacentes(Grafo g, char vertice[]);

// Inserir meio de transporte na localização com geocódigo passado por parâmetro
int inserirMeio(Grafo g, char geocodigo[], int codigoMeio);

// Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro
void listarMeios(Grafo g, char geocodigo[]);

/** @brief Finds a vertex in the graph based on its index.
*
* @param g - The graph in which to search for the vertex.
* @param indice - The index of the vertex to find.
*
* @return The vertex found at the specified index, or NULL if not found. */
Grafo encontrarVerticePorIndice(Grafo g, unsigned int indice);

/** @brief Copies vertices in reverse order from the source graph to the destination graph.
*
* @param destino - The destination graph where the vertices will be copied to.
* @param origem - The source graph from which the vertices will be copied.           */
void copiarVerticesInvertido(Grafo* destino, Grafo origem);

/** @brief Finds the index of a vertex in the graph based on its geocode.
*
* @param g - The graph in which to search for the vertex.
* @param geocode - The geocode of the vertex to find.
*
* @return The index of the vertex found, or -1 if not found. */
int encontrarIndiceVertice(Grafo g, char* geocode);

/** @brief Finds the vertex in the graph based on its geocode.
*
* @param g - The graph in which to search for the vertex.
* @param geocode - The geocode of the vertex to find.
*
* @return The vertex found, or -1 if not found. */
Grafo encontrarVertice(Grafo g, char* geocode);