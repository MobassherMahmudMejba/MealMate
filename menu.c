#include <stdio.h>
#include <string.h>
#include "menu.h"

int loadMenu(MenuItem menu[], int maxItems) {
    FILE *file = fopen("data/menu.txt", "r");
    if (file == NULL) return 0;
    int count = 0;
    while (count < maxItems && fscanf(file, "%d|%[^|]|%[^|]|%f|%d|%[^|]|%d\n", 
           &menu[count].id, menu[count].name, menu[count].category, 
           &menu[count].price, &menu[count].quantity, menu[count].description, 
           &menu[count].available) != EOF) {
        count++;
    }
    fclose(file);
    return count;
}

void displayAllMenu(MenuItem menu[], int count) {
    printf("\n=================================== MEALMATE MENU ===================================\n");
    printf("%-4s | %-25s | %-12s | %-10s | %-12s\n", "ID", "Name", "Category", "Price", "Availability");
    printf("-------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-4d | %-25s | %-12s | %-10.2f | %-12s\n", 
               menu[i].id, menu[i].name, menu[i].category, menu[i].price, 
               menu[i].available ? "Available" : "Sold Out");
    }
    printf("=====================================================================================\n");
}

void displayByCategory(MenuItem menu[], int count, const char *category) {
    printf("\n=============================== CATEGORY: %s ===============================\n", category);
    printf("%-4s | %-25s | %-10s | %-12s\n", "ID", "Name", "Price", "Availability");
    printf("-----------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        if (strstr(menu[i].category, category) != NULL) {
            printf("%-4d | %-25s | %-10.2f | %-12s\n", 
                   menu[i].id, menu[i].name, menu[i].price, 
                   menu[i].available ? "Available" : "Sold Out");
        }
    }
    printf("=============================================================================\n");
}

void displayDishById(MenuItem menu[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (menu[i].id == id) {
            printf("\n--- Dish Details ---\n");
            printf("ID: %d\n", menu[i].id);
            printf("Name: %s\n", menu[i].name);
            printf("Category: %s\n", menu[i].category);
            printf("Price: %.2f BDT\n", menu[i].price);
            printf("Stock Qty: %d\n", menu[i].quantity);
            printf("Description: %s\n", menu[i].description);
            printf("Status: %s\n", menu[i].available ? "In Stock" : "Out of Stock");
            printf("--------------------\n");
            return;
        }
    }
    printf("\n[!] Dish with ID %d not found.\n", id);
}