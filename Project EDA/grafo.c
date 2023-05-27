#include "grafo.h"

// Criar um novo vértice
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarVertice(Grafo* g, char novoId[])
{
	Grafo novo = malloc(sizeof(struct registo1));

	if (novo != NULL)
	{
		strcpy(novo->vertice, novoId);
		novo->meios = NULL;
		novo->adjacentes = NULL;
		novo->seguinte = *g;
		*g = novo;
		return(1);
	}
	else return(0);
}

// Devolve 1 se o vertice existe no grafo ou 0 caso contrário
int existeVertice(Grafo g, char vertice[])
{
	while (g != NULL)
	{
		if (strcmp(g->vertice, vertice) == 0) return(1);
		else g = g->seguinte;
	}
	return(0);
}

// Criar uma nova aresta
// Devolve 1 em caso de sucesso ou 0 caso contrário
Grafo criarAresta(Grafo g, char vOrigem[], char vDestino[], float peso)
{
	Adjacente novo;
	Grafo aux = g;
	if (existeVertice(aux, vOrigem) && existeVertice(aux, vDestino))
	{
		while (strcmp(aux->vertice, vOrigem) != 0) aux = aux->seguinte;
		novo = malloc(sizeof(struct registo2));
		if (novo != NULL)
		{
			strcpy(novo->vertice, vDestino);
			novo->peso = peso;
			novo->seguinte = aux->adjacentes;
			aux->adjacentes = novo;
			return(g);
		}
		else return(0);
	}
	else return(0);
}

// Listar os vértices adjacentes 
void listarAdjacentes(Grafo g, char vertice[])
{
	Adjacente aux;
	if (existeVertice(g, vertice))
	{
		while (strcmp(g->vertice, vertice) != 0) g = g->seguinte;
		aux = g->adjacentes;
		while (aux != NULL)
		{
			printf("Adjacente:%s Peso:%.2f\n", aux->vertice, aux->peso);
			aux = aux->seguinte;
		}
	}
}

// Inserir meio de transporte na localização com geocódigo passado por parâmetro
// Devolve 1 em caso de sucesso ou 0 caso contrário
int inserirMeio(Grafo g, char geocodigo[], int codigoMeio)
{
	while ((g != NULL) && (strcmp(g->vertice, geocodigo) != 0))
		g = g->seguinte;
	if (g == NULL) return(0);
	else {
		Meios novo = malloc(sizeof(struct registo3));
		novo->codigo = codigoMeio;
		novo->seguinte = g->meios;
		g->meios = novo;
		return(1);
	}
}

// Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro
void listarMeios(Grafo g, char geocodigo[])
{
	while ((g != NULL) && (strcmp(g->vertice, geocodigo) != 0))
		g = g->seguinte;
	if (g != NULL)
	{
		Meios aux = g->meios;
		if (aux == NULL) printf("sem meios de transporte\n");
		else while (aux != NULL)
		{
			printf("Codigo meio: %d\n", aux->codigo);
			aux = aux->seguinte;
		}
	}
	else printf("geocodigo inexistente\n");
}

/** @brief Finds a vertex in the graph based on its index.
* 
* @param g - The graph in which to search for the vertex.
* @param indice - The index of the vertex to find.
* 
* @return The vertex found at the specified index, or NULL if not found. */
Grafo encontrarVerticePorIndice(Grafo g, unsigned int indice) {
	for (unsigned int i = 0; i < indice; i++) {
		if (g == NULL) {
			break;
		}
		g = g->seguinte;
	}
	return g;
}

/** @brief Finds the index of a vertex in the graph based on its geocode.
* 
* @param g - The graph in which to search for the vertex.
* @param geocode - The geocode of the vertex to find.
*
* @return The index of the vertex found, or -1 if not found. */
int encontrarIndiceVertice(Grafo g, char* geocode) {
	unsigned int vertex_index = 0;
	while (g!=NULL) {
		if (strcmp(g->vertice, geocode)==0) {
			return vertex_index;
		}
		vertex_index++;
		g = g->seguinte;
	}
	return -1;
}

/** @brief Copies vertices in reverse order from the source graph to the destination graph.
* 
* @param destino - The destination graph where the vertices will be copied to.
* @param origem - The source graph from which the vertices will be copied.           */
void copiarVerticesInvertido(Grafo* destino, Grafo origem) {
	while (origem != NULL)
	{
		criarVertice(destino, origem->vertice);
		origem = origem->seguinte;
	}
}

/** @brief Finds the vertex in the graph based on its geocode.
*
* @param g - The graph in which to search for the vertex.
* @param geocode - The geocode of the vertex to find.
*
* @return The vertex found, or -1 if not found. */
Grafo encontrarVertice(Grafo g, char* geocode) {

	while (g != NULL) {
		if (strcmp(g->vertice, geocode) == 0) {
			return g;
		}
		g = g->seguinte;
	}
	return -1;
}
