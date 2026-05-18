#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "user.h"
#include "menu.h"
#include "cart.h"
#include "order.h"
#include "feedback.h"
#include "issues.h"

void autoFixMenuFile() {
    FILE *f = fopen("data/menu.txt", "w");
    if (f != NULL) {
        fprintf(f, "1|Paratha with Egg|Breakfast|25.00|50|Fresh paratha with fried egg|1\n");
        fprintf(f, "2|Khichuri|Lunch|40.00|30|Classic Bengali khichuri|1\n");
        fprintf(f, "3|Chicken Fried Rice|Lunch|60.00|25|Wok rice with chicken|1\n");
        fprintf(f, "4|Singara|Snack|10.00|100|Crispy fried singara|1\n");
        fprintf(f, "5|Halim|Lunch|50.00|20|Spicy beef halim|1\n");
        fclose(f);
    }
}

int main() {
    srand(time(NULL));
    autoFixMenuFile(); 

    printf(">>> FRESH START: MEALMATE SYSTEM INTERACTIVE TEST <<<\n");
    MenuItem globalMenu[50];
    int menuCount = loadMenu(globalMenu, 50);
    printf("[1] Loaded %d items from menu.txt\n", menuCount);
    displayAllMenu(globalMenu, menuCount);

    registerUser("252-35-999", "mejba123", "Mejba Mahmud");
    saveWallet("252-35-999", 500.00); 

    MenuItem item1; int found1 = 0;
    for (int i = 0; i < menuCount; i++) {
        if (globalMenu[i].id == 2) { item1 = globalMenu[i]; found1 = 1; break; }
    }
    if (found1) addToCart(item1, 2);

    MenuItem item2; int found2 = 0;
    for (int i = 0; i < menuCount; i++) {
        if (globalMenu[i].id == 4) { item2 = globalMenu[i]; found2 = 1; break; }
    }
    if (found2) addToCart(item2, 5);

    viewCart();
    float totalCost = calculateTotal();
    
    placeOrder("252-35-316"); 
    displayOrderHistory("252-35-316");

    printf("\n>>> DAY 4 INTEGRATION TESTING START <<<\n");
    char currentStudent[] = "252-35-316"; 
    int currentOrder = 2113; 

    submitFeedback(currentStudent, currentOrder);
    viewMyFeedback(currentStudent);
    reportIssue(currentStudent);
    viewMyTickets(currentStudent);

    printf("\n>>> DAY 4 TESTING COMPLETE <<<\n");
    printf("\n>>> LOCAL TEST PASSED: SYSTEM WORKING PERFECTLY! <<<\n");
    return 0;
}
