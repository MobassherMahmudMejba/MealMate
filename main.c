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
        fprintf(f, "2|Classic Bengali Khichuri|Lunch|40.00|30|Classic Bengali khichuri|1\n");
        fprintf(f, "3|Chicken Fried Rice|Lunch|60.00|25|Wok rice with chicken|1\n");
        fprintf(f, "4|Crispy fried Singara|Snack|10.00|100|Crispy fried singara|1\n");
        fprintf(f, "5|Spicy beef Halim|Lunch|50.00|20|Spicy beef halim|1\n");
        fclose(f);
    }
}

int main() {
    srand(time(NULL));
    autoFixMenuFile(); 

    MenuItem globalMenu[50];
    int menuCount = loadMenu(globalMenu, 50);

    // সেশন ট্র্যাকিংয়ের জন্য ডিফল্ট স্টুডেন্ট আইডি ও ওয়ালেট ইনিশিয়ালাইজেশন
    char currentStudent[] = "252-35-316"; 
    registerUser(currentStudent, "mejba123", "Mejba Mahmud");
    saveWallet(currentStudent, 500.00); 

    int choice;
    while (1) {
        printf("\n=====================================================\n");
        printf("             CAMPUS MEALMATE DASHBOARD               \n");
        printf("         Logged in as Student ID: %s                 \n", currentStudent);
        printf("=====================================================\n");
        printf("[1] View Cafeteria Menu\n");
        printf("[2] Add Item to Cart\n");
        printf("[3] View Cart & Checkout\n");
        printf("[4] View Order History\n");
        printf("[5] Submit Feedback for an Order\n");
        printf("[6] View My Submitted Feedback\n");
        printf("[7] Report an Issue (Support Ticket)\n");
        printf("[8] View My Support Tickets\n");
        printf("[0] Exit Application\n");
        printf("-----------------------------------------------------\n");
        printf("Select an option: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("[!] Invalid input format!\n");
            getchar(); // Clear invalid token
            continue;
        }

        switch (choice) {
            case 1:
                displayAllMenu(globalMenu, menuCount);
                break;
                
            case 2: {
                int itemId, qty;
                printf("\nEnter Item ID to add: ");
                scanf("%d", &itemId);
                printf("Enter Quantity: ");
                scanf("%d", &qty);
                
                int found = 0;
                for (int i = 0; i < menuCount; i++) {
                    if (globalMenu[i].id == itemId) {
                        addToCart(globalMenu[i], qty);
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("[!] Product ID not found in inventory!\n");
                break;
            }
                
            case 3: {
                viewCart();
                float total = calculateTotal();
                if (total > 0) {
                    char confirm;
                    printf("Proceed to Place Order? (y/n): ");
                    getchar(); // Clear buffer
                    scanf("%c", &confirm);
                    if (confirm == 'y' || confirm == 'Y') {
                        placeOrder(currentStudent);
                    } else {
                        printf("[*] Checkout canceled. Staging buffer preserved.\n");
                    }
                }
                break;
            }
                
            case 4:
                displayOrderHistory(currentStudent);
                break;
                
            case 5: {
                int orderId;
                printf("\nEnter the Order ID you want to rate: ");
                scanf("%d", &orderId);
                submitFeedback(currentStudent, orderId);
                break;
            }
                
            case 6:
                viewMyFeedback(currentStudent);
                break;
                
            case 7:
                reportIssue(currentStudent);
                break;
                
            case 8:
                viewMyTickets(currentStudent);
                break;
                
            case 0:
                printf("\nClosing session. Thank you for using MealMate!\n");
                return 0;
                
            default:
                printf("[!] Invalid choice! Please select between 0 and 8.\n");
        }
    }
    return 0;
}