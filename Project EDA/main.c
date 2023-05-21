#include <stdlib.h>
#include <locale.h>
#include "accounts.h"
#include "transp.h"
#include "menus.h"
#include "ll.h"
#include "locations.h"


void list_all_accounts(ListElem accounts) {
	while (accounts != NULL) {
		show_accounts_data(accounts->data);
		accounts = accounts->next;
	}
}

void list_all_transports(ListElem transports) {
	while (transports != NULL) {
		show_transports_data(transports->data);
		transports = transports->next;
	}
}

int main() {

	setlocale(LC_ALL, "Portuguese");

	/* Will store data of account logged */
	account_info logged_account = { 0 };

	/* Linked list that will store accounts */
	ListElem accounts = NULL;

	/* Linked list that will store transports */
	ListElem transports = NULL;

	/* Linked list that will store rentals */
	ListElem rental_transports = NULL;

	/* Graph that stores all the locations and distances beetween them */
	Grafo map = NULL;

	/* Reads Map from files */
	read_map(&map);

	/* Reads Rentals from file */
	read_rents(&rental_transports);

	/* Reads Accounts from file */
	read_accounts(&accounts);

	//list_all_accounts(accounts);

	/* Reads Transports from file */
	read_transports(&transports);

	//list_all_transports(transports);

	/* Inserts all transports in the correct map location */
	insert_transports_in_map(&map , transports);

	/* Executes Login */
	login_menu(&accounts, &logged_account);

	/* Verifies if account logged is an ADMIN or CLIENT */
	if (logged_account.type == ADMIN) {
		/* ADMIN menu */
		admin_main_menu(&accounts, &transports, &logged_account, map);
	}
	else if (logged_account.type == CLIENT) {
		/* CLIENT menu */
		client_main_menu(&rental_transports, &transports, &accounts, &logged_account, map);
	}

	return 0;
}