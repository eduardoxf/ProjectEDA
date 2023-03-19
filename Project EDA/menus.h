#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "accounts.h"
#include "transp.h"
#include "rents.h"

/* General menu options */
#define NONE 0 
#define EXIT_MENU 27

/* Login menu options */
#define SIGN_UP 'Y'
#define LOGIN 'N'

/* Client main menu options */
#define RENT_TRANSPORT 'R'
#define LIST_TRANSPORTS 'L'
#define ADD_BALANCE 'B'

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

/* Login Menu
* Freatures:
* Login and Registring Account
* Arguments:
* accounts_llist - linked list that stores all accounts
* logged_account - will store data of account logged if login sucessfull  */
void login_menu(ListElem* accounts_llist, account_info* logged_account);

/* Menu specific only for clients 
* Freatures:
* Rent Transport, List Transports or Recharge Balance
* Arguments:
* rental_transports - linked list that stores all rentals
* transports_llist - linked lsit that stores all transports
* accounts - linked list that stores all accounts
* logged_account - stores data of logged account */
void client_main_menu(ListElem* rental_transports, ListElem* transports_llist, ListElem* accounts, account_info* logged_account);

/* Menu specific only for admins
* Freatures:
* Manage Accounts and Manage Transports
* Arguments:
* transports_llist - linked lsit that stores all transports
* accounts_llist - linked list that stores all accounts
* logged_account - stores data of logged account */
void admin_main_menu(ListElem* accounts_llist, ListElem* transports_llist, account_info* logged_account);

/* Menu for accounts management(ADMINs Only)
* Freatures:
* Create, Delete or Edit an Account
* Arguments:
* accounts_llist - linked list that stores all accounts
* logged_account - stores data of logged account */
void account_menu(ListElem* accounts_llist, account_info* logged_account);

/* Menu for transport managements(ADMINs Only)
* Freatures:
* Create, Delete or Edit an Transport
* Arguments:
* transports - linked list that stores all transports
* accounts - linked list that stores all accounts
* logged_account - stores data of logged account */
void transport_menu(ListElem* transports, ListElem* accounts, account_info* logged_account);

/* Menu for listings of transports
* Freatures:
* List by Autonomy and Geocode
* Arguments:
* transports - linked list that stores all transports
* logged_account - stores data of logged account */
void list_transport_menu(ListElem* transports, account_info* logged_account);

/* Menu for rentings of Transports
* Arguments:
* rental_transports - linked list that stores all rentals
* transports - linked lsit that stores all transports
* accounts - linked list that stores all accounts
* logged_account - stores data of logged account */
void rent_transport_menu(ListElem* rental_transports, ListElem transports, ListElem* accounts, account_info* logged_account);