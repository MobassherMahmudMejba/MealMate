#include <stdio.h>
#include <string.h>
#include "user.h"

int registerUser(const char *id, const char *password, const char *name) {
    FILE *file = fopen("data/users.txt", "r");
    if (file != NULL) {
        User u;
        while (fscanf(file, "%[^|]|%[^|]|%[^|]|%f\n", u.studentId, u.password, u.name, &u.walletBalance) != EOF) {
            if (strcmp(u.studentId, id) == 0) {
                fclose(file);
                return 0; 
            }
        }
        fclose(file);
    }
    file = fopen("data/users.txt", "a");
    if (file == NULL) return -1; 
    fprintf(file, "%s|%s|%s|0.00\n", id, password, name);
    fclose(file);
    return 1; 
}

int loginUser(const char *id, const char *password, User *loggedInUser) {
    FILE *file = fopen("data/users.txt", "r");
    if (file == NULL) return 0;
    User u;
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%f\n", u.studentId, u.password, u.name, &u.walletBalance) != EOF) {
        if (strcmp(u.studentId, id) == 0 && strcmp(u.password, password) == 0) {
            *loggedInUser = u;
            fclose(file);
            return 1; 
        }
    }
    fclose(file);
    return 0; 
}

float loadWallet(const char *id) {
    FILE *file = fopen("data/users.txt", "r");
    if (file == NULL) return 0.0f;
    User u;
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%f\n", u.studentId, u.password, u.name, &u.walletBalance) != EOF) {
        if (strcmp(u.studentId, id) == 0) {
            fclose(file);
            return u.walletBalance;
        }
    }
    fclose(file);
    return 0.0f;
}

int saveWallet(const char *id, float newBalance) {
    FILE *file = fopen("data/users.txt", "r");
    if (file == NULL) return 0;
    User users[100];
    int count = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%f\n", users[count].studentId, users[count].password, users[count].name, &users[count].walletBalance) != EOF) {
        if (strcmp(users[count].studentId, id) == 0) {
            users[count].walletBalance = newBalance;
        }
        count++;
    }
    fclose(file);
    file = fopen("data/users.txt", "w");
    if (file == NULL) return 0;
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s|%s|%s|%.2f\n", users[i].studentId, users[i].password, users[i].name, users[i].walletBalance);
    }
    fclose(file);
    return 1;
}