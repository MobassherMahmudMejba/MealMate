// order.c — Day 3: Order Management Implementation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "order.h"
#include "cart.h"

// ১. সিক্রেট ৬-ডিজিটের ইউনিক পিকআপ কোড জেনারেটর
int generatePickupCode() {
    return rand() % 900000 + 100000; // 100000 থেকে 999999 এর মধ্যে র্যান্ডম কোড
}

// ২. ইন-মেমোরি কার্ট স্টেটকে পারসিস্টেন্ট ডাটাবেসে সেভ করার ফাংশন
void placeOrder(char* studentId) {
    int itemCount = getCartItemCount();
    if (itemCount == 0) {
        printf("[!] Cannot place order. Your cart is empty!\n");
        return;
    }

    float grandTotal = calculateTotal();
    
    // র্যান্ডম আইডি জেনারেশন (৪ ডিজিট)
    int orderId = rand() % 9000 + 1000;
    int pickupCode = generatePickupCode();
    char status[] = "Confirmed";
    char orderDate[] = "2026-05-18"; // কারেন্ট সিস্টেম ডেট

    // ফ্ল্যাট-ফাইল ডাটাবেসে ট্রানজেকশন লগ রাইট করা (Append Mode)
    FILE *file = fopen("data/orders.txt", "a");
    if (file == NULL) {
        printf("[!] Error Accessing Database Table: data/orders.txt\n");
        return;
    }

    // টোকেনাইজড ফরম্যাটে ডাটা রাইট করা হচ্ছে: orderId|studentId|total|pickupCode|status|date
    fprintf(file, "%d|%s|%.2f|%d|%s|%s\n", orderId, studentId, grandTotal, pickupCode, status, orderDate);
    fclose(file);

    printf("\n[✓] Order Placed Successfully!\n");
    printf("Order ID: %d\n", orderId);
    printf("Pickup Code: %d\n", pickupCode);

    // স্টেট রিসেট: অর্ডার কমপ্লিট হওয়ার পর মেমোরি বাফার ক্লিয়ার করা
    clearCart();
}

// ৩. ফাইল থেকে নির্দিষ্ট স্টুডেন্টের আগের সব ট্রানজেকশন হিস্ট্রি পার্স করার ফাংশন
void displayOrderHistory(char* studentId) {
    FILE *file = fopen("data/orders.txt", "r");
    if (file == NULL) {
        printf("\n==================== ORDER HISTORY ====================\n");
        printf("               No order history found.\n");
        printf("=======================================================\n");
        return;
    }

    char line[200];
    int o_id, o_pickup;
    char o_studentId[20], o_status[20], o_date[20];
    float o_total;
    int hasOrders = 0;

    printf("\n==================== ORDER HISTORY ====================\n");
    printf("%-10s | %-10s | %-12s | %-10s\n", "Order ID", "Total (BDT)", "Pickup Code", "Status");
    printf("-------------------------------------------------------\n");

    // Linear Parsing System
    while (fgets(line, sizeof(line), file)) {
        // পাইপ (|) ডেলিমিটার দিয়ে টোকেন আলাদা করা হচ্ছে
        sscanf(line, "%d|%[^|]|%f|%d|%[^|]|%[^\n]", &o_id, o_studentId, &o_total, &o_pickup, o_status, o_date);
        
        if (strcmp(o_studentId, studentId) == 0) {
            printf("%-10d | %-11.2f | %-12d | %-10s\n", o_id, o_total, o_pickup, o_status);
            hasOrders = 1;
        }
    }
    fclose(file);

    if (!hasOrders) {
        printf("         No previous orders found for this Student.\n");
    }
    printf("=======================================================\n");
}