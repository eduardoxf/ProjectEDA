#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "accounts.h"

#define NONE 0 
#define MANAGE_ACCOUNTS 'A'
#define MANAGE_TRANSPORTS 'T'
#define EXIT_MENU 27

void main_menu(account_info* logged_account);

void account_menu(account_info* logged_account);