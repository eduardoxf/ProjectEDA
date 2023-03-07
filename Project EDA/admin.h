#pragma once

#define MAX_ADMIN_NAME_SIZE 30
#define MAX_ADMIN_PASSWORD_SIZE 30

typedef struct admins_data_s{
	char name[MAX_ADMIN_NAME_SIZE];
	unsigned int nif;
	char password[MAX_ADMIN_PASSWORD_SIZE];
	struct admins_data_s* next;
}* admins_data;

