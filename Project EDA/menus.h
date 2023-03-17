#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "accounts.h"
#include "transp.h"

/* General menu options */
#define NONE 0 
#define EXIT_MENU 27

/* Login menu options */
#define SIGN_UP 'Y'
#define LOGIN 'N'

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

void login_menu(ListElem* accounts_llist, account_info* logged_account);

void client_main_menu(ListElem* rental_transports, ListElem* transports_llist, account_info* logged_account);

void admin_main_menu(ListElem* accounts_llist, ListElem* transports_llist, account_info* logged_account);

void account_menu(ListElem* accounts_llist, account_info* logged_account);

void transport_menu(ListElem* transports, account_info* logged_account);

void list_transport_menu(ListElem* transports, account_info* logged_account);

void rent_transport_menu(ListElem* rental_transports, ListElem transports, account_info* logged_account);