#include "accounts.h"

/* Copies data from data2 and stores it in data1 
* Arguments:
* data1 - account data buffer that will store the information
* data2 - account data to copy								*/
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

/* Compares if Nif in data1 is equal to Nif in data2
* Arguments:
* data1 - account 1 data to compare
* data2 - account 2 data to compare
* Returns:
* 1 - Nifs are equal
* 0 - Nifs are different							*/
unsigned int compare_account_nif(account_info* data1, account_info* data2) {
	if (data1->nif == data2->nif) {
		return 1;
	}
	else {
		return 0;
	}
}

/* Compares if Nif and Password in data1 is equal to Nif and Password in data2
* Argumens:
* data1 - account 1 data to compare
* data2 - account 2 data to compare
* Returns:
* 1 - Nifs and passwords are equal
* 0 - Nifs and passwords are different										*/
unsigned int compare_account_pass_nif(account_info* data1, account_info* data2) {

	if (data1->nif == data2->nif && strcmp(data1->password, data2->password) == 0) {
		return 1;
	}
	return 0;
}

/* Reads accounts in ACCOUNTS_FILE and stores it in accounts_llist linked list 
* Arguments:
* accounts_llist - linked list where the accounts will be stored            */
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

/* Writes a account in ACCOUNTS_FILE and adds it to accounts linked list 
* Arguments:
* acounts - linked list that stores all accounts 
* new_account_data - data of account to create						  */
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

/* Writes all accounts in ACCOUNTS_FILE
* Arguments:
* accounts - linked list that stores all accounts */
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

/* Deletes account from ACCOUNTS_FILE and accounts linked list 
* Arguments:
* accounts - linked list that stores all accounts
* data_of_account_to_delete - stores data to know which account is to delete
*							  (stores nif of account to delete)           */
void delete_account(ListElem* accounts, account_info* data_of_account_to_delete) {

	*accounts = removeItemIterative(*accounts, data_of_account_to_delete, &compare_account_pass_nif);
	
	save_accounts(*accounts);
}

/* Edits data of an specific account 
* Arguments:
* accounts - linked list that stores all accounts 
* data_to_find_account - stores data to know which account is to edit
*						 (stores nif of account to edit)
* new_data - stores the new data of the account                    */
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

/* Executes the login based on NIF and Password given and if login is sucessfull
* stores data of account logged
* Argumens:
* accounts - linked list that stores all accounts
* logged_account - will store information of account logged 
* data_to_find_account - stores data to know which account is to login
*						 (stores nif and password of account to login)       */
void login(ListElem* accounts, account_info* logged_account, account_info* data_to_find_account) {

	ListElem account_to_login = { 0 };

	account_to_login = findItemIterative(*accounts, data_to_find_account, &compare_account_pass_nif);
	if (account_to_login != NULL) {
		cpy_account_data(logged_account, account_to_login->data);
	}
}

/* Recharges the balance of the account currently acessed
* Arguments:
* accounts - linked list that stores all accounts
* logged_account - account that user is logged
* balance_to_sum - balance to sum to logged account    */
void add_balance_account(ListElem* accounts, account_info* logged_account, int balance_to_sum) {
	account_info* data_buf = NULL;
	ListElem account_to_add_balance = NULL;

	account_to_add_balance = findItemIterative(*accounts, logged_account, &compare_account_nif);

	if (account_to_add_balance != NULL) {
		data_buf = account_to_add_balance->data;

		data_buf->balance += balance_to_sum;
		logged_account->balance += balance_to_sum;

		save_accounts(*accounts);
	}
}

/* Shows data of one account 
* Arguments:
* data - data to show     */
void show_accounts_data(account_info* data) {
	printf("Name: %s\n", data->name);
	printf("Nif: %d\n", data->nif);
	printf("Balance: %d\n", data->balance);
	printf("Admin: %d\n", data->type);
	printf("Password: %s\n", data->password);
	printf("Residence: %s\n", data->residence);
	printf("\n");
}