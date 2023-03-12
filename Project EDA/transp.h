#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "ll.h"

#define SCOOTER 1
#define BYCICLE 2

#define SCOOTER_COST 1.34
#define BYCICLE_COST 0.82

#define TRANSPORTS_FILE "transports.txt"

#define MAX_GEOCODE_SIZE 30

typedef struct transports_data_s{
	unsigned int id;
	unsigned int type;
	unsigned int battery;
	unsigned int autonomy;
	char geocode[MAX_GEOCODE_SIZE];
}transports_data;

void cpy_transport_data(transports_data* data1, transports_data* data2);

void read_transports(ListElem* transports);
