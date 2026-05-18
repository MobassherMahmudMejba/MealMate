#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "user.h"
#include "menu.h"
#include "cart.h"
#include "order.h"
#include "feedback.h"
#include "issues.h"
#include "admin.h"

void autoFixMenuFile() {
    FILE *f = fopen("data/menu.txt", "r");
    if (f == NULL) {
        f = fopen("data/menu.txt", "w");
        if (f != NULL) {
            fprintf(f, "1|Paratha with Egg|Breakfast|25.00|50|Fresh paratha with fried egg|1\n");
            fprintf(f, "2|Classic Bengali Khichuri|Lunch|40.00|30|Classic Bengali khichuri|1\n");
            fprintf(f, "3|Chicken Fried Rice|Lunch|60.00|25|Wok rice with chicken|1\n");
            fprintf(f, "4|Crispy fried Singara|Snack|10.00|100|Crispy fried singara|1\n");
            fprintf(f, "5|Spicy beef Halim|Lunch|50.00|20|Spicy beef halim|1\n");
            fclose(f);
        }
    } else {
        fclose(f);
    }
}

int main() {
    srand(time(NULL));
    autoFixMenuFile(); 

    MenuItem globalMenu[50];
    int menuCount = loadMenu(globalMenu, 50);

    char currentStudent[] = "252-35-316"; 
    registerUser(currentStudent, "mejba123", "Mejba Mahmud");
    if (getWalletBalance(currentStudent) == 0.0f) {
        saveWallet(currentStudent, 300.00); 
    }

    int roleChoice;
    while (1) {
        printf("\n=====================================================\n");
        printf("             WELCOME TO CAMPUS MEALMATE              \n");
        printf("=====================================================\n");
        printf("[1] Student Portal\n");
        printf("[2] Admin / Cafeteria Manager Portal\n");
        printf("[0] Exit System\n");
        printf("-----------------------------------------------------\n");
        printf("Select your role: ");
        if (scanf("%d", &roleChoice) != 1) {
            printf("[!] Invalid format!\n");
            getchar(); continue;
        }

        if (roleChoice == 0) {
            printf("\nShutting down MealMate Core Systems. Goodbye!\n");
            return 0;
        }

        if (roleChoice == 2) {
            char pass[20];
            printf("Enter Admin Security Password: ");
            scanf("%s", pass);
            if (strcmp(pass, "admin123") == 0) {
                adminDashboard(globalMenu, &menuCount);
            } else {
                printf("[!] ACCESS DENIED: Invalid Security Password!\n");
            }
            continue;
        }

        if (roleChoice == 1) {
            int choice;
            while (1) {
                printf("\n=====================================================\n");
                printf("             CAMPUS MEALMATE STUDENT PORTAL          \n");
                printf("         Logged in as Student ID: %s                 \n", currentStudent);
                printf("         Current Wallet Balance: %.2f BDT            \n", getWalletBalance(currentStudent));
                printf("=====================================================\n");
                printf("[1] View Cafeteria Menu\n");
                printf("[2] Add Item to Cart\n");
                printf("[3] View Cart & Checkout (Payment)\n");
                printf("[4] View Order History\n");
                printf("[5] Submit Feedback for an Order\n");
                printf("[6] View My Submitted Feedback\n");
                printf("[7] Report an Issue (Support Ticket)\n");
                printf("[8] View My Support Tickets\n");
                printf("[0] Logout to Main Gateway\n");
                printf("-----------------------------------------------------\n");
                printf("Select an option: ");
                scanf("%d", &choice);

                if (choice == 0) break;

                switch (choice) {
                    case 1:
                        menuCount = loadMenu(globalMenu, 50); // Reload values from file
                        displayAllMenu(globalMenu, menuCount);
                        break;
                    case 2: {
                        int itemId, qty;
                        printf("\nEnter Item ID to add: "); scanf("%d", &itemId);
                        printf("Enter Quantity: "); scanf("%d", &qty);
                        int found = 0;
                        for (int i = 0; i < menuCount; i++) {
                            if (globalMenu[i].id == itemId) {
                                addToCart(globalMenu[i], qty); found = 1; break;
                            }
                        }
                        if (!found) printf("[!] Product ID not found!\n");
                        break;
                    }
                    case 3: {
                        viewCart();
                        float total = calculateTotal();
                        if (total > 0) {
                            char confirm;
                            printf("Grand Total: %.2f BDT | Wallet: %.2f BDT\n", total, getWalletBalance(currentStudent));
                            printf("Proceed to Pay? (y/n): ");
                            getchar(); scanf("%c", &confirm);
                            if (confirm == 'y' || confirm == 'Y') {
                                if (deductWalletBalance(currentStudent, total)) placeOrder(currentStudent);
                                else printf("\n[!] TRANSACTION FAILED: Insufficient Balance!\n");
                            }
                        }
                        break;
                    }
                    case 4: displayOrderHistory(currentStudent); break;
                    case 5: {
                        int orderId; printf("\nEnter Order ID: "); scanf("%d", &orderId);
                        submitFeedback(currentStudent, orderId); break;
                    }
                    case 6: viewMyFeedback(currentStudent); break;
                    case 7: reportIssue(currentStudent); break;
                    case 8: viewMyTickets(currentStudent); break;
                    default: printf("[!] Invalid choice!\n");
                }
            }
        }
    }
    return 0;
}
