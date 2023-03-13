#include "transp.h"

void cpy_transport_data(transports_data* data1, transports_data* data2) {
	if (data1 != NULL && data2 != NULL) {

		data1->id = data2->id;
		data1->type = data2->type;
		data1->battery = data2->battery;
		data1->autonomy = data2->autonomy;
		strcpy_s(data1->geocode, MAX_GEOCODE_SIZE, data2->geocode);
	}
}

void read_transports(ListElem* transports) {
	FILE* fd;
	fd = fopen(TRANSPORTS_FILE, "r");
	if (fd != NULL) {
		transports_data aux_buf = { 0 };
		while (fscanf(fd, "%d:%d:%d:%d:%[^:]:\n", 
			&aux_buf.id,
			&aux_buf.type,
			&aux_buf.battery,
			&aux_buf.autonomy,
			aux_buf.geocode) != EOF) {

			transports_data* aux = malloc(sizeof(transports_data));

			cpy_transport_data(aux, &aux_buf);

			*transports = addItemHead(*transports, aux);
		}
		fclose(fd);
	}
}

void create_transport(ListElem* transports, transports_data* new_transport_data) {
	FILE* fd;

	fd = fopen(TRANSPORTS_FILE, "a");

	if (fd != NULL) {
		fprintf(fd, "%d:%d:%d:%d:%s:\n",
			new_transport_data->id,
			new_transport_data->type,
			new_transport_data->battery,
			new_transport_data->autonomy,
			new_transport_data->geocode);

		*transports = addItemHead(*transports, new_transport_data);
		fclose(fd);
	}
}