#pragma once

#include "grafo.h"
#include "transp.h"
#include "ll.h"
#include <math.h>

/* File paths for MAP */
#define MAP_LOCATIONS_FILE "locations.txt"
#define MAP_ROADS_FILE "roads.txt"

/* Infinite Value */
#define MAX_FLOAT 99999992

/* False or True Generic */
#define FALSE 0
#define TRUE 1

/* Max Capacity of the collector */
#define MAX_COLLECTOR_CAPACITY 30

/** @struct transport_collector_s
* @brief Data structure that stores the data about the transport's collector
*
* @var transport_collector_s::capacity
* Member 'capacity' contains the current capacity of the transport
*
* @var transport_collector_s::path
* Member 'path' contains the best path found to collect all transports
*
* @var transport_collector_s::transports_collected
* Member 'transports_collected' contains the transports collected   */
typedef struct transport_collector_s {
	int capacity;
	ListElem path;
	ListElem transports_collected;
} transport_collector;

/** @struct distance_path_s
* @brief Data structure that stores all the Djikstra Algorithm Data (find_shortest_path function)
*
* @var distance_path_s::distance
* Member 'distance' contains the Minimum distance from origin

* @var distance_path_s::path
* Member 'path' contains stores the path from origin to the location
*
* @var distance_path_s::path_length
* Member 'path_length' contains the Length of the path array   */
typedef struct distance_path_s{
	float distance;      
	int* path;           
	int path_length;      
} distance_path;

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
* @param min_distances - The array containing the minimum distances for each location.
* @param locations_processed - An array indicating whether each location has been processed.
* @param number_locations - The total number of locations.

* @return The index of the location with the minimum distance among the unprocessed adjacent locations.   */
int min_distance_adjacents(distance_path* path_distance, char locations_processed[], int number_locations);

/** @brief Finds the shortest path and distance from a specified origin location to all other locations in the graph.

@param map - The graph representing the locations and connections between them.
@param origin_geocode - The geocode of the origin location.
@param number_locations - The total number of locations in the graph.

@return An array of containing the shorthest path and minimum distances from the origin location to each location.     */
distance_path* find_shortest_path(Grafo map, char* origin_geocode, int number_locations);

/** @brief Lists all the djikstra minimum distances and Paths.

@param path_distance - All the Djikstra Distances and Paths.
@param number_locations - The total number of vertices.    */
void list_djikstra(distance_path* path_distance, int number_locations);

/** @brief Checks if a location is acessible in the map (its acessible and has a way back)
* 
* @param map - The graph representing the locations and connections between them.
* @param origin_geocode - The geocode of the origin location.
* @param vertex_geocode - location geocode to check acessibility
* @param number_locations - The total number of locations in the graph
* 
* @return 1 if location is acessible 0 if not         */
int check_vertex_acessible(Grafo map, char* origin_geocode, char* vertex_geocode, int number_locations);

/** @brief Verifies if locations index are equal
* @param vertex_index1 - location 1 index
* @param vertex_index2 - location 2 index
* 
* @return 1 if location is equal 0 if not         */
int compare_vertex(int* vertex_index1, int* vertex_index2);

/** @brief Gets a list of acessible locations with transports with less than 50% battery.
* 
* @param map - The graph representing the locations and connections between them.
* @param transports - list containing all transports with their respective data.
* @param[out] vertices_with_transports - Output List that will contain all the acessible locations with transports.
* @param origin_geocode - The geocode of the origin location.
* @param number_locations - The total number of locations in the graph       */
void get_vertices_with_transports(Grafo map, ListElem transports, ListElem* vertices_with_transports, char* origin_geocode, int number_locations);

/** @brief Sorts locations with transports in the optimal order to minimize the total path distance to traverse all the locations with transports.
*
* @param map - The graph representing the locations and connections between them.
* @param vertices_with_transports - List that contains all the acessible locations with transports.
* @param origin_geocode - The geocode of the origin location.
* @param number_locations - The total number of locations in the graph.
*
* @return Sorted List of vertices with transports	*/
ListElem sort_vertices_with_transports(Grafo map, ListElem vertices_with_transports, char* origin_geocode, int number_locations);

/** @brief Gets best path to follow that includes all the locations with transports.
*
* @param map - The graph representing the locations and connections between them.
* @param vertices_with_transports - List that contains all the acessible locations with transports.
* @param origin_geocode - The geocode of the origin location.
* @param number_locations - The total number of locations in the graph.
*
* @return Optimized Path to get all transports	*/
ListElem get_path_follow(Grafo map, ListElem vertices_with_transports, char* origin_geocode, int number_locations);

/** @brief Traverses a determined path and collects all the transports along the way until collector reachs max capacity.
*
* @param map - The graph representing the locations and connections between them.
* @param path_follow - Path to traverse.
* @param transports - list of all transports.
* @param[out] collector - Will contain the transports collected and the optimized path to collect the maximum quantity of transports and go back to origin. 
* @param origin_geocode - The geocode of the origin location.
* @param number_locations - The total number of locations in the graph.     */
void traverse_path(Grafo map, ListElem transports, ListElem path_follow, transport_collector* collector, char* origin_geocode, int number_locations);

/** @brief Shows best path to collect transports with less than 50% battery.
*
* @param map - The graph representing the locations and connections between them.
* @param transports - list of all transports.
* @param origin_geocode - The geocode of the origin location.
* @param number_locations - The total number of locations in the graph.     */
void collect_transports(Grafo map, ListElem transports, char* origin_geocode, int number_locations);
