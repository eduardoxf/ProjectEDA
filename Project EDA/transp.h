#pragma once

#define SCOOTER 1
#define BYCICLE 2

typedef struct {
	float longi;
	float lati;
}coordinates;

typedef struct {
	coordinates north_corner;
	coordinates south_corner;
}map_chunk;

typedef struct transports_data_s{
	unsigned int id;
	unsigned int type;
	unsigned int battery;
	unsigned int autonomia;
	float custo;
	coordinates location;
}transports_data;