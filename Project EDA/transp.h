#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "ll.h"
#include "accounts.h"
#include "locations.h"

/* Types of Transports */
#define SCOOTER 1
#define BYCICLE 2

/* Path of file that stores transports */
#define TRANSPORTS_FILE "transports.txt"

/* Sizes of each string in transports data structure */
#define MAX_GEOCODE_SIZE 70

/** @struct transports_data_s
* @brief Data structure of each transport in the linked list
*
* @var transports_data_s::id
* Member 'id' contains the ID number of the transport

* @var transports_data_s::type
* Member 'type' contains if the transport is SCOOTER or BYCICLE
*
* @var transports_data_s::battery
* Member 'battery' contains the battery of the transport
*
* @var transports_data_s::autonomy
* Member 'autonomy' contains the autonomy of the transport
*
* @var transports_data_s::geocode
* Member 'geocode' contains the Transport location geocode */
typedef struct transports_data_s{

	unsigned int id;

	unsigned int type;

	unsigned int battery;

	unsigned int autonomy;

	char geocode[MAX_GEOCODE_SIZE];
}transports_data;

/** @brief Compares if ID in data1 is equal to ID in data2
* 
* @param data1 - transport 1 data to compare
* @param data2 - transport 2 data to compare
* 
* @retval 1 - IDs are equal
* @retval 2 - IDs are different							*/
int compare_transports_id(transports_data* data1 , transports_data* data2);

/** @brief Copies data from data2 and stores it in data1
* 
* @param[out] data1 - transport data buffer that will store the information
* @param data2 - transport data to copy								*/
void cpy_transport_data(transports_data* data1, transports_data* data2);

/** @brief Reads transports in TRANSPORTS_FILE and stores it in transports linked list
* 
* @param[out] transports - linked list where the transports will be stored             */
void read_transports(ListElem* transports);

/** @brief Writes a transport in TRANSPORTS_FILE and adds it to transports linked list
* 
* @param[out] transports - linked list that stores all transports
* @param new_transport_data - data of transport to create					   	  */
void create_transport(ListElem* transports, transports_data* new_transport_data);

/** @brief Writes all transports in TRANSPORTS_FILE
* 
* @param transports - linked list that stores all transports */
void save_transports(ListElem transports);

/** @brief Deletes transport from TRANSPORTS_FILE and from the transports linked list
* 
* @param[out] transports - linked list that stores all transports
* @param data_of_transport_to_delete - stores data to know which transport is to delete
*							   (stores id of transport to delete)             */
void delete_transport(ListElem* transports, transports_data* data_of_transport_to_delete);

/** @brief Edits data of an specific transport
* 
* @param[out] transports - linked list that stores all transports
* @param data_to_find_transport - stores data to know which transport is to edit
*						   (stores Id of transport to edit)
* @param new_data - stores the new data of the transport                    */
void edit_transport(ListElem* transports, transports_data* data_to_find_transport, transports_data* new_data);

/** @brief Shows data of one transport
* 
* @param data - data to show     */
void show_transports_data(transports_data* data);

/** @brief Compares if Autonomy in data1 is equal, greater or lesser to Autonomy in data2
* 
* @param data1 - transport 1 data to compare
* @param data2 - transport 2 data to compare
* 
* @retval 1 - Data1 < Data2 autonomy
* @retval -1 - Data1 > Data2 autonomy
* @retval 0 - Data1 = Data2 autonomy													*/
int compare_transports_autonomy(transports_data* data1, transports_data* data2);

/** @brief Lists transports in descending order of autonomy 
* 
* @param transports - linked list that stores all transports */
void list_transports_by_autonomy(ListElem transports);

/** @brief Lists all transports with an specific geocode
* 
* @param transports - linked list that stores all transports
* @param geocode - geocode of transports to list			*/
void list_transports_by_geocode(ListElem transports, char geocode[]);

/** @brief Inserts all Transports in the Map data structure
*
* @param map - map where the transports will be inserted
* @param transports - all transports to be inserted			*/
void insert_transports_in_map(Grafo* map, ListElem transports);

void list_transports_by_distance(ListElem transport, Grafo map, char* geocode_origin, unsigned int distance):