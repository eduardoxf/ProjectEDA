#pragma once

#include "grafo.h"
#include "transp.h"
#include "ll.h"

#define MAP_LOCATIONS_FILE "locations.txt"
#define MAP_ROADS_FILE "roads.txt"

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

int find_shortest_path(Grafo map, char* origin_geocode, char* destiny_geocode);