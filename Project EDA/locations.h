#pragma once

#include "grafo.h"
#include "transp.h"
#include "ll.h"

#define MAP_LOCATIONS_FILE "locations.txt"
#define MAP_ROADS_FILE "roads.txt"

void read_map_locations(Grafo* map);

void read_map_roads(Grafo* map);

void read_map(Grafo* map);
