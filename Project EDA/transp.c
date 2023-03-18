#include "transp.h"


int compare_transports_id(transports_data* data1, transports_data* data2) {
	if (data1->id == data2->id) {
		return 1;
	}
	else {
		return 0;
	}
}

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

void save_transports(ListElem transports) {
	FILE* fd;
	fd = fopen(TRANSPORTS_FILE, "w");
	transports_data* transport_data = NULL;

	if (fd != NULL) {
		while (transports != NULL) {
			transport_data = transports->data;
			fprintf(fd, "%d:%d:%d:%d:%s:\n",
				transport_data->id,
				transport_data->type,
				transport_data->battery,
				transport_data->autonomy,
				transport_data->geocode);

			transports = transports->next;
		}
		fclose(fd);
	}
}

void delete_transport(ListElem* transports, transports_data* data_of_transport_to_delete) {

	*transports = removeItemIterative(*transports, data_of_transport_to_delete, &compare_transports_id);

	save_transports(*transports);
}

void edit_transport(ListElem* transports, transports_data* data_to_find_transport, transports_data* new_data) {
	ListElem transport_to_edit = { 0 };
	transports_data* current_transport_data;

	transport_to_edit = findItemIterative(*transports, data_to_find_transport, &compare_transports_id);
	current_transport_data = transport_to_edit->data;

	if (new_data->id == 0) {
		new_data->id = current_transport_data->id;
	}
	if (new_data->type == 0) {
		new_data->type = current_transport_data->type;
	}

	editItemData(transport_to_edit, new_data);
	save_transports(*transports);
}

int compare_transports_autonomy(transports_data* data1, transports_data* data2) {
	if (data1->autonomy>data2->autonomy) {
		return -1;
	}
	else if (data1->autonomy < data2->autonomy) {
		return 1;
	}
	else {
		return 0;
	}
}

void show_transports_data(transports_data* data) {
	printf("ID: %d\n", data->id);
	printf("Type: %d\n", data->type);
	printf("Balance: %d\n", data->battery);
	printf("Autonomy: %d\n", data->autonomy);
	printf("Geocode: %s\n", data->geocode);
	printf("\n");
}

void list_transports_by_autonomy(ListElem transports) {
	ListElem show_transport_list = NULL;
	while (transports != NULL) {
		transports_data* data_buf = malloc(sizeof(transports_data));
		cpy_transport_data(data_buf, transports->data);
		show_transport_list = addItemOrderedIterative(show_transport_list, data_buf, &compare_transports_autonomy);
		transports = transports->next;
	}
	showListIterative(show_transport_list, &show_transports_data);
	show_transport_list = deleteList(show_transport_list);
}

void list_transports_by_geocode(ListElem transports, char geocode[]) {
	transports_data* data_buf = NULL;
	while (transports != NULL) {
		data_buf = transports->data;
		if (strcmp(data_buf->geocode, geocode)==0) {
			show_transports_data(data_buf);
		}
		transports = transports->next;
	}
}