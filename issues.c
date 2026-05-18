#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "issues.h"

void reportIssue(char* studentId) {
    char issueDescription[200];
    printf("\n--- Report an Issue ---\n");
    
    // FIX: ?????????? ?????? fgets ????? ????? ???????? getchar() ????? ???
    printf("Describe your issue: ");
    fgets(issueDescription, sizeof(issueDescription), stdin);
    issueDescription[strcspn(issueDescription, "\n")] = 0; // ???????? ??????? ????? ??? ???
    
    int ticketId = rand() % 9000 + 1000;
    FILE *file = fopen("data/issues.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d|%s|%s|Open\n", ticketId, studentId, issueDescription);
        fclose(file);
        printf("[+] Issue reported successfully! Ticket ID: #%d\n", ticketId);
    }
}

void viewMyTickets(char* studentId) {
    FILE *file = fopen("data/issues.txt", "r");
    if (file == NULL) {
        printf("\n==================== MY TICKETS ====================\n");
        printf("               No issue history found.\n");
        printf("====================================================\n");
        return;
    }
    char line[300], t_studentId[20], t_issue[200], t_status[20];
    int t_ticketId, found = 0;
    printf("\n==================== MY TICKETS ====================\n");
    printf("%-10s | %-10s | %-30s\n", "Ticket ID", "Status", "Issue Description");
    printf("----------------------------------------------------\n");
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d|%[^|]|%[^|]|%[^\n]", &t_ticketId, t_studentId, t_issue, t_status) == 4) {
            if (strcmp(t_studentId, studentId) == 0) {
                printf("#%-9d | %-10s | %-30s\n", t_ticketId, t_status, t_issue);
                found = 1;
            }
        }
    }
    fclose(file);
    if (!found) printf("           No support tickets found for your ID.\n");
    printf("====================================================\n");
}
