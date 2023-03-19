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

/** @struct transports_rent_s
* @brief Data structure of an rental in the linked list
* 
* @var transports_rent_s::client_nif
* Member 'client_nif' contains the Nif of the client that rented the transport

* @var transports_rent_s::transport_id
* Member 'transport_id' contains the transport id that was rented 
* 
* @var transports_rent_s::start_rent_time
* Member 'start_rent_time' contains the time that transport was rented 
* 
* @var transports_rent_s::final_rent_time 
* Member 'final_rent_time' contains the time that the rental finished 
* 
* @var transports_rent_s::rent_cost
* Member 'rent_cost' contains the final cost of rental */
typedef struct transports_rent_s {
	
	unsigned int client_nif;

	unsigned int transport_id;

	time_t start_rent_time;

	time_t final_rent_time;

	float rent_cost;
}transports_rent;

/** @brief Starts to rent an transport 
* 
* @param[out] rental_transports - linked list that stores the rentals
* @param transports - linked list that stores the transports
* @param logged_account - account curently logged(efectuating the rental)
* @param transport_id - transport ID to rent							
* 
* @retval TRANSPORT_RENTED - start rent sucessfull 
* @retval TRANSPORT_NOT_FOUND - start rent unsucessfull    */
unsigned int start_rent_transport(ListElem* rental_transports, ListElem transports, account_info logged_account, unsigned int transport_id);

/** @brief Main Function that manages the rents
* 
* @param rental_transports[out] - linked list that stores the rentals
* @param transports - linked list that stores the transports
* @param accounts[out] - linked list that stores the accounts 
* @param logged_account[out] - account curently logged(efectuating the rental)
* @param transport_id - transport ID to rent				*/
void rent_transport(ListElem* rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account, unsigned int transport_id);

/** @brief Verifies if transport ID is equal in two rentals data 
* 
* @param data1 - rental1 data to compare 
* @param data2 - rental2 data to compare	
* 
* @retval 1 - Transports IDs of the two rentals are equal 
* @retval 0 - Transports IDs of the two rentals are different */
unsigned int compare_rent_transport_id(transports_rent* data1, transports_rent* data2);

/** @brief Verifies if client ID is equal in two rentals data
* 
* @param data1 - rental1 data to compare
* @param data2 - rental2 data to compare
* 
* @retval 1 - Client NIF of the two rentals are equal
* @retval 0 - Client NIF of the two rentals are different */
unsigned int compare_rent_client_nif(transports_rent* data1, transports_rent* data2);

/** @brief Finishes a rental
* 
* @param[out] rental_transports - linked list that stores the rentals
* @param transports - linked list that stores the transports
* @param[out] accounts - linked list that stores the accounts	
* @param[out] logged_account - account curently logged(efectuating the rental)					
* 
* @retval TRANSPORT_RENT_STOPPED - finish rent sucessfull 
* @retval TRANSPORT_RENT_STOP_ERROR - finish rent unsucessfull    */
void stop_rent_transport(ListElem* rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account);

/** @brief Reads accounts in RENTALS_FILE and stores it in rental_transports linked list
* 
* @param rental_transports - linked list where the rentals will be stored            */
void read_rents(ListElem* rental_transports);

/** @brief Shows data of one rental
* 
* @param data - rental data to show     */
void show_rents_data(transports_rent* data);

/** @brief Saves one rental in RENTALS_FILE 
* 
* @param rental_transports - linked list that stores rentals
* @param new_rental - rental data to save					*/
void save_transport_rent(ListElem* rental_transports, transports_rent* new_rental);

/** @brief Writes all rentals in RENTALS_FILE
* 
* @param accounts - linked list that stores all accounts */
void save_rents(ListElem rental_transports);

/** @brief Efectuates the payment of an rental 
* 
* @param rental_transports - linked list that stores rentals
* @param transports - linked list that stores the transports
* @param[out] accounts - linked list that stores the accounts	
* @param[out] logged_account - account curently logged				*/
void rent_payment(ListElem rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account);

/** @brief Copies rental data from data2 and stores it in data1
* 
* @param[out] data1 - rental data buffer that will store the information
* @param data2 - rental data to copy								*/
void cpy_rent_data(transports_rent* data1, transports_rent* data2);
