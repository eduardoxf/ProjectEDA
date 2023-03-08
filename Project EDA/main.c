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

	accounts = read_accounts(accounts);
	showListIterative(accounts, &show_data);

	while (logged_account.nif == NULL) {
		login(accounts, &logged_account);
	}

	main_menu(&logged_account);

	return 0;
}