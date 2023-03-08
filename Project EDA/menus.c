#include "menus.h"

void client_main_menu(account_info* logged_account) {
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

void admin_main_menu(account_info* logged_account) {
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
			account_menu(logged_account);
			break;
		case MANAGE_TRANSPORTS:
			transport_menu(logged_account);
			break;
		}
	}
}

void account_menu(account_info* logged_account) {
	unsigned char account_menu_option = NONE;

	while (account_menu_option != EXIT_MENU) {
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
			break;
		case DELETE_ACCOUNT:
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

