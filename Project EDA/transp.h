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

/* Types of Transports */
#define SCOOTER 1
#define BYCICLE 2

/* Path of file that stores transports */
#define TRANSPORTS_FILE "transports.txt"

/* Sizes of each string in transports data structure */
#define MAX_GEOCODE_SIZE 30

/* Data structure of each transport in the linked list */
typedef struct transports_data_s{
	/* Number that identifies each transport (unique for each transport) */
	unsigned int id;
	/* Type: SCOOTER or BYCICLE */
	unsigned int type;
	unsigned int battery;
	unsigned int autonomy;
	/* Transport location geocode */
	char geocode[MAX_GEOCODE_SIZE];
}transports_data;

/* Compares if ID in data1 is equal to ID in data2
* Arguments:
* data1 - transport 1 data to compare
* data2 - transport 2 data to compare
* Returns:
* 1 - IDs are equal
* 2 - IDs are different							*/
int compare_transports_id(transports_data* data1 , transports_data* data2);

/* Copies data from data2 and stores it in data1
* Arguments:
* data1 - transport data buffer that will store the information
* data2 - transport data to copy								*/
void cpy_transport_data(transports_data* data1, transports_data* data2);

/* Reads transports in TRANSPORTS_FILE and stores it in transports linked list
* Arguments:
* transports - linked list where the transports will be stored             */
void read_transports(ListElem* transports);

/* Writes a transport in TRANSPORTS_FILE and adds it to transports linked list
* Arguments:
* transports - linked list that stores all transports
* new_transport_data - data of transport to create					   	  */
void create_transport(ListElem* transports, transports_data* new_transport_data);

/* Writes all transports in TRANSPORTS_FILE
* Arguments:
* transports - linked list that stores all transports */
void save_transports(ListElem transports);

/* Deletes transport from TRANSPORTS_FILE and from the transports linked list
* Arguments:
* transports - linked list that stores all transports
* data_of_transport_to_delete - stores data to know which transport is to delete
*							   (stores id of transport to delete)             */
void delete_transport(ListElem* transports, transports_data* data_of_transport_to_delete);

/* Edits data of an specific transport
* Arguments:
* transports - linked list that stores all transports
* data_to_find_transport - stores data to know which transport is to edit
*						   (stores Id of transport to edit)
* new_data - stores the new data of the transport                    */
void edit_transport(ListElem* transports, transports_data* data_to_find_transport, transports_data* new_data);

/* Shows data of one transport
* Arguments:
* data - data to show     */
void show_transports_data(transports_data* data);

/* Compares if Autonomy in data1 is equal, greater or lesser to Autonomy in data2
* Arguments:
* data1 - transport 1 data to compare
* data2 - transport 2 data to compare
* Returns:
* 1 - Data1 < Data2 autonomy
* -1 - Data1 > Data2 autonomy
* 0 - Data1 = Data2 autonomy													*/
int compare_transports_autonomy(transports_data* data1, transports_data* data2);

/* Lists transports in descending order of autonomy 
* Arguments:
* transports - linked list that stores all transports */
void list_transports_by_autonomy(ListElem transports);

/* Lists all transports with an specific geocode
* Arguments:
* transports - linked list that stores all transports
* geocode - geocode of transports to list			*/
void list_transports_by_geocode(ListElem transports, char geocode[]);
