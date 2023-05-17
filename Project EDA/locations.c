#include "locations.h"

/** @brief Reads the MAP locations file(MAP_LOCATIONS_FILE) and stores the
* locations in the map data structure
*
* @param[out] map - map data structure where the data will be stored */
void read_map_locations(Grafo* map) {
	FILE* fd;
	fd = fopen(MAP_LOCATIONS_FILE, "r");

	Grafo* aux_graph = malloc(sizeof(Grafo));

	if (aux_graph != NULL) {
		memset(aux_graph, 0, sizeof(Grafo));


		if (fd != NULL) {
			char str_buf[MAX_BUFFERS_SIZE] = { 0 };

			while (fscanf(fd, "%s\n",
				str_buf) != EOF) {

				criarVertice(aux_graph, str_buf);
			}

			copiarVerticesInvertido(map, *aux_graph);
		}
	}
}

/** @brief Reads the MAP roads file(MAP_ROADS_FILE) and stores the
* roads in the map data structure
*
* @param[out] map - map data structure where the data will be stored */
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

/** @brief Reads MAP relatable files(MAP_LOCATIONS_FILE, MAP_ROADS_FILE) and stores the
* data in the map data structure
*
* @param[out] map - map data structure where the data will be stored */
void read_map(Grafo* map) {

	read_map_locations(map);

	read_map_roads(map);

}

int get_number_locations(Grafo map) {
	int n_locations = 0;
	while (map != NULL) {
		n_locations++;
		map = map->seguinte;
	}
	return n_locations;
}

int min_distance_adjacents(float min_distances[], char locations_processed[], int number_locations)
{
	float min = INT_MAX;
	int min_index = -1;

	for (int i = 0; i < number_locations; i++)
		if (locations_processed[i] == FALSE && min_distances[i] <= min)
			min = min_distances[i], min_index = i;

	return min_index;
}





void find_shortest_path(Grafo map, char* origin_geocode, int number_locations, float** output_distances) {

	/* Regista distancias minimas encontradas para cada vertice */
	float* min_distances;
	min_distances = (float*)malloc(number_locations * sizeof(float));

	/* Regista se distancia minima foi encontrada para cada vertice */
	char* locations_processed;
	locations_processed = (char*)malloc(number_locations);

	/* Inicializa a lista de distancias a infinito */
	/* Inicializa a lista de distancias minimas processadas a falso */
	for (int i = 0; i < number_locations; i++) {
		min_distances[i] = MAX_FLOAT;
		locations_processed[i] = FALSE;
	}

	/* Distancia da origem para ela mesma definida a 0 */
	min_distances[encontrarIndiceVertice(map, origin_geocode)] = 0;


	for (int i = 0; i < (number_locations - 1); i++) {

		int min_distance_vertex_index = min_distance_adjacents(min_distances, locations_processed, number_locations);

		locations_processed[min_distance_vertex_index] = TRUE;

		Grafo vertex_found = encontrarVerticePorIndice(map, min_distance_vertex_index);

		Adjacente vertex_found_adjacents = vertex_found->adjacentes;

		//cpy_adjacent_data(&vertex_found_adjacents, vertex_found->adjacentes);

		while (vertex_found_adjacents != NULL) {
			
			int vertex_found_adjacent_index = encontrarIndiceVertice(map, vertex_found_adjacents->vertice);
				
			if (locations_processed[vertex_found_adjacent_index] == FALSE 
				&& min_distances[min_distance_vertex_index] != MAX_FLOAT
				&& (vertex_found_adjacents->peso+ min_distances[min_distance_vertex_index])< min_distances[vertex_found_adjacent_index]) {

				min_distances[vertex_found_adjacent_index] = min_distances[min_distance_vertex_index] + vertex_found_adjacents->peso;
			}

			vertex_found_adjacents = vertex_found_adjacents->seguinte;
		}
	}

	*output_distances = min_distances;

}

