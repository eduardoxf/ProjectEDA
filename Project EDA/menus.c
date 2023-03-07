#include "menus.h"

void login(ListElem accounts,account_info* logged_account) {


	char str_buf[MAX_PASSWORD_SIZE] = { 0 };
	account_info* aux_buf = malloc(sizeof(account_info));
	ListElem Elem_buf = { 0 };

	system("cls");
	printf("-----------[LOG IN]-----------\n");
	printf("Insert NIF: ");
	gets_s(str_buf, MAX_PASSWORD_SIZE);
	aux_buf->nif = atoi(str_buf);

	printf("Insert Password: ");
	gets_s(aux_buf->password, MAX_PASSWORD_SIZE);

	Elem_buf = findItemIterative(accounts,aux_buf, &compare_account);
	if (Elem_buf != NULL) {
		cpyAccountData(logged_account, Elem_buf->data);
	}
	
	free(aux_buf);
}
