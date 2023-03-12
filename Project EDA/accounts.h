#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ll.h"

/* Should be at least the same size of the biggest data in the accounts data structure */
#define MAX_BUFFERS_SIZE 75
#define MAX_NAME_SIZE 30
#define MAX_RESIDENCE_SIZE 75
#define MAX_PASSWORD_SIZE 30

#define ADMIN 1
#define CLIENT 2

#define ACCOUNTS_FILE "accounts.txt"

typedef struct {
	char name[MAX_NAME_SIZE];
	unsigned int type;
	unsigned int nif;
	unsigned int balance;
	char residence[MAX_RESIDENCE_SIZE];
	char password[MAX_PASSWORD_SIZE];
}account_info;

void cpy_account_data(account_info* data1, account_info* data2);

unsigned int compare_account_nif(account_info* data1, account_info* data2);

unsigned int compare_account_pass_nif(account_info* data1, account_info* data2);

void read_accounts(ListElem* accounts_llist);

void login(ListElem* accounts, account_info* logged_account, account_info* data);

void delete_account(ListElem* accounts, account_info* data_of_account_to_delete);

void create_account(ListElem* accounts, account_info* new_account_data);

void edit_account(ListElem* accounts, account_info* data_to_find_account, account_info* new_data);

void save_accounts(ListElem accounts);