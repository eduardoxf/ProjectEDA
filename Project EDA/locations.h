#pragma once

#include "grafo.h"
#include "transp.h"
#include "ll.h"
#include <math.h>

#define MAP_LOCATIONS_FILE "locations.txt"
#define MAP_ROADS_FILE "roads.txt"


#define MAX_FLOAT 99999992

#define FALSE 0
#define TRUE 1

/** @brief Reads the MAP locations file(MAP_LOCATIONS_FILE) and stores the
* locations in the map data structure
*
* @param[out] map - map data structure where the data will be stored */
void read_map_locations(Grafo* map);

/** @brief Reads the MAP roads file(MAP_ROADS_FILE) and stores the
* roads in the map data structure
*
* @param[out] map - map data structure where the data will be stored */
void read_map_roads(Grafo* map);

/** @brief Reads MAP relatable files(MAP_LOCATIONS_FILE, MAP_ROADS_FILE) and stores the
* data in the map data structure
*
* @param[out] map - map data structure where the data will be stored */
void read_map(Grafo* map);

/* @brief Retrieves the number of locations in the graph.
*
* @param map - The graph representing the locations.
*
* @return The number of locations in the graph.*/
int get_number_locations(Grafo map);

/** @brief Finds the index of the location with the minimum distance among the unprocessed adjacent locations.
*
* @param min_distances - An array of minimum distances for each location.
* @param locations_processed - An array indicating whether each location has been processed.
* @param number_locations - The total number of locations.

* @return The index of the location with the minimum distance among the unprocessed adjacent locations.   */
int min_distance_adjacents(float min_distances[], char locations_processed[], int number_locations);

/** @brief Finds the shortest path from a specified origin location to all other locations in the graph.

@param map - The graph representing the locations and connections between them.
@param origin_geocode - The geocode of the origin location.
@param number_locations - The total number of locations in the graph.

@return An array of minimum distances from the origin location to each location.     */
float* find_shortest_path(Grafo map, char* origin_geocode, int number_locations);