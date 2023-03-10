#include "accounts.h"

void cpy_account_data(account_info* data1, account_info* data2) {
	if (data1 != NULL && data2 != NULL) {

		data1->balance = data2->balance;
		data1->nif = data2->nif;
		data1->type = data2->type;
		strcpy_s(data1->name, MAX_NAME_SIZE, data2->name);
		strcpy_s(data1->password, MAX_PASSWORD_SIZE, data2->password);
		strcpy_s(data1->residence, MAX_RESIDENCE_SIZE, data2->residence);
		
	}
}

unsigned int compare_account(account_info* data1, account_info* data2) {

	if (data1->nif == data2->nif && strcmp(data1->password, data2->password) == 0) {
		return 1;
	}
	return 0;
}

void read_accounts(ListElem* accounts_llist) {

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

			cpy_account_data(aux,&aux_buf);

			*accounts_llist = addItemHead(*accounts_llist, aux);
		}
		fclose(fd);
	}
}

void create_account(ListElem* accounts, account_info* new_account_data) {
	FILE* fd;

	fd = fopen(ACCOUNTS_FILE, "a");

	if (fd != NULL) {
		fprintf(fd, "%s:%d:%d:%d:%s:%s:\n",
			new_account_data->name,
			new_account_data->type,
			new_account_data->nif,
			new_account_data->balance,
			new_account_data->residence,
			new_account_data->password);
		
		*accounts = addItemHead(*accounts, new_account_data);
		fclose(fd);
	}
}

void save_accounts(ListElem accounts) {
	FILE* fd;
	fd = fopen(ACCOUNTS_FILE, "w");
	account_info* account_data = NULL;

	if (fd != NULL) {
		while (accounts != NULL) {
			account_data = accounts->data;
			fprintf(fd, "%s:%d:%d:%d:%s:%s:\n",
				account_data->name,
				account_data->type, 
				account_data->nif,
				account_data->balance,
				account_data->residence,
				account_data->password);

			accounts = accounts->next;
		}
		fclose(fd);
	}
}

void delete_account(ListElem* accounts, account_info* account_data) {

	*accounts = removeItemIterative(*accounts, account_data, &compare_account);
	
	save_accounts(*accounts);
}

void login(ListElem* accounts, account_info* logged_account, account_info* data) {

	ListElem Elem_buf = { 0 };

	Elem_buf = findItemIterative(*accounts, data, &compare_account);
	if (Elem_buf != NULL) {
		cpy_account_data(logged_account, Elem_buf->data);
	}
}