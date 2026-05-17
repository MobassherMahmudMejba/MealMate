#ifndef USER_H
#define USER_H
#include "structs.h"

int registerUser(const char *id, const char *password, const char *name);
int loginUser(const char *id, const char *password, User *loggedInUser);
float loadWallet(const char *id);
int saveWallet(const char *id, float newBalance);

#endif