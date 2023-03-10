#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "accounts.h"

/* General menu options */
#define NONE 0 
#define EXIT_MENU 27

/* Client main menu options */
#define RENT_TRANSPORT 'R'
#define LIST_TRANSPORTS 'L'

/* Admin main menu options */
#define MANAGE_ACCOUNTS 'A'
#define MANAGE_TRANSPORTS 'T'

/* Accounts menu options */
#define CREATE_ACCOUNT 'C'
#define DELETE_ACCOUNT 'D'
#define EDIT_ACCOUNT 'E'

/* Transports menu options */
#define CREATE_TRANSPORT 'C'
#define DELETE_TRANSPORT 'D'
#define EDIT_TRANSPORT 'E'

/* List Transports menu options */
#define LIST_TRANSPORTS_BY_AUTONOMY 'A'
#define LIST_TRANSPORTS_BY_LOCATION 'L'

void client_main_menu(ListElem* accounts_llist, account_info* logged_account);

void admin_main_menu(ListElem* accounts_llist, account_info* logged_account);

void account_menu(ListElem* accounts_llist, account_info* logged_account);

void transport_menu(account_info* logged_account);

void list_transport_menu(account_info* logged_account);