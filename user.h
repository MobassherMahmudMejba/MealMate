#ifndef USER_H
#define USER_H

void registerUser(char* id, char* password, char* name);
int loginUser(char* id, char* password);
void saveWallet(char* id, float balance);
float getWalletBalance(char* id);
int deductWalletBalance(char* id, float amount);
void addWalletFunds(char* id, float amount);

#endif
