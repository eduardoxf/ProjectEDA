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
