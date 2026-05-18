#include <stdio.h>
#include <string.h>
#include "feedback.h"
void submitFeedback(char* studentId, int orderId) {
    int rating; char comment[100];
    printf("\n--- Submit Feedback for Order #%d ---\n", orderId);
    do {
        printf("Enter Rating (1-5): ");
        scanf("%d", &rating);
        if (rating < 1 || rating > 5) printf("[!] Invalid rating!\n");
    } while (rating < 1 || rating > 5);
    getchar();
    printf("Enter Comment: ");
    fgets(comment, sizeof(comment), stdin);
    comment[strcspn(comment, "\n")] = 0;
    FILE *file = fopen("data/feedback.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s|%d|%d|%s\n", studentId, orderId, rating, comment);
        fclose(file);
        printf("[+] Feedback submitted successfully.\n");
    }
}
void viewMyFeedback(char* studentId) {
    FILE *file = fopen("data/feedback.txt", "r");
    if (file == NULL) return;
    char line[200], f_studentId[20], f_comment[100];
    int f_orderId, f_rating, found = 0;
    printf("\n==================== MY FEEDBACK ====================\n");
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^|]|%d|%d|%[^\n]", f_studentId, &f_orderId, &f_rating, f_comment) == 4) {
            if (strcmp(f_studentId, studentId) == 0) {
                printf("Order ID: %d | Rating: %d | Comment: %s\n", f_orderId, f_rating, f_comment);
                found = 1;
            }
        }
    }
    fclose(file);
    if (!found) printf("No feedback found.\n");
    printf("=====================================================\n");
}
