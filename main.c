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

    char currentStudent[] = "252-35-316"; 
    registerUser(currentStudent, "mejba123", "Mejba Mahmud");
    
    // ???????? ??? ??? ?????? ??? ???? ??????????? ???? ??? ????????? ? ????
    if (getWalletBalance(currentStudent) == 0.0f) {
        saveWallet(currentStudent, 300.00); 
    }

    int choice;
    while (1) {
        printf("\n=====================================================\n");
        printf("             CAMPUS MEALMATE DASHBOARD               \n");
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
        printf("[9] Wallet Management (Add Funds)\n");
        printf("[0] Exit Application\n");
        printf("-----------------------------------------------------\n");
        printf("Select an option: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("[!] Invalid input format!\n");
            getchar(); 
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
                    printf("Grand Total: %.2f BDT\n", total);
                    printf("Your Wallet Balance: %.2f BDT\n", getWalletBalance(currentStudent));
                    printf("Proceed to Place Order & Pay? (y/n): ");
                    getchar(); 
                    scanf("%c", &confirm);
                    if (confirm == 'y' || confirm == 'Y') {
                        // ?? WALLET CHECK & DEDUCTION GATEWAY
                        if (deductWalletBalance(currentStudent, total)) {
                            placeOrder(currentStudent);
                        } else {
                            printf("\n[!] TRANSACTION FAILED: Insufficient Balance!\n");
                            printf("[*] Please select option [9] to load funds into your wallet.\n");
                        }
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
                
            case 9: {
                printf("\n--- WALLET SUBSYSTEM ---\n");
                printf("Current Balance: %.2f BDT\n", getWalletBalance(currentStudent));
                printf("[1] Add Funds (Load Money)\n");
                printf("[2] Back to Main Menu\n");
                printf("Select sub-option: ");
                int w_choice;
                scanf("%d", &w_choice);
                if (w_choice == 1) {
                    float add_amount;
                    printf("Enter amount to add (BDT): ");
                    scanf("%f", &add_amount);
                    if (add_amount > 0) {
                        addWalletFunds(currentStudent, add_amount);
                        printf("[?] %.2f BDT added successfully! New Balance: %.2f BDT\n", add_amount, getWalletBalance(currentStudent));
                    } else {
                        printf("[!] Invalid amount entry!\n");
                    }
                }
                break;
            }
                
            case 0:
                printf("\nClosing session. Thank you for using MealMate!\n");
                return 0;
                
            default:
                printf("[!] Invalid choice! Please select between 0 and 9.\n");
        }
    }
    return 0;
}
