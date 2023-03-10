#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include "accounts.h"
#include "menus.h"
#include "ll.h"

void show_data(account_info* data) {
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

	read_accounts(&accounts);

	while (logged_account.nif == NULL) {
		login(accounts, &logged_account);
	}

	if (logged_account.type == ADMIN) {
		admin_main_menu(&accounts, &logged_account);
	}
	else if (logged_account.type == CLIENT) {
		client_main_menu(&accounts, &logged_account);
	}

	showListIterative(accounts, &show_data);

	return 0;
}