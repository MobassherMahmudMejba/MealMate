#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "order.h"
#include "user.h"

int generatePickupCode() { return rand() % 900000 + 100000; }

int placeOrder(const char *studentId, CartItem cart[], int itemCount, float total) {
    float balance = loadWallet(studentId);
    if (balance < total) {
        printf("\n[!] Checkout Failed: Insufficient wallet balance.\n");
        return 0; 
    }
    saveWallet(studentId, balance - total);
    FILE *file = fopen("data/orders.txt", "a");
    if (file == NULL) return -1;
    int orderId = rand() % 9000 + 1000;
    int pCode = generatePickupCode();
    fprintf(file, "%d|%s|%.2f|%d|Confirmed|2026-05-17\n", orderId, studentId, total, pCode);
    fclose(file);
    printf("\n[✓] Order Placed Successfully!\n");
    printf("Order ID: %d\n", orderId);
    printf("Pickup Code: %d\n", pCode);
    return 1;
}

void displayOrderHistory(const char *studentId) {
    FILE *file = fopen("data/orders.txt", "r");
    printf("\n==================== ORDER HISTORY ====================\n");
    if (file == NULL) { printf("No orders found.\n=======================================================\n"); return; }
    int id, pCode;
    char stId[20], status[20], date[20];
    float total; int found = 0;
    printf("%-10s | %-10s | %-12s | %-10s\n", "Order ID", "Total", "Pickup Code", "Status");
    printf("-------------------------------------------------------\n");
    while (fscanf(file, "%d|%[^|]|%f|%d|%[^|]|%s\n", &id, stId, &total, &pCode, status, date) != EOF) {
        if (strcmp(stId, studentId) == 0) {
            printf("%-10d | %-10.2f | %-12d | %-10s\n", id, total, pCode, status);
            found = 1;
        }
    }
    fclose(file);
    if (!found) printf("No past orders.\n");
    printf("=======================================================\n");
}