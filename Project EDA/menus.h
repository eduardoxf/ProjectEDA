#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "accounts.h"
#include "ll.h"

void login(ListElem accounts, account_info* logged_account);
