#include <stdio.h>
#include <string.h>
#include "user.h"

void registerUser(char* id, char* password, char* name) {
    FILE *f = fopen("data/users.txt", "a+");
    if (f != NULL) {
        fprintf(f, "%s|%s|%s\n", id, password, name);
        fclose(f);
        printf("[?] Account registered successfully for %s!\n", name);
    }
}

int loginUser(char* id, char* password) {
    FILE *f = fopen("data/users.txt", "r");
    if (f == NULL) return 0;
    
    char line[150], f_id[20], f_pass[20], f_name[50];
    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%[^|]|%[^|]|%[^\n]", f_id, f_pass, f_name) == 3) {
            if (strcmp(f_id, id) == 0 && strcmp(f_pass, password) == 0) {
                fclose(f);
                return 1; // Authentication Passed
            }
        }
    }
    fclose(f);
    return 0; // Authentication Failed
}

void saveWallet(char* id, float balance) {
    FILE *f = fopen("data/wallet.txt", "r");
    char lines[100][100];
    int count = 0;
    char f_id[20];
    float f_bal;
    int found = 0;

    if (f != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), f)) {
            if (sscanf(line, "%[^|]|%f", f_id, &f_bal) == 2) {
                if (strcmp(f_id, id) == 0) {
                    sprintf(lines[count++], "%s|%.2f\n", id, balance);
                    found = 1;
                } else {
                    strcpy(lines[count++], line);
                }
            }
        }
        fclose(f);
    }

    if (!found) {
        sprintf(lines[count++], "%s|%.2f\n", id, balance);
    }

    f = fopen("data/wallet.txt", "w");
    if (f != NULL) {
        for (int i = 0; i < count; i++) {
            fputs(lines[i], f);
        }
        fclose(f);
    }
}

float getWalletBalance(char* id) {
    FILE *f = fopen("data/wallet.txt", "r");
    if (f == NULL) return 0.0f;
    char line[100], f_id[20];
    float f_bal;
    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%[^|]|%f", f_id, &f_bal) == 2) {
            if (strcmp(f_id, id) == 0) {
                fclose(f);
                return f_bal;
            }
        }
    }
    fclose(f);
    return 0.0f;
}

int deductWalletBalance(char* id, float amount) {
    float currentBal = getWalletBalance(id);
    if (currentBal < amount) return 0; 
    saveWallet(id, currentBal - amount);
    return 1; 
}

void addWalletFunds(char* id, float amount) {
    float currentBal = getWalletBalance(id);
    saveWallet(id, currentBal + amount);
}
