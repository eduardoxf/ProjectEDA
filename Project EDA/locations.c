#include "locations.h"

void read_map_locations(Grafo* map) {
	FILE* fd;
	fd = fopen(MAP_LOCATIONS_FILE, "r");

	Grafo* aux_graph = malloc(sizeof(Grafo));
	memset(aux_graph, 0, sizeof(Grafo));

	Grafo aux = { 0 };

	if (fd != NULL) {
		char str_buf[MAX_BUFFERS_SIZE] = { 0 };

		while (fscanf(fd, "%s\n",
			str_buf) != EOF) {

			criarVertice(aux_graph, str_buf);
		}

		while (aux_graph != NULL) {


			aux = *aux_graph;
			if (aux->vertice != NULL) {
				criarVertice(map, aux->vertice);
				*aux_graph = aux->seguinte;
			}
			else {
				aux_graph = NULL;
			}

		}
	}
}

void read_map_roads(Grafo* map) {

	FILE* fd;
	fd = fopen(MAP_ROADS_FILE, "r");

	if (fd != NULL) {

		unsigned int index_origin, index_destiny, cost;

		while (fscanf(fd, "%d:%d:%d:\n",
			&index_origin,
			&index_destiny,
			&cost) != EOF) {

			Grafo origin = { 0 };
			Grafo destiny = { 0 };

			origin = encontrarVerticePorIndice(*map, index_origin);
			destiny = encontrarVerticePorIndice(*map, index_destiny);

			*map = criarAresta(*map, origin->vertice, destiny->vertice, cost);

		}
	}
}

void read_map(Grafo* map) {

	read_map_locations(map);

	read_map_roads(map);
}