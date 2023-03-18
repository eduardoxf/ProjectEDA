#include <stdlib.h>
#include <locale.h>
#include "accounts.h"
#include "transp.h"
#include "menus.h"
#include "ll.h"

void show_accounts_data(account_info* data) {
	printf("Name: %s\n", data->name);
	printf("Nif: %d\n", data->nif);
	printf("Balance: %d\n", data->balance);
	printf("Admin: %d\n", data->type);
	printf("Password: %s\n", data->password);
	printf("Residence: %s\n", data->residence);
	printf("\n");
}

void show_rents_data(transports_rent* data) {
	printf("Client NIF: %d\n", data->client_nif);
	printf("Transport ID: %d\n", data->transport_id);
	printf("When was rented: %lld\n", data->start_rent_time);
	printf("Finish Rent time: %lld\n", data->final_rent_time);
	printf("Final Cost: %f\n", data->rent_cost);
	printf("\n");
}

int main() {

	setlocale(LC_ALL, "Portuguese");

	account_info logged_account = { 0 };
	ListElem accounts = NULL;
	ListElem transports = NULL;
	ListElem rental_transports = NULL;

	read_rents(&rental_transports);

	showListIterative(rental_transports, &show_rents_data);

	read_accounts(&accounts);

	read_transports(&transports);

	login_menu(&accounts, &logged_account);

	if (logged_account.type == ADMIN) {
		admin_main_menu(&accounts, &transports, &logged_account);
	}
	else if (logged_account.type == CLIENT) {
		client_main_menu(&rental_transports, &transports, &accounts, &logged_account);
	}

	showListIterative(transports, &show_transports_data);

	return 0;
}