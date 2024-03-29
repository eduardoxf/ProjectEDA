#include "menus.h"

/** @brief Login Menu
* Freatures:
* Login and Registring Account
*
* @param[out] accounts_llist - linked list that stores all accounts
* @param[out] logged_account - will store data of account logged if login sucessfull  */
void login_menu(ListElem* accounts_llist, account_info* logged_account) {
	unsigned char menu_option = NONE;
	char str_buf[MAX_BUFFERS_SIZE] = { 0 };

	while (logged_account->nif == 0) {
		account_info* data_buf = malloc(sizeof(account_info));

		system("cls");
		printf("\t\033[0;34mCreate new Account?(%c-yes,%c-no)", SIGN_UP, LOGIN);
		menu_option = _getch();
		menu_option = toupper(menu_option);

		switch (menu_option)
		{
		case SIGN_UP:
			data_buf->type = CLIENT;
			data_buf->balance = 0;

			system("cls");
			printf("\t\033[0;34mInsert Account Name:\n");
			gets_s(data_buf->name, MAX_NAME_SIZE);

			printf("\t\033[0;34mInsert NIF:\n");
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->nif = atoi(str_buf);

			printf("\t\033[0;34mInsert Residence:\n");
			gets_s(data_buf->residence, MAX_RESIDENCE_SIZE);

			printf("\t\033[0;34mInsert Password:\n");
			gets_s(data_buf->password, MAX_PASSWORD_SIZE);

			printf("\t\033[0;34mInsert Geocode:\n");
			gets_s(data_buf->geocode, MAX_GEOCODE_SIZE);

			create_account(accounts_llist, data_buf);
			break;

		case LOGIN:

			system("cls");
			printf("\t\033[0;34m-----------[LOG IN]-----------\n");
			printf("\t Insert NIF: ");
			gets_s(str_buf, MAX_PASSWORD_SIZE);
			data_buf->nif = atoi(str_buf);

			printf("\t Insert Password: ");
			gets_s(data_buf->password, MAX_PASSWORD_SIZE);

			login(accounts_llist, logged_account, data_buf);
			free(data_buf);
			break;
		}
	}
}

/** @brief Menu specific only for clients
* Freatures:
* Rent Transport, List Transports or Recharge Balance
*
* @param[out] rental_transports - linked list that stores all rentals
* @param[out] transports_llist - linked lsit that stores all transports
* @param[out] accounts - linked list that stores all accounts
* @param[out] logged_account - stores data of logged account */
void client_main_menu(ListElem* rental_transports, ListElem* transports_llist, ListElem* accounts, account_info* logged_account, Grafo map) {
	unsigned char menu_option = NONE;
	int balance_buf = 0;

	while (menu_option != EXIT_MENU) {
		system("cls");
		printf("\t\033[0;34m-------------[ MENU ]-------------\t \033[0;36mLogged Account\n");
		printf("\t\033[0;34m  %c  - List Transports\t\t\t   \033[0;36mName: %s\n", LIST_TRANSPORTS, logged_account->name);
		printf("\t\033[0;34m  %c  - Rent Transport\t\t\t   \033[0;36mNIF: %d\n", RENT_TRANSPORT, logged_account->nif);
		printf("\t\033[0;34m  %c - Add Balance\t\t\t   \033[0;36mBalance: %d\n", ADD_BALANCE, logged_account->balance);
		printf("\t\033[0;34m  ESC - EXIT\t\t\t\t   \033[0;36mResidence: %s\n", logged_account->residence);
		menu_option = _getch();
		menu_option = toupper(menu_option);
		switch (menu_option) {
		case LIST_TRANSPORTS:
			list_transport_menu(transports_llist, logged_account, map);
			break;
		case RENT_TRANSPORT:
			rent_transport_menu(rental_transports, *transports_llist, accounts, logged_account);
			break;
		case ADD_BALANCE:
			system("cls");
			printf("\t\033[0;34mInsert Ammount to Recharge:\n ");
			scanf("%d", &balance_buf);

			add_balance_account(accounts, logged_account, balance_buf);
			break;
		}
	}
}

/** @brief Menu specific only for admins
* Freatures:
* Manage Accounts and Manage Transports
*
* @param[out] transports_llist - linked lsit that stores all transports
* @param[out] accounts_llist - linked list that stores all accounts
* @param[out] logged_account - stores data of logged account */
void admin_main_menu(ListElem* accounts_llist, ListElem* transports_llist, account_info* logged_account, Grafo map) {
	unsigned char menu_option = NONE;

	while (menu_option != EXIT_MENU) {
		system("cls");
		printf("\t\033[0;34m-------------[ MENU ]-------------\t \033[0;36mLogged Account\n");
		printf("\t\033[0;34m  %c  - Manage Accounts\t\t\t   \033[0;36mName: %s\n", MANAGE_ACCOUNTS, logged_account->name);
		printf("\t\033[0;34m  %c  - Manage Transports\t\t   \033[0;36mNIF: %d\n", MANAGE_TRANSPORTS, logged_account->nif);
		printf("\t\033[0;34m  ESC - EXIT\t\t\t\t   \033[0;36mBalance: %d\n", logged_account->balance);
		printf("\t\t\t\t\t\t   \033[0;36mResidence: %s\n", logged_account->residence);
		menu_option = _getch();
		menu_option = toupper(menu_option);
		switch (menu_option) {
		case MANAGE_ACCOUNTS:
			account_menu(accounts_llist, logged_account);
			break;
		case MANAGE_TRANSPORTS:
			transport_menu(transports_llist, accounts_llist, logged_account, map);
			break;
		}
	}
}

/** @brief Menu for accounts management(ADMINs Only)
* Freatures:
* Create, Delete or Edit an Account
*
* @param[out] accounts_llist - linked list that stores all accounts
* @param[out] logged_account - stores data of logged account */
void account_menu(ListElem* accounts_llist, account_info* logged_account) {
	unsigned char account_menu_option = NONE;
	char str_buf[MAX_BUFFERS_SIZE] = { 0 };

	while (account_menu_option != EXIT_MENU) {
		account_info* data_buf = malloc(sizeof(account_info));
		system("cls");
		printf("\t\033[0;34m-------------[ MENU ]-------------\t \033[0;36mLogged Account\n");
		printf("\t\033[0;34m  %c  - Create Account\t\t\t   \033[0;36mName: %s\n", CREATE_ACCOUNT, logged_account->name);
		printf("\t\033[0;34m  %c  - Delete Account\t\t\t   \033[0;36mNIF: %d\n", DELETE_ACCOUNT, logged_account->nif);
		printf("\t\033[0;34m  %c  - Edit Account\t\t\t   \033[0;36mBalance: %d\n", EDIT_ACCOUNT, logged_account->balance);
		printf("\t\033[0;34m  ESC - Back\t\t\t\t   \033[0;36mResidence: %s\n", logged_account->residence);
		account_menu_option = _getch();
		account_menu_option = toupper(account_menu_option);
		switch (account_menu_option) {
		case CREATE_ACCOUNT:

			system("cls");
			printf("\t\033[0;34mInsert Account Name:\n");
			gets_s(data_buf->name, MAX_NAME_SIZE);

			printf("\t\033[0;34mIs the new account an Admin?(%d - Yes,%d - No)\n", ADMIN, CLIENT);
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->type = atoi(str_buf);

			printf("\t\033[0;34mInsert NIF:\n");
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->nif = atoi(str_buf);

			printf("\t\033[0;34mInsert Balance:\n");
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->balance = atoi(str_buf);

			printf("\t\033[0;34mInsert Residence:\n");
			gets_s(data_buf->residence, MAX_RESIDENCE_SIZE);

			printf("\t\033[0;34mInsert Password:\n");
			gets_s(data_buf->password, MAX_PASSWORD_SIZE);

			printf("\t\033[0;34mInsert Geocode:\n");
			gets_s(data_buf->geocode, MAX_GEOCODE_SIZE);

			create_account(accounts_llist, data_buf);
			break;
		case DELETE_ACCOUNT:
			system("cls");

			printf("\t\033[0;34mInsert NIF:\n");
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->nif = atoi(str_buf);

			printf("\t\033[0;34mInsert Password:\n");
			gets_s(data_buf->password, MAX_PASSWORD_SIZE);

			delete_account(accounts_llist, data_buf);
			free(data_buf);
			break;
		case EDIT_ACCOUNT:

			system("cls");
			printf("\t\033[0;34mInsert NIF of account to edit:\n");
			account_info account_to_edit_data = { 0 };
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			account_to_edit_data.nif = atoi(str_buf);

			system("cls");
			printf("\t\033[0;34mInsert Account Name:\n");
			gets_s(data_buf->name, MAX_NAME_SIZE);

			printf("\t\033[0;34mIs the new account an Admin?(%d - Yes,%d - No)\n", ADMIN, CLIENT);
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->type = atoi(str_buf);

			printf("\t\033[0;34mInsert NIF:\n");
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->nif = atoi(str_buf);

			printf("\t\033[0;34mInsert Balance:\n");
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->balance = atoi(str_buf);

			printf("\t\033[0;34mInsert Residence:\n");
			gets_s(data_buf->residence, MAX_RESIDENCE_SIZE);

			printf("\t\033[0;34mInsert Password:\n");
			gets_s(data_buf->password, MAX_PASSWORD_SIZE);

			printf("\t\033[0;34mInsert Geocode:\n");
			gets_s(data_buf->geocode, MAX_GEOCODE_SIZE);

			edit_account(accounts_llist, &account_to_edit_data, data_buf);
			break;
		}
	}
}

/** @brief Menu for transport managements(ADMINs Only)
* Freatures:
* Create, Delete, Edit or Collect Transport(s)
*
* @param[out] transports - linked list that stores all transports
* @param[out] accounts - linked list that stores all accounts
* @param[out] logged_account - stores data of logged account */
void transport_menu(ListElem* transports, ListElem* accounts, account_info* logged_account, Grafo map) {
	unsigned char transport_menu_option = NONE;
	char str_buf[MAX_BUFFERS_SIZE] = { 0 };

	while (transport_menu_option != EXIT_MENU) {
		transports_data* data_buf = malloc(sizeof(account_info));
		system("cls");
		printf("\t\033[0;34m-------------[ MENU ]-------------\t \033[0;36mLogged Account\n");
		printf("\t\033[0;34m  %c  - Add Transport\t\t\t   \033[0;36mName: %s\n", CREATE_TRANSPORT, logged_account->name);
		printf("\t\033[0;34m  %c  - Remove Transport\t\t\t   \033[0;36mNIF: %d\n", DELETE_TRANSPORT, logged_account->nif);
		printf("\t\033[0;34m  %c  - Edit Transport\t\t\t   \033[0;36mBalance: %d\n", EDIT_TRANSPORT, logged_account->balance);
		printf("\t\033[0;34m  %c  - List Transports\t\t\t   \033[0;36mResidence: %s\n", LIST_TRANSPORTS, logged_account->residence);
		printf("\t\033[0;34m  %c - Collect Transports\n", COLLECT_TRANSPORTS);
		printf("\t\033[0;34m  ESC - Back\n");
		transport_menu_option = _getch();
		transport_menu_option = toupper(transport_menu_option);
		switch (transport_menu_option) {
		case CREATE_TRANSPORT:
			system("cls");
			printf("\t\033[0;34mInsert Transport ID:\n");
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->id = atoi(str_buf);

			printf("\t\033[0;34mDefine what type of transport: (%d - Scooter,%d - Bycicle)\n", SCOOTER, BYCICLE);
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->type = atoi(str_buf);

			printf("\t\033[0;34mInsert Battery:\n");
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->battery = atoi(str_buf);

			printf("\t\033[0;34mInsert Autonomy:\n");
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->autonomy = atoi(str_buf);

			printf("\t\033[0;34mInsert Geocode:\n");
			gets_s(data_buf->geocode, MAX_GEOCODE_SIZE);

			create_transport(transports, data_buf);
			break;
		case DELETE_TRANSPORT:

			system("cls");
			printf("\t\033[0;34mInsert ID:\n");
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->id = atoi(str_buf);

			delete_transport(transports, data_buf);
			free(data_buf);
			break;
		case EDIT_TRANSPORT:

			system("cls");
			printf("\t\033[0;34mInsert ID of account to edit:\n");
			transports_data transport_to_edit_data = { 0 };
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			transport_to_edit_data.id = atoi(str_buf);

			system("cls");
			printf("\t\033[0;34mInsert new ID:\n");
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->id = atoi(str_buf);

			printf("\t\033[0;34mInsert new transport Type: (%d - Scooter,%d - Bycicle)\n", SCOOTER, BYCICLE);
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->type = atoi(str_buf);

			printf("\t\033[0;34mInsert new battery:\n");
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->battery = atoi(str_buf);

			printf("\t\033[0;34mInsert new autonomy:\n");
			gets_s(str_buf, MAX_BUFFERS_SIZE);
			data_buf->autonomy = atoi(str_buf);

			printf("\t\033[0;34mInsert new Geocode:\n");
			gets_s(data_buf->geocode, MAX_GEOCODE_SIZE);

			edit_transport(transports, &transport_to_edit_data, data_buf);

			break;
		case LIST_TRANSPORTS:
			list_transport_menu(transports, logged_account, map);
			break;
		case COLLECT_TRANSPORTS:
			system("cls");
			collect_transports(map,*transports,logged_account->geocode, get_number_locations(map));
			printf("Press any key to continue...\n");
			_getch();
			break;
		}
	}
}

/** @brief Menu for listings of transports
* Freatures:
* List by Autonomy, Geocode and Distance
*
* @param[out] transports - linked list that stores all transports
* @param[out] logged_account - stores data of logged account */
void list_transport_menu(ListElem* transports, account_info* logged_account, Grafo map) {
	unsigned char list_transport_menu_option = NONE;
	char str_buf[MAX_GEOCODE_SIZE] = { 0 };
	unsigned int distance_buf = 0;

	while (list_transport_menu_option != EXIT_MENU)
	{
		system("cls");
		printf("\t\033[0;34m-------------[ MENU ]-------------\t \033[0;36mLogged Account\n");
		printf("\t\033[0;34m  %c  - List Transports by autonomy\t   \033[0;36mName: %s\n", LIST_TRANSPORTS_BY_AUTONOMY, logged_account->name);
		printf("\t\033[0;34m  %c  - List Transports by location\t   \033[0;36mNIF: %d\n", LIST_TRANSPORTS_BY_LOCATION, logged_account->nif);
		printf("\t\033[0;34m  %c  - List Transports by Distance\t   \033[0;36mBalance: %d\n", LIST_TRANSPORTS_BY_DISTANCE, logged_account->balance);
		printf("\t\033[0;34m  ESC - Back\t\t\t\t   \033[0;36mResidence: %s\n", logged_account->residence);
		list_transport_menu_option = _getch();
		list_transport_menu_option = toupper(list_transport_menu_option);
		switch (list_transport_menu_option) {
		case LIST_TRANSPORTS_BY_AUTONOMY:
			list_transports_by_autonomy(*transports);
			printf("Press any key to continue...");
			_getch();
			break;
		case LIST_TRANSPORTS_BY_LOCATION:
			system("cls");
			printf("\t\033[0;34m Insert geocode:\n");
			gets_s(str_buf, MAX_GEOCODE_SIZE);
			system("cls");
			list_transports_by_geocode(*transports, str_buf);
			printf("Press any key to continue...\n");
			_getch();
			break;
		case LIST_TRANSPORTS_BY_DISTANCE:
			system("cls");
			printf("\t\033[0;34m Insert Distance:\n");
			gets_s(str_buf, MAX_GEOCODE_SIZE);
			distance_buf = atoi(str_buf);

			system("cls");
			list_transports_by_distance(*transports, map,logged_account->geocode, distance_buf);
			printf("Press any key to continue...\n");
			_getch();
			break;
		}
	}
}

/** @brief Menu for rentings of Transports
*
* @param[out] rental_transports - linked list that stores all rentals
* @param transports - linked lsit that stores all transports
* @param[out] accounts - linked list that stores all accounts
* @param[out] logged_account - stores data of logged account */
void rent_transport_menu(ListElem* rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account) {
	char str_buf[MAX_BUFFERS_SIZE] = { 0 };
	unsigned int transport_id_to_rent = 0;
	system("cls");
	printf("\tInsert Transport ID to rent:");
	gets_s(str_buf, MAX_BUFFERS_SIZE);
	transport_id_to_rent = atoi(str_buf);

	rent_transport(rental_transports, transports, accounts, logged_account, transport_id_to_rent);

}
