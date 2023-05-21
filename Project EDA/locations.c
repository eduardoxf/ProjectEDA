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

/* @brief Retrieves the number of locations in the graph.
* 
* @param map - The graph representing the locations.
* 
* @return The number of locations in the graph.*/
int get_number_locations(Grafo map) {
	int n_locations = 0;
	while (map != NULL) {
		n_locations++;
		map = map->seguinte;
	}
	return n_locations;
}

/** @brief Finds the index of the location with the minimum distance among the unprocessed adjacent locations.
*
* @param min_distances - An array of minimum distances for each location.
* @param locations_processed - An array indicating whether each location has been processed.
* @param number_locations - The total number of locations.

* @return The index of the location with the minimum distance among the unprocessed adjacent locations.   */
int min_distance_adjacents(float min_distances[], char locations_processed[], int number_locations){
	float min = INT_MAX;
	int min_index = -1;

	for (int i = 0; i < number_locations; i++)
		if (locations_processed[i] == FALSE && min_distances[i] <= min)
			min = min_distances[i], min_index = i;

	return min_index;
}

/** @brief Finds the shortest path from a specified origin location to all other locations in the graph.

@param map - The graph representing the locations and connections between them.
@param origin_geocode - The geocode of the origin location.
@param number_locations - The total number of locations in the graph.

@return An array of minimum distances from the origin location to each location.     */
float* find_shortest_path(Grafo map, char* origin_geocode, int number_locations) {

	
	/* min_distances is an array with size equal to the number of locations */
	/* Stores minimum distances found from the origin to each location */
	float* min_distances;
	min_distances = (float*)malloc(number_locations * sizeof(float));

	/* locations_processed is an array with size equal to the number of locations */
	/* Stores if minimum distance was already found for each location */
	char* locations_processed;
	locations_processed = (char*)malloc(number_locations);

	/* Inicializes array of minimum distances as infinite */
	/* Inicializes array of locations processed as infinite */
	for (int i = 0; i < number_locations; i++) {
		min_distances[i] = MAX_FLOAT;
		locations_processed[i] = FALSE;
	}

	/* Defines minimum distance of origin to herself as 0*/
	min_distances[encontrarIndiceVertice(map, origin_geocode)] = 0;


	/* Runs through all locations */
	for (int i = 0; i < (number_locations - 1); i++) {

		/* Gets the index of the adjacent closer */
		int min_distance_vertex_index = min_distance_adjacents(min_distances, locations_processed, number_locations);

		/* Marks the closest adjacent location as processed */
		locations_processed[min_distance_vertex_index] = TRUE;

		/* Gets the closest adjacent location */
		Grafo vertex_found = encontrarVerticePorIndice(map, min_distance_vertex_index);

		/* Gets the list of adjacents to the closest adjacent location */
		Adjacente vertex_found_adjacents = vertex_found->adjacentes;

		/* Runs through all the adjacents to the closest adjacent location */
		while (vertex_found_adjacents != NULL) {
			
			/* Finds the index of the adjacent */
			int vertex_found_adjacent_index = encontrarIndiceVertice(map, vertex_found_adjacents->vertice);
				
			/* Checks if the adjacent location is not processed, the current minimum distance is not infinite,
			* and the new calculated distance is smaller than the previous minimum distance for the adjacent location.*/
			if (locations_processed[vertex_found_adjacent_index] == FALSE 
				&& min_distances[min_distance_vertex_index] != MAX_FLOAT
				&& (vertex_found_adjacents->peso+ min_distances[min_distance_vertex_index])< min_distances[vertex_found_adjacent_index]) {

				/* Updates the new minimum distance for the adjacent location */
				min_distances[vertex_found_adjacent_index] = min_distances[min_distance_vertex_index] + vertex_found_adjacents->peso;
			}

			/* Skips to next adjacent */
			vertex_found_adjacents = vertex_found_adjacents->seguinte;
		}
	}

	/* Returns list of minimum distances */
	return min_distances;

}

