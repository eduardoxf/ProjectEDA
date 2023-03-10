#include "accounts.h"

void cpyAccountData(account_info* data1, account_info* data2) {
	if (data1 != NULL && data2 != NULL) {

		data1->balance = data2->balance;
		data1->nif = data2->nif;
		data1->type = data2->type;
		strcpy(data1->name, data2->name);
		strcpy(data1->password, data2->password);
		strcpy(data1->residence, data2->residence);
		
	}
}

unsigned int compare_account(account_info* data1, account_info* data2) {

	if (data1->nif == data2->nif && strcmp(data1->password, data2->password) == 0) {
		return 1;
	}
	return 0;
}

ListElem read_accounts(ListElem accounts_llist) {

	char str_buf[MAX_BUFFERS_SIZE] = { 0 };

	FILE* fd;

	fd = fopen(ACCOUNTS_FILE, "r");

	if (fd != NULL) {
		account_info aux_buf = { 0 };
		while (fscanf(fd, "%[^:]:%d:%d:%d:%[^:]:%[^:]:\n", aux_buf.name, 
																	&aux_buf.type, 
																	&aux_buf.nif,
																	&aux_buf.balance, 
																	aux_buf.residence, 
																	aux_buf.password) != EOF) {
			account_info* aux = malloc(sizeof(account_info));

			cpyAccountData(aux,&aux_buf);

			accounts_llist = addItemHead(accounts_llist, aux);
		}
		fclose(fd);
	}
	return accounts_llist;
}

void create_account(ListElem accounts_llist, account_info* new_account_data) {
	FILE* fd;

	fd = fopen(ACCOUNTS_FILE, "a");

	if (fd != NULL) {
		fprintf(fd, "\n%s:%d:%d:%d:%s:%s:",
			new_account_data->name,
			new_account_data->type,
			new_account_data->nif,
			new_account_data->balance,
			new_account_data->residence,
			new_account_data->password);
		fclose(fd);
	}

	addItemHead(accounts_llist, new_account_data);
}

void login(ListElem accounts, account_info* logged_account) {


	char str_buf[MAX_PASSWORD_SIZE] = { 0 };
	account_info* aux_buf = malloc(sizeof(account_info));
	ListElem Elem_buf = { 0 };

	system("cls");
	printf("\t\033[0;34m-----------[LOG IN]-----------\n");
	printf("\t Insert NIF: ");
	gets_s(str_buf, MAX_PASSWORD_SIZE);
	aux_buf->nif = atoi(str_buf);

	printf("\t Insert Password: ");
	gets_s(aux_buf->password, MAX_PASSWORD_SIZE);

	Elem_buf = findItemIterative(accounts, aux_buf, &compare_account);
	if (Elem_buf != NULL) {
		cpyAccountData(logged_account, Elem_buf->data);
	}

	free(aux_buf);
}