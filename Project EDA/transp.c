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

	printf("Press any key to continue...");
	_getch();
}

void save_transport_rent(ListElem* rental_transports, transports_rent* new_rental) {
	FILE* fd;

	fd = fopen(RENTALS_FILE, "a");

	if (fd != NULL) {

		fprintf(fd,"%d:%d:%lld:%lld:%f:\n",
			new_rental->client_nif,
			new_rental->transport_id, 
			new_rental->start_rent_time, 
			new_rental->final_rent_time,
			new_rental->rent_cost);

		*rental_transports = addItemHead(*rental_transports, new_rental);

		fclose(fd);
	}
}

unsigned int start_rent_transport(ListElem* rental_transports,ListElem transports, account_info logged_account, unsigned int transport_id) {
	transports_data* aux_buf = malloc(sizeof(transports_data));
	transports_rent* new_transport_rent = malloc(sizeof(transports_rent));
	aux_buf->id = transport_id;
	ListElem transport_to_rent = NULL;
	transport_to_rent = findItemIterative(transports,aux_buf,&compare_transports_id);

	if (transport_to_rent != NULL) {
		aux_buf = transport_to_rent->data;
		new_transport_rent->client_nif = logged_account.nif;
		new_transport_rent->transport_id = aux_buf->id;
		new_transport_rent->start_rent_time = time(NULL);
		new_transport_rent->final_rent_time = 0;
		new_transport_rent->rent_cost = 0;

		save_transport_rent(rental_transports, new_transport_rent);

		return TRANSPORT_RENTED;
	}
	else {
		return TRANSPORT_NOT_FOUND;
	}
}

unsigned int compare_rent_transport_id(transports_rent* data1, transports_rent* data2) {
	if (data1->transport_id = data2->transport_id) {
		return 1;
	}
	else {
		return 0;
	}
}

unsigned int compare_rent_client_nif(transports_rent* data1, transports_rent* data2) {
	if (data1->client_nif = data2->client_nif) {
		return 1;
	}
	else {
		return 0;
	}
}

void rent_transport(ListElem* rental_transports, ListElem transports, account_info* logged_account, unsigned int transport_id) {
	ListElem transport_already_rented = NULL;
	ListElem account_already_rent = NULL;
	transports_rent data_buf = { 0 };
	char option = 0;
	data_buf.transport_id = transport_id;
	transport_already_rented = findItemIterative(*rental_transports, &data_buf, &compare_rent_transport_id);
	data_buf.client_nif = logged_account->nif;
	account_already_rent = findItemIterative(*rental_transports, &data_buf, &compare_rent_client_nif);

	if (transport_already_rented == NULL && account_already_rent == NULL) {
		if (start_rent_transport(rental_transports, transports, *logged_account, transport_id) != TRANSPORT_RENTED) {
			printf("Transport ID Incorrect\n");
		}
	}
	else if (account_already_rent != NULL){
		printf("Account Already Rent want to finish the rent? (%d - Yes, %d - No)\n", YES_OPTION, NO_OPTION);
		scanf("%c", &option);
		if (option == YES_OPTION) {
			stop_rent_transport(rental_transports, logged_account);
		}
	}
	else {
		printf("Transport Already Rented\n");
	}
}


void save_rents(ListElem rental_transports) {
	FILE* fd;
	fd = fopen(RENTALS_FILE, "w");
	transports_rent* rent_data = malloc(sizeof(transports_rent));

	if (fd != NULL) {
		while (rental_transports !=NULL)
		{	
			rent_data = rental_transports->data;
			fprintf(fd, "%d:%d:%lld:%lld:%f:\n",
				rent_data->client_nif,
				rent_data->transport_id,
				rent_data->start_rent_time,
				rent_data->final_rent_time,
				rent_data->rent_cost);
			rental_transports = rental_transports->next;
		}
	}
}

void stop_rent_transport(ListElem* rental_transports, account_info* logged_account) {

	transports_rent data_buf = { 0 };
	data_buf.client_nif = logged_account->nif;
	*rental_transports = removeItemIterative(*rental_transports, &data_buf, &compare_rent_client_nif);

	save_rents(*rental_transports);
}