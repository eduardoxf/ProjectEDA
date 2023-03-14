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

int main() {

	setlocale(LC_ALL, "Portuguese");

	account_info logged_account = { 0 };
	ListElem accounts = NULL;
	ListElem transports = NULL;
	
	read_accounts(&accounts);

	read_transports(&transports);

	login_menu(&accounts, &logged_account);

	if (logged_account.type == ADMIN) {
		admin_main_menu(&accounts, &transports, &logged_account);
	}
	else if (logged_account.type == CLIENT) {
		client_main_menu(&transports, &logged_account);
	}

	showListIterative(transports, &show_transports_data);

	return 0;
}