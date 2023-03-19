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
#include "transp.h"

/* Path of File that stores rentals */
#define RENTALS_FILE "rentals.txt"

/* Cost of rental by second of each type of transport */
#define SCOOTER_COST_SEC 2
#define BYCICLE_COST_SEC 1

/* Returns Possible of start_rent_transport function */
#define TRANSPORT_RENT_STOPPED 23
#define TRANSPORT_RENT_STOP_ERROR 32

/* Returns Possible of stop_rent_transport function */
#define TRANSPORT_RENTED 1
#define TRANSPORT_NOT_FOUND 0

/* Utilities for rent_transport function */
#define YES_OPTION 'Y'
#define NO_OPTION 'N'

/* Data structure of an rental in the linked list */
typedef struct transports_rent_s {
	/* Client nif that rented */
	unsigned int client_nif;

	/* Transport ID that was rented */
	unsigned int transport_id;

	/* Time that rental was efectuated */
	time_t start_rent_time;

	/* Time that rental as finished */
	time_t final_rent_time;

	/* Final cost of rental */
	float rent_cost;
}transports_rent;

/* Starts to rent an transport 
* Arguments:
* rental_transports - linked list that stores the rentals
* transports - linked list that stores the transports
* logged_account - account curently logged(efectuating the rental)
* transport_id - transport ID to rent							
* Returns:
* TRANSPORT_RENTED - start rent sucessfull 
* TRANSPORT_NOT_FOUND - start rent unsucessfull    */
unsigned int start_rent_transport(ListElem* rental_transports, ListElem transports, account_info logged_account, unsigned int transport_id);

/* Main Function that manages the rents
* Arguments:
* rental_transports - linked list that stores the rentals
* transports - linked list that stores the transports
* accounts - linked list that stores the accounts 
* logged_account - account curently logged(efectuating the rental)
* transport_id - transport ID to rent				*/
void rent_transport(ListElem* rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account, unsigned int transport_id);

/* Verifies if transport ID is equal in two rentals data 
* Arguments:
* data1 - rental1 data to compare 
* data2 - rental2 data to compare	
* Returns:
* 1 - Transports IDs of the two rentals are equal 
* 0 - Transports IDs of the two rentals are different */
unsigned int compare_rent_transport_id(transports_rent* data1, transports_rent* data2);

/* Verifies if client ID is equal in two rentals data
* Arguments:
* data1 - rental1 data to compare
* data2 - rental2 data to compare
* Returns:
* 1 - Client NIF of the two rentals are equal
* 0 - Client NIF of the two rentals are different */
unsigned int compare_rent_client_nif(transports_rent* data1, transports_rent* data2);

/* Finishes a rental
* Arguments:
* rental_transports - linked list that stores the rentals
* transports - linked list that stores the transports
* accounts - linked list that stores the accounts	
* logged_account - account curently logged(efectuating the rental)					
* Returns:
* TRANSPORT_RENT_STOPPED - finish rent sucessfull 
* TRANSPORT_RENT_STOP_ERROR - finish rent unsucessfull    */
void stop_rent_transport(ListElem* rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account);

/* Reads accounts in RENTALS_FILE and stores it in rental_transports linked list
* Arguments:
* rental_transports - linked list where the rentals will be stored            */
void read_rents(ListElem* rental_transports);

/* Shows data of one rental
* Arguments:
* data - rental data to show     */
void show_rents_data(transports_rent* data);

/* Saves one rental in RENTALS_FILE 
* Arguments:
* rental_transports - linked list that stores rentals
* new_rental - rental data to save					*/
void save_transport_rent(ListElem* rental_transports, transports_rent* new_rental);

/* Writes all rentals in RENTALS_FILE
* Arguments:
* accounts - linked list that stores all accounts */
void save_rents(ListElem rental_transports);

/* Efectuates the payment of an rental 
* Arguments:
* rental_transports - linked list that stores rentals
* transports - linked list that stores the transports
* accounts - linked list that stores the accounts	
* logged_account - account curently logged				*/
void rent_payment(ListElem rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account);

/* Copies rental data from data2 and stores it in data1
* Arguments:
* data1 - rental data buffer that will store the information
* data2 - rental data to copy								*/
void cpy_rent_data(transports_rent* data1, transports_rent* data2);
