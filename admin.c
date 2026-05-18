#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"

void adminDashboard(MenuItem* globalMenu, int* menuCount) {
    int choice;
    while (1) {
        printf("\n=====================================================\n");
        printf("             MEALMATE ADMIN DASHBOARD                \n");
        printf("=====================================================\n");
        printf("[1] View All Student Feedbacks\n");
        printf("[2] Manage Support Tickets (Resolve Issues)\n");
        printf("[3] Update Menu Item Price (Inventory Control)\n");
        printf("[0] Logout & Back to Gateway\n");
        printf("-----------------------------------------------------\n");
        printf("Select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAllFeedback();
                break;
            case 2:
                manageSupportTickets();
                break;
            case 3:
                updateMenuPrice(globalMenu, *menuCount);
                break;
            case 0:
                printf("[*] Logging out from Admin Panel...\n");
                return;
            default:
                printf("[!] Invalid choice!\n");
        }
    }
}

void viewAllFeedback() {
    FILE *file = fopen("data/feedback.txt", "r");
    if (file == NULL) {
        printf("\n[!] No feedback logs found in data/feedback.txt\n");
        return;
    }
    char line[200], studentId[20], comment[100];
    int orderId, rating;
    printf("\n==================== ALL STUDENT FEEDBACKS ====================\n");
    printf("%-15s | %-10s | %-8s | %-30s\n", "Student ID", "Order ID", "Rating", "Comment");
    printf("---------------------------------------------------------------\n");
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^|]|%d|%d|%[^\n]", studentId, &orderId, &rating, comment) == 4) {
            printf("%-15s | %-10d | %-8d | %-30s\n", studentId, orderId, rating, comment);
        }
    }
    fclose(file);
    printf("===============================================================\n");
}

void manageSupportTickets() {
    FILE *file = fopen("data/issues.txt", "r");
    if (file == NULL) {
        printf("\n[!] No support tickets found.\n");
        return;
    }
    char line[300], studentId[20], issue[200], status[20];
    int ticketId;
    
    printf("\n====================== ACTIVE SUPPORT TICKETS ======================\n");
    printf("%-10s | %-15s | %-10s | %-30s\n", "Ticket ID", "Student ID", "Status", "Issue Description");
    printf("--------------------------------------------------------------------\n");
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d|%[^|]|%[^|]|%[^\n]", &ticketId, studentId, issue, status) == 4) {
            printf("#%-9d | %-15s | %-10s | %-30s\n", ticketId, studentId, status, issue);
        }
    }
    fclose(file);
    printf("--------------------------------------------------------------------\n");

    int targetId;
    printf("Enter Ticket ID to resolve (or 0 to cancel): ");
    scanf("%d", &targetId);
    if (targetId == 0) return;

    file = fopen("data/issues.txt", "r");
    FILE *temp = fopen("data/temp_issues.txt", "w");
    int resolved = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d|%[^|]|%[^|]|%[^\n]", &ticketId, studentId, issue, status) == 4) {
            if (ticketId == targetId) {
                fprintf(temp, "%d|%s|%s|Resolved\n", ticketId, studentId, issue);
                resolved = 1;
            } else {
                fprintf(temp, "%d|%s|%s|%s\n", ticketId, studentId, issue, status);
            }
        }
    }
    fclose(file);
    fclose(temp);

    remove("data/issues.txt");
    rename("data/temp_issues.txt", "data/issues.txt");

    if (resolved) printf("[?] Ticket #%d has been successfully marked as RESOLVED!\n", targetId);
    else printf("[!] Ticket ID not found!\n");
}

void updateMenuPrice(MenuItem* globalMenu, int menuCount) {
    int targetId;
    float newPrice;
    printf("\nEnter Menu Item ID to update price: ");
    scanf("%d", &targetId);
    
    int index = -1;
    for (int i = 0; i < menuCount; i++) {
        if (globalMenu[i].id == targetId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("[!] Item ID not found in menu database!\n");
        return;
    }

    printf("Current Price of %s: %.2f BDT\n", globalMenu[index].name, globalMenu[index].price);
    printf("Enter New Price: ");
    scanf("%f", &newPrice);

    if (newPrice <= 0) {
        printf("[!] Invalid Price!\n");
        return;
    }

    globalMenu[index].price = newPrice;

    FILE *file = fopen("data/menu.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < menuCount; i++) {
            fprintf(file, "%d|%s|%s|%.2f|50|%s|1\n", 
                globalMenu[i].id, globalMenu[i].name, globalMenu[i].category, 
                globalMenu[i].price, globalMenu[i].description);
        }
        fclose(file);
        printf("[?] Price updated successfully in menu.txt database!\n");
    }
}
