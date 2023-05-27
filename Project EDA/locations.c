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
* @param path_distance - The array containing the minimum distances for each location.
* @param locations_processed - An array indicating whether each location has been processed.
* @param number_locations - The total number of locations.

* @return The index of the location with the minimum distance among the unprocessed adjacent locations.   */
int min_distance_adjacents(distance_path* path_distance, char locations_processed[], int number_locations) {
	float min = INT_MAX;
	int min_index = -1;

	for (int i = 0; i < number_locations; i++)
		if (locations_processed[i] == FALSE && path_distance[i].distance <= min)
			min = path_distance[i].distance, min_index = i;

	return min_index;
}



/** @brief Finds the shortest path and distance from a specified origin location to all other locations in the graph.

@param map - The graph representing the locations and connections between them.
@param origin_geocode - The geocode of the origin location.
@param number_locations - The total number of locations in the graph.

@return An array containing the shorthest path and minimum distances from the origin location to each location.     */
distance_path* find_shortest_path(Grafo map, char* origin_geocode, int number_locations) {

	/* min_distances is an array with size equal to the number of locations */
	/* Stores minimum distances found from the origin to each location */
	distance_path* path_distance;
	path_distance = (distance_path*)malloc(number_locations * sizeof(distance_path));

	/* locations_processed is an array with size equal to the number of locations */
	/* Stores if minimum distance was already found for each location */
	char* locations_processed;
	locations_processed = (char*)malloc(number_locations);

	/* Inicializes array of minimum distances as infinite */
	/* Inicializes array of locations processed as infinite */
	for (int i = 0; i < number_locations; i++) {

		path_distance[i].distance = MAX_FLOAT;
		path_distance[i].path = NULL;
		path_distance[i].path_length = 0;
		locations_processed[i] = FALSE;
	}

	/* Defines minimum distance of origin to herself as 0*/
	path_distance[encontrarIndiceVertice(map, origin_geocode)].distance = 0;


	/* Runs through all locations */
	for (int i = 0; i < (number_locations - 1); i++) {

		/* Gets the index of the adjacent closer to any of the processed vertex */
		int min_distance_vertex_index = min_distance_adjacents(path_distance, locations_processed, number_locations);

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
				&& path_distance[min_distance_vertex_index].distance != MAX_FLOAT
				&& (vertex_found_adjacents->peso + path_distance[min_distance_vertex_index].distance) < path_distance[vertex_found_adjacent_index].distance) {

				/* Updates the new minimum distance for the adjacent location */
				path_distance[vertex_found_adjacent_index].distance = path_distance[min_distance_vertex_index].distance + vertex_found_adjacents->peso;

				/* Adds one empty element in the path */
				path_distance[vertex_found_adjacent_index].path_length = path_distance[min_distance_vertex_index].path_length + 1;
				path_distance[vertex_found_adjacent_index].path = (int*)realloc(path_distance[vertex_found_adjacent_index].path, path_distance[vertex_found_adjacent_index].path_length * sizeof(int));

				/* Copies the path of the closest vertex of the adjacent(min_distance_vertex_index) to the path of the current adjacent vertex we are visiting */
				memcpy(path_distance[vertex_found_adjacent_index].path, path_distance[min_distance_vertex_index].path, path_distance[min_distance_vertex_index].path_length * sizeof(int));

				/* Inserts the last element of the path as the current adjacent vertex we are visiting */
				path_distance[vertex_found_adjacent_index].path[path_distance[vertex_found_adjacent_index].path_length - 1] = vertex_found_adjacent_index;

			}

			/* Skips to next adjacent */
			vertex_found_adjacents = vertex_found_adjacents->seguinte;
		}
	}

	/* Returns list of minimum distances */
	return path_distance;

}

/** @brief Lists all the djikstra minimum distances and Paths.

@param path_distance - All the Djikstra Distances and Paths.
@param number_locations - The total number of vertices.    */
void list_djikstra(distance_path* path_distance, int number_locations) {
	for (int i = 0; i < number_locations; i++) {
		printf("----\n");
		printf("To vertex %d\n", i);
		printf("Distance: %f\n", path_distance[i].distance);

		printf("Size Path: %d\n", path_distance[i].path_length);
		printf("Path: ");
		for (int j = 0; j < path_distance[i].path_length; j++) {
			printf(" ->%d", path_distance[i].path[j]);
		}
		printf("\n");

	}
}

/** @brief Checks if a location is acessible in the map (its acessible and has a way back)
*
* @param map - The graph representing the locations and connections between them.
* @param origin_geocode - The geocode of the origin location.
* @param vertex_geocode - location geocode to check acessibility
* @param number_locations - The total number of locations in the graph
*
* @return 1 if location is acessible 0 if not         */
int check_vertex_acessible(Grafo map, char* origin_geocode, char* vertex_geocode, int number_locations) {
	int vertex_to_origin_path = 0;
	int origin_to_vertex_path = 0;

	distance_path* path_distance;
	path_distance = find_shortest_path(map, origin_geocode, number_locations);

	if (path_distance[encontrarIndiceVertice(map, vertex_geocode)].distance != MAX_FLOAT) {
		origin_to_vertex_path = TRUE;
	}

	path_distance = find_shortest_path(map, vertex_geocode, number_locations);

	if (path_distance[encontrarIndiceVertice(map, origin_geocode)].distance != MAX_FLOAT) {
		vertex_to_origin_path = TRUE;
	}

	if (vertex_to_origin_path && origin_to_vertex_path) {
		return 1;
	}
	else {
		return 0;
	}
}

/** @brief Verifies if locations index are equal
* @param vertex_index1 - location 1 index
* @param vertex_index2 - location 2 index
*
* @return 1 if location is equal 0 if not         */
int compare_vertex(int* vertex_index1, int* vertex_index2) {
	if (*vertex_index1 == *vertex_index2) {
		return 1;
	}
	return 0;
}

/** @brief Gets a list of acessible locations with transports
*
* @param map - The graph representing the locations and connections between them.
* @param transports - list containing all transports with their respective data.
* @param[out] vertices_with_transports - Output List that will contain all the acessible locations with transports.
* @param origin_geocode - The geocode of the origin location.
* @param number_locations - The total number of locations in the graph       */
void get_vertices_with_transports(Grafo map, ListElem transports, ListElem* vertices_with_transports, char* origin_geocode, int number_locations) {

	transports_data* transport_data_buf;

	while (transports != NULL) {
		int* index_vertex = (int*)malloc(sizeof(int));
		transport_data_buf = transports->data;
		*index_vertex = encontrarIndiceVertice(map, transport_data_buf->geocode);

		if (transport_data_buf->battery < 50) {
			if (check_vertex_acessible(map, origin_geocode, transport_data_buf->geocode, number_locations)) {

				if (findItemIterative(*vertices_with_transports, index_vertex, compare_vertex) == NULL) {
					*vertices_with_transports = addItemHead(*vertices_with_transports, index_vertex);
				}

			}
		}

		transports = transports->next;
	}
}

/** @brief Sorts locations with transports in the optimal order to minimize the total path distance to traverse all the locations with transports.
* 
* @param map - The graph representing the locations and connections between them.
* @param vertices_with_transports - List that contains all the acessible locations with transports.
* @param origin_geocode - The geocode of the origin location.
* @param number_locations - The total number of locations in the graph.
* 
* @return Sorted List of vertices with transports	*/
ListElem sort_vertices_with_transports(Grafo map, ListElem vertices_with_transports, char* origin_geocode, int number_locations) {

	ListElem sorted_vertices = NULL;
	ListElem copy_vertices_with_transports;
	copy_vertices_with_transports = vertices_with_transports;

	distance_path* distances_buf;

	int* processed = (int*)malloc(number_locations * sizeof(int));
	memset(processed, 0, number_locations * sizeof(int));

	char previous_geocode[MAX_GEOCODE_SIZE] = { 0 };
	int min_value;
	int* index_min_value;
	int* aux;

	strcpy(previous_geocode, origin_geocode);

	while (vertices_with_transports != NULL) {
		index_min_value = (int*)malloc(sizeof(int));

		distances_buf = find_shortest_path(map, previous_geocode, number_locations);

		min_value = INT_MAX;
		*index_min_value = -1;
		for (int j = 0; j < number_locations; j++) {
			if (distances_buf[j].distance < min_value && processed[j] == 0) {

				aux = (int*)malloc(sizeof(int));
				*aux = j;

				if (findItemIterative(copy_vertices_with_transports, aux, &compare_vertex) != NULL) {

					min_value = distances_buf[j].distance;
					*index_min_value = j;
				}
				free(aux);
			}
		}

		if (*index_min_value != -1) {
			processed[*index_min_value] = 1;
			sorted_vertices = addItemLastIterative(sorted_vertices, index_min_value);
			strcpy(previous_geocode, encontrarVerticePorIndice(map, *index_min_value));
		}

		vertices_with_transports = vertices_with_transports->next;
	}

	vertices_with_transports = deleteList(vertices_with_transports);

	return sorted_vertices;
}

/** @brief Gets best path to follow that includes all the locations with transports.
*
* @param map - The graph representing the locations and connections between them.
* @param vertices_with_transports - List that contains all the acessible locations with transports.
* @param origin_geocode - The geocode of the origin location.
* @param number_locations - The total number of locations in the graph.
*
* @return Optimized Path to get all transports	*/
ListElem get_path_follow(Grafo map, ListElem vertices_with_transports, char* origin_geocode, int number_locations) {

	ListElem path_follow = NULL;

	Grafo vertex_buf;
	unsigned int* index_buf;
	unsigned int* previous_index_buf;
	distance_path* paths_buf;

	char previous_geocode[MAX_GEOCODE_SIZE] = { 0 };
	strcpy(previous_geocode, origin_geocode);

	previous_index_buf = (unsigned int*)malloc(sizeof(unsigned int));
	*previous_index_buf = encontrarIndiceVertice(map, previous_geocode);
	path_follow = addItemHead(path_follow, previous_index_buf);

	while (vertices_with_transports != NULL) {

		index_buf = vertices_with_transports->data;

		paths_buf = find_shortest_path(map, previous_geocode, number_locations);


		for (int j = 0; j < paths_buf[*index_buf].path_length; j++) {

			int* aux = (int*)malloc(sizeof(int));
			*aux = paths_buf[*index_buf].path[j];

			path_follow = addItemLastIterative(path_follow, aux);
		}

		vertex_buf = encontrarVerticePorIndice(map, *index_buf);
		if (vertex_buf != NULL) {
			strcpy(previous_geocode, vertex_buf->vertice);
		}


		vertices_with_transports = vertices_with_transports->next;
	}

	return path_follow;
}

void show_index(int* index) {
	printf("->%d", *index);
}


/** @brief Traverses a determined path and collects all the transports along the way until collector reachs max capacity.
*
* @param map - The graph representing the locations and connections between them.
* @param path_follow - Path to traverse.
* @param transports - list of all transports.
* @param[out] collector - Will contain the transports collected and the optimized path to collect the maximum quantity of transports and go back to origin.
* @param origin_geocode - The geocode of the origin location.
* @param number_locations - The total number of locations in the graph.     */
void traverse_path(Grafo map, ListElem transports, ListElem path_follow, transport_collector* collector, char* origin_geocode, int number_locations) {

	Grafo current_vertex;
	Meios transports_in_vertex;
	ListElem transport_found;
	transports_data* transport_found_data;
	int* current_vertex_index;
	int last_vertex_index = encontrarIndiceVertice(map, origin_geocode);
	int* origin_index;

	distance_path* path_distance;

	while (path_follow != NULL) {

		if (collector->capacity + SCOOTER_WHEIGHT <= MAX_COLLECTOR_CAPACITY
			|| collector->capacity + BYCICLE_WHEIGHT <= MAX_COLLECTOR_CAPACITY) {

			current_vertex_index = path_follow->data;
			last_vertex_index = *current_vertex_index;

			collector->path = addItemLastIterative(collector->path, current_vertex_index);

			current_vertex = encontrarVerticePorIndice(map, *current_vertex_index);

			transports_in_vertex = current_vertex->meios;

			while (transports_in_vertex != NULL) {

				transport_found = findItemIterative(transports, transports_in_vertex, &compare_transports_id);
				transport_found_data = transport_found->data;

				if (findItemIterative(collector->transports_collected, transport_found_data, &compare_vertex) == NULL) {
					if (transport_found_data->battery < 50) {
						if (transport_found_data->type == SCOOTER) {
							if (collector->capacity + SCOOTER_WHEIGHT <= MAX_COLLECTOR_CAPACITY) {
								int* aux1 = (int*)malloc(sizeof(int));
								*aux1 = transport_found_data->id;
								collector->capacity += SCOOTER_WHEIGHT;
								collector->transports_collected = addItemLastIterative(collector->transports_collected, aux1);
							}
						}
						else if (transport_found_data->type == BYCICLE) {
							if (collector->capacity + BYCICLE_WHEIGHT <= MAX_COLLECTOR_CAPACITY) {
								int* aux2 = (int*)malloc(sizeof(int));
								*aux2 = transport_found_data->id;
								collector->capacity += BYCICLE_WHEIGHT;
								collector->transports_collected = addItemLastIterative(collector->transports_collected, aux2);
							}
						}
					}
				}
				transports_in_vertex = transports_in_vertex->seguinte;
			}

		}
		path_follow = path_follow->next;
	}

	current_vertex = encontrarVerticePorIndice(map, last_vertex_index);
	path_distance = find_shortest_path(map, current_vertex->vertice, number_locations);

	origin_index = collector->path->data;

	for (int j = 0; j < path_distance[*origin_index].path_length; j++) {
		current_vertex_index = (int*)malloc(sizeof(int));
		*current_vertex_index = path_distance[*origin_index].path[j];
		collector->path = addItemLastIterative(collector->path, current_vertex_index);
	}


}

/** @brief Shows best path to collect transports with less than 50% battery.
*
* @param map - The graph representing the locations and connections between them.
* @param transports - list of all transports.
* @param origin_geocode - The geocode of the origin location.
* @param number_locations - The total number of locations in the graph.     */
void collect_transports(Grafo map, ListElem transports, char* origin_geocode, int number_locations) {

	ListElem vertices_with_transports = NULL;
	get_vertices_with_transports(map, transports, &vertices_with_transports, origin_geocode, number_locations);

	//showListIterative(vertices_with_transports, &show_index);
	//printf("\n");

	vertices_with_transports = sort_vertices_with_transports(map, vertices_with_transports, origin_geocode, number_locations);


	//showListIterative(vertices_with_transports, &show_index);
	//printf("\n");

	ListElem path_follow = NULL;
	path_follow = get_path_follow(map, vertices_with_transports, origin_geocode, number_locations);

	vertices_with_transports = deleteList(vertices_with_transports);

	//showListIterative(path_follow, &show_index);
	//printf("\n");

	transport_collector collector = { 0 };
	traverse_path(map, transports, path_follow, &collector, origin_geocode, number_locations);

	printf(" Path Found: ");
	showListIterative(collector.path, &show_index);
	printf("\n");
	printf(" Transports Collected: ");
	showListIterative(collector.transports_collected, &show_index);
	printf("\n");

	path_follow = deleteList(path_follow);

}