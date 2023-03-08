#include "menus.h"

void main_menu(account_info* logged_account) {
	unsigned char menu_option = NONE;

	while (menu_option != EXIT_MENU) {
		system("cls");
		printf("\t\033[0;34m----------[ MENU ]----------\t\t \033[0;36mLogged Account\n");
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
			printf("transports");
			_getch();
			break;
		}
	}
}

void account_menu(account_info* logged_account) {

}

