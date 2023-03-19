#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ll.h"

/* Should be at least the same size of the biggest data in the accounts data structure */
#define MAX_BUFFERS_SIZE 75

/* Sizes of each string in accounts data structures */
#define MAX_NAME_SIZE 30
#define MAX_RESIDENCE_SIZE 75
#define MAX_PASSWORD_SIZE 30

/* Type of Account */
#define ADMIN 1
#define CLIENT 2

/* Path of File that stores accounts */
#define ACCOUNTS_FILE "accounts.txt"

/* Data structure of an account in the linked list */
typedef struct {
	/* Name: Cant have spaces */
	char name[MAX_NAME_SIZE];
	/* Type: ADMIN or Client */
	unsigned int type;
	unsigned int nif;
	int balance;
	char residence[MAX_RESIDENCE_SIZE];
	char password[MAX_PASSWORD_SIZE];
}account_info;

/* Copies data from data2 and stores it in data1
* Arguments:
* data1 - account data buffer that will store the information
* data2 - account data to copy								*/
void cpy_account_data(account_info* data1, account_info* data2);

/* Compares if Nif in data1 is equal to Nif in data2
* Arguments:
* data1 - account 1 data to compare
* data2 - account 2 data to compare
* Returns:
* 1 - Nifs are equal
* 0 - Nifs are different							*/
unsigned int compare_account_nif(account_info* data1, account_info* data2);

/* Compares if Nif and Password in data1 is equal to Nif and Password in data2
* Argumens:
* data1 - account 1 data to compare
* data2 - account 2 data to compare
* Returns:
* 1 - Nifs and passwords are equal
* 0 - Nifs and passwords are different										*/
unsigned int compare_account_pass_nif(account_info* data1, account_info* data2);

/* Reads accounts in ACCOUNTS_FILE and stores it in accounts_llist linked list
* Arguments:
* accounts_llist - linked list where the accounts will be stored            */
void read_accounts(ListElem* accounts_llist);

/* Executes the login based on NIF and Password given and if login is sucessfull
* stores data of account logged
* Argumens:
* accounts - linked list that stores all accounts
* logged_account - will store information of account logged
* data_to_find_account - stores data to know which account is to login
*						 (stores nif and password of account to login)       */
void login(ListElem* accounts, account_info* logged_account, account_info* data);

/* Deletes account from ACCOUNTS_FILE and accounts linked list
* Arguments:
* accounts - linked list that stores all accounts
* data_of_account_to_delete - stores data to know which account is to delete
*							  (stores nif of account to delete)           */
void delete_account(ListElem* accounts, account_info* data_of_account_to_delete);


/* Writes a account in ACCOUNTS_FILE and adds it to accounts linked list
* Arguments:
* acounts - linked list that stores all accounts
* new_account_data - data of account to create						  */
void create_account(ListElem* accounts, account_info* new_account_data);

/* Edits data of an specific account
* Arguments:
* accounts - linked list that stores all accounts
* data_to_find_account - stores data to know which account is to edit
*						 (stores nif of account to edit)
* new_data - stores the new data of the account                    */
void edit_account(ListElem* accounts, account_info* data_to_find_account, account_info* new_data);

/* Writes all accounts in ACCOUNTS_FILE
* Arguments:
* accounts - linked list that stores all accounts */
void save_accounts(ListElem accounts);

/* Recharges the balance of the account currently acessed
* Arguments:
* accounts - linked list that stores all accounts
* logged_account - account that user is logged
* balance_to_sum - balance to sum to logged account    */
void add_balance_account(ListElem* accounts, account_info* logged_account, int balance_to_sum);

/* Shows data of one account
* Arguments:
* data - data to show     */
void show_accounts_data(account_info* data);
