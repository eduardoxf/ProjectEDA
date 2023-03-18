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

#define SCOOTER 1
#define BYCICLE 2

#define SCOOTER_COST_SEC 2
#define BYCICLE_COST_SEC 1

#define TRANSPORTS_FILE "transports.txt"
#define RENTALS_FILE "rentals.txt"

#define TRANSPORT_RENTED 1
#define TRANSPORT_NOT_FOUND 0

#define YES_OPTION 'Y'
#define NO_OPTION 'N'

#define MAX_GEOCODE_SIZE 30

#define TRANSPORT_RENT_STOPPED 23
#define TRANSPORT_RENT_STOP_ERROR 32

typedef struct transports_rent_s {
	unsigned int client_nif;
	unsigned int transport_id;
	time_t start_rent_time;
	time_t final_rent_time;
	float rent_cost;
}transports_rent;

typedef struct transports_data_s{
	unsigned int id;
	unsigned int type;
	unsigned int battery;
	unsigned int autonomy;
	char geocode[MAX_GEOCODE_SIZE];
}transports_data;

int compare_transports_id(transports_data* data1 , transports_data* data2);

void cpy_transport_data(transports_data* data1, transports_data* data2);

void read_transports(ListElem* transports);

void create_transport(ListElem* transports, transports_data* new_transport_data);

void save_transports(ListElem transports);

void delete_transport(ListElem* transports, transports_data* data_of_transport_to_delete);

void edit_transport(ListElem* transports, transports_data* data_to_find_transport, transports_data* new_data);

void show_transports_data(transports_data* data);

int compare_transports_autonomy(transports_data* data1, transports_data* data2);

void list_transports_by_autonomy(ListElem transports);

unsigned int start_rent_transport(ListElem* rental_transports, ListElem transports, account_info logged_account, unsigned int transport_id);

void rent_transport(ListElem* rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account, unsigned int transport_id);

unsigned int compare_rent_transport_id(transports_rent* data1, transports_rent* data2);

unsigned int compare_rent_client_nif(transports_rent* data1, transports_rent* data2);

void stop_rent_transport(ListElem* rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account);

void read_rents(ListElem* rental_transports);