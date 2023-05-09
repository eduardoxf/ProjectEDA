#include <stdlib.h>
#include <locale.h>
#include "accounts.h"
#include "transp.h"
#include "menus.h"
#include "ll.h"
#include "locations.h"

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

	Grafo map = NULL;

	read_map(&map);

	/* Reads Rentals from file */
	read_rents(&rental_transports);

	/* Reads Accounts from file */
	read_accounts(&accounts);

	/* Reads Transports from file */
	read_transports(&transports);

	insert_transports_in_map(&map , transports);

	/* Executes Login */
	login_menu(&accounts, &logged_account);

	/* Verifies if account logged is an ADMIN or CLIENT */
	if (logged_account.type == ADMIN) {
		/* ADMIN menu */
		admin_main_menu(&accounts, &transports, &logged_account);
	}
	else if (logged_account.type == CLIENT) {
		/* CLIENT menu */
		client_main_menu(&rental_transports, &transports, &accounts, &logged_account);
	}

	return 0;
}