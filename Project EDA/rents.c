#include "rents.h"

void save_transport_rent(ListElem* rental_transports, transports_rent* new_rental) {
	FILE* fd;

	fd = fopen(RENTALS_FILE, "a");

	if (fd != NULL) {

		fprintf(fd, "%d:%d:%lld:%lld:%f:\n",
			new_rental->client_nif,
			new_rental->transport_id,
			new_rental->start_rent_time,
			new_rental->final_rent_time,
			new_rental->rent_cost);

		*rental_transports = addItemHead(*rental_transports, new_rental);

		fclose(fd);
	}
}

unsigned int start_rent_transport(ListElem* rental_transports, ListElem transports, account_info logged_account, unsigned int transport_id) {
	transports_data* aux_buf = malloc(sizeof(transports_data));
	transports_rent* new_transport_rent = malloc(sizeof(transports_rent));
	aux_buf->id = transport_id;
	ListElem transport_to_rent = NULL;
	transport_to_rent = findItemIterative(transports, aux_buf, &compare_transports_id);

	if (transport_to_rent != NULL) {
		aux_buf = transport_to_rent->data;
		new_transport_rent->client_nif = logged_account.nif;
		new_transport_rent->transport_id = aux_buf->id;
		new_transport_rent->start_rent_time = time(NULL);
		new_transport_rent->final_rent_time = 0;
		new_transport_rent->rent_cost = 0;

		save_transport_rent(rental_transports, new_transport_rent);
		free(aux_buf);
		return TRANSPORT_RENTED;
	}
	else {
		free(aux_buf);
		return TRANSPORT_NOT_FOUND;
	}
}

unsigned int compare_rent_transport_id(transports_rent* data1, transports_rent* data2) {
	if (data1->transport_id == data2->transport_id) {
		return 1;
	}
	else {
		return 0;
	}
}

unsigned int compare_rent_client_nif(transports_rent* data1, transports_rent* data2) {
	if (data1->client_nif == data2->client_nif) {
		return 1;
	}
	else {
		return 0;
	}
}

void show_rents_data(transports_rent* data) {
	printf("Client NIF: %d\n", data->client_nif);
	printf("Transport ID: %d\n", data->transport_id);
	printf("When was rented: %lld\n", data->start_rent_time);
	printf("Finish Rent time: %lld\n", data->final_rent_time);
	printf("Final Cost: %f\n", data->rent_cost);
	printf("\n");
};

void rent_transport(ListElem* rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account, unsigned int transport_id) {


	ListElem transport_already_rented = NULL;
	ListElem account_already_rent = NULL;
	transports_rent data_buf = { 0 };
	char option = 0;
	data_buf.transport_id = transport_id;

	transport_already_rented = findItemIterative(*rental_transports, &data_buf, &compare_rent_transport_id);
	showListIterative(*rental_transports, &show_rents_data);
	data_buf.client_nif = logged_account->nif;
	account_already_rent = findItemIterative(*rental_transports, &data_buf, &compare_rent_client_nif);

	if (logged_account->balance > 0) {
		if (transport_already_rented == NULL && account_already_rent == NULL) {

			if (start_rent_transport(rental_transports, transports, *logged_account, transport_id) != TRANSPORT_RENTED) {
				printf("Transport ID Incorrect...\n");
				_getch();
			}
		}
		else if (account_already_rent != NULL) {
			printf("Account Already Rent want to finish the rent? (%c - Yes, %c - No)\n", YES_OPTION, NO_OPTION);
			option = _getch();
			option = toupper(option);
			if (option == YES_OPTION) {
				stop_rent_transport(rental_transports, transports, accounts, logged_account);
			}
		}
		else {
			printf("Transport Already Rented...\n");
			_getch();
		}
	}
	else {
		printf("Account doesnt have enough credit...\n");
		_getch();
	}

}


void save_rents(ListElem rental_transports) {
	FILE* fd;
	fd = fopen(RENTALS_FILE, "w");
	transports_rent* rent_data = malloc(sizeof(transports_rent));

	if (fd != NULL) {
		while (rental_transports != NULL)
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

		free(rent_data);
		fclose(fd);
	}
}

void rent_payment(ListElem rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account) {

	unsigned int cost = 0;
	transports_rent* rental_data_buf = malloc(sizeof(transports_rent));
	rental_data_buf->client_nif = logged_account->nif;

	transports_data* transport_data_buf = malloc(sizeof(transports_data));

	account_info* account_data_buf = NULL;

	ListElem rental = NULL;
	rental = findItemIterative(rental_transports, rental_data_buf, &compare_rent_client_nif);
	free(rental_data_buf);

	rental_data_buf = rental->data;
	rental_data_buf->final_rent_time = time(NULL);
	transport_data_buf->id = rental_data_buf->transport_id;

	ListElem transport_rented = NULL;
	transport_rented = findItemIterative(transports, transport_data_buf, &compare_transports_id);
	free(transport_data_buf);

	transport_data_buf = transport_rented->data;

	ListElem account_that_rent;
	account_that_rent = findItemIterative(*accounts, logged_account, compare_account_nif);

	account_data_buf = account_that_rent->data;

	if (transport_data_buf->type == SCOOTER) {
		cost = (rental_data_buf->final_rent_time - rental_data_buf->start_rent_time) * SCOOTER_COST_SEC;
	}
	else if (transport_data_buf->type == BYCICLE) {
		cost = (rental_data_buf->final_rent_time - rental_data_buf->start_rent_time) * BYCICLE_COST_SEC;
	}

	account_data_buf->balance -= cost;
	logged_account->balance -= cost;

	save_accounts(*accounts);
}

void stop_rent_transport(ListElem* rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account) {

	transports_rent data_buf = { 0 };

	data_buf.client_nif = logged_account->nif;

	rent_payment(*rental_transports, transports, accounts, logged_account);

	*rental_transports = removeItemIterative(*rental_transports, &data_buf, &compare_rent_client_nif);

	save_rents(*rental_transports);
}

void cpy_rent_data(transports_rent* data1, transports_rent* data2) {
	if (data1 != NULL && data2 != NULL) {
		data1->client_nif = data2->client_nif;
		data1->transport_id = data2->transport_id;
		data1->start_rent_time = data2->start_rent_time;
		data1->final_rent_time = data2->final_rent_time;
		data1->rent_cost = data2->rent_cost;
	}
}

void read_rents(ListElem* rental_transports) {
	FILE* fd;
	fd = fopen(RENTALS_FILE, "r");

	transports_rent data_buf = { 0 };

	if (fd != NULL) {

		while (fscanf(fd, "%d:%d:%lld:%lld:%f:\n",
			&data_buf.client_nif,
			&data_buf.transport_id,
			&data_buf.start_rent_time,
			&data_buf.final_rent_time,
			&data_buf.rent_cost) != EOF) {

			transports_rent* rent_data = malloc(sizeof(transports_rent));

			cpy_rent_data(rent_data, &data_buf);

			*rental_transports = addItemHead(*rental_transports, rent_data);
		}
		fclose(fd);
	}
}