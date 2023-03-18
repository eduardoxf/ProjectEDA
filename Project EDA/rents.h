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


#define RENTALS_FILE "rentals.txt"

#define SCOOTER_COST_SEC 2
#define BYCICLE_COST_SEC 1

#define TRANSPORT_RENT_STOPPED 23
#define TRANSPORT_RENT_STOP_ERROR 32

#define TRANSPORT_RENTED 1
#define TRANSPORT_NOT_FOUND 0

#define YES_OPTION 'Y'
#define NO_OPTION 'N'

typedef struct transports_rent_s {
	unsigned int client_nif;
	unsigned int transport_id;
	time_t start_rent_time;
	time_t final_rent_time;
	float rent_cost;
}transports_rent;

unsigned int start_rent_transport(ListElem* rental_transports, ListElem transports, account_info logged_account, unsigned int transport_id);

void rent_transport(ListElem* rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account, unsigned int transport_id);

unsigned int compare_rent_transport_id(transports_rent* data1, transports_rent* data2);

unsigned int compare_rent_client_nif(transports_rent* data1, transports_rent* data2);

void stop_rent_transport(ListElem* rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account);

void read_rents(ListElem* rental_transports);

void show_rents_data(transports_rent* data);
