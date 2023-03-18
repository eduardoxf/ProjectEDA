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

unsigned int compare_account_nif(account_info* data1, account_info* data2) {
	if (data1->nif == data2->nif) {
		return 1;
	}
	else {
		return 0;
	}
}

unsigned int compare_account_pass_nif(account_info* data1, account_info* data2) {

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

void delete_account(ListElem* accounts, account_info* data_of_account_to_delete) {

	*accounts = removeItemIterative(*accounts, data_of_account_to_delete, &compare_account_pass_nif);
	
	save_accounts(*accounts);
}

void edit_account(ListElem* accounts, account_info* data_to_find_account, account_info* new_data) {
	ListElem account_to_edit = { 0 };
	account_info* current_account_data;
	
	account_to_edit = findItemIterative(*accounts, data_to_find_account, &compare_account_nif);
	current_account_data = account_to_edit->data;

	if (new_data->name[0] == 0) {
		strcpy(new_data->name, current_account_data->name);
	}
	if (new_data->type == 0) {
		new_data->type = current_account_data->type;
	}
	if (new_data->password[0] == 0) {
		strcpy(new_data->password, current_account_data->password);
	}
	if (new_data->residence[0] == 0) {
		strcpy(new_data->residence, current_account_data->residence);
	}
	if (new_data->nif == 0) {
		new_data->nif = current_account_data->nif;
	}

	editItemData(account_to_edit,new_data);
	save_accounts(*accounts);
}

void login(ListElem* accounts, account_info* logged_account, account_info* data_to_find_account) {

	ListElem account_to_login = { 0 };

	account_to_login = findItemIterative(*accounts, data_to_find_account, &compare_account_pass_nif);
	if (account_to_login != NULL) {
		cpy_account_data(logged_account, account_to_login->data);
	}
}