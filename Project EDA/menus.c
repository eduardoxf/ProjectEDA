#include "menus.h"

void login_menu(ListElem* accounts_llist, account_info* logged_account) {
	unsigned char menu_option = NONE;
	char str_buf[MAX_BUFFERS_SIZE] = { 0 };

	while (logged_account->nif == NULL) {
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

void client_main_menu(ListElem* accounts_llist, account_info* logged_account) {
	unsigned char menu_option = NONE;

	while (menu_option != EXIT_MENU) {
		system("cls");
		printf("\t\033[0;34m-------------[ MENU ]-------------\t \033[0;36mLogged Account\n");
		printf("\t\033[0;34m  %c  - List Transports\t\t\t   \033[0;36mName: %s\n", LIST_TRANSPORTS, logged_account->name);
		printf("\t\033[0;34m  %c  - Rent Transport\t\t\t   \033[0;36mNIF: %d\n", RENT_TRANSPORT, logged_account->nif);
		printf("\t\033[0;34m  ESC - EXIT\t\t\t\t   \033[0;36mBalance: %d\n", logged_account->balance);
		printf("\t\t\t\t\t\t   \033[0;36mResidence: %s\n", logged_account->residence);
		menu_option = _getch();
		menu_option = toupper(menu_option);
		switch (menu_option) {
		case LIST_TRANSPORTS:
			list_transport_menu(logged_account);
			break;
		case RENT_TRANSPORT:
			break;
		}
	}
}

void admin_main_menu(ListElem* accounts_llist, account_info* logged_account) {
	unsigned char menu_option = NONE;

	while (menu_option != EXIT_MENU) {
		system("cls");
		printf("\t\033[0;34m-------------[ MENU ]-------------\t \033[0;36mLogged Account\n");
		printf("\t\033[0;34m  %c  - Manage Accounts\t\t\t   \033[0;36mName: %s\n", MANAGE_ACCOUNTS,logged_account->name);
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
			transport_menu(logged_account);
			break;
		}
	}
}

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

			printf("\t\033[0;34mIs the new account an Admin?(1 - Yes,0 - No)\n");
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
			break;
		}
	}
}

void transport_menu(account_info* logged_account) {
	unsigned char transport_menu_option = NONE;

	while (transport_menu_option != EXIT_MENU) {
		system("cls");
		printf("\t\033[0;34m-------------[ MENU ]-------------\t \033[0;36mLogged Account\n");
		printf("\t\033[0;34m  %c  - Add Transport\t\t\t   \033[0;36mName: %s\n", CREATE_TRANSPORT, logged_account->name);
		printf("\t\033[0;34m  %c  - Remove Transport\t\t\t   \033[0;36mNIF: %d\n", DELETE_TRANSPORT, logged_account->nif);
		printf("\t\033[0;34m  %c  - Edit Transport\t\t\t   \033[0;36mBalance: %d\n", EDIT_TRANSPORT, logged_account->balance);
		printf("\t\033[0;34m  %c  - List Transports\t\t\t   \033[0;36mResidence: %s\n", LIST_TRANSPORTS, logged_account->residence);
		printf("\t\033[0;34m  ESC - Back");
		transport_menu_option = _getch();
		transport_menu_option = toupper(transport_menu_option);
		switch (transport_menu_option) {
		case CREATE_TRANSPORT:
			break;
		case DELETE_TRANSPORT:
			break;
		case EDIT_TRANSPORT:
			break;
		case LIST_TRANSPORTS:
			list_transport_menu(logged_account);
			break;
		}
	}
}

void list_transport_menu(account_info* logged_account) {
	unsigned char list_transport_menu_option = NONE;
	while (list_transport_menu_option!=EXIT_MENU)
	{
		system("cls");
		printf("\t\033[0;34m-------------[ MENU ]-------------\t \033[0;36mLogged Account\n");
		printf("\t\033[0;34m  %c  - List Transports by autonomy\t   \033[0;36mName: %s\n", LIST_TRANSPORTS_BY_AUTONOMY, logged_account->name);
		printf("\t\033[0;34m  %c  - List Transports by location\t   \033[0;36mNIF: %d\n", LIST_TRANSPORTS_BY_LOCATION, logged_account->nif);
		printf("\t\033[0;34m  ESC - Back\t\t\t\t   \033[0;36mBalance: %d\n", logged_account->balance);
		printf("\t\t\t\t\t\t   \033[0;36mResidence: %s\n", logged_account->residence);
		list_transport_menu_option = _getch();
		list_transport_menu_option = toupper(list_transport_menu_option);
		switch (list_transport_menu_option) {
		case LIST_TRANSPORTS_BY_AUTONOMY:
			break;
		case LIST_TRANSPORTS_BY_LOCATION:
			break;
		}
	}
}

