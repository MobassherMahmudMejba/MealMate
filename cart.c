// cart.c — Day 3: Cart Management Implementation
#include <stdio.h>
#include <string.h>
#include "cart.h"

#define MAX_CART_ITEMS 10

// কার্টের ডাটা সাময়িকভাবে জমা রাখার জন্য গ্লোবাল ভ্যারিয়েবল
static CartItem cart[MAX_CART_ITEMS];
static int cartItemCount = 0;

// ১. কার্টে খাবার যোগ করার ফাংশন
void addToCart(MenuItem item, int qty) {
    if (!item.available || item.quantity <= 0) {
        printf("[!] Sorry, item is sold out or unavailable!\n");
        return;
    }
    if (qty <= 0) {
        printf("[!] Invalid quantity! Quantity must be greater than 0.\n");
        return;
    }

    // ডুপ্লিকেট আইটেম চেক: কার্টে অলরেডি থাকলে শুধু কোয়ান্টিটি বাড়িয়ে দেবে
    for (int i = 0; i < cartItemCount; i++) {
        if (cart[i].menuItemId == item.id) {
            cart[i].qty += qty;
            printf("[+] Increased quantity for '%s' in your cart.\n", item.name);
            return;
        }
    }

    // কার্ট ফুল কি না চেক (সর্বোচ্চ ১০টা আলাদা আইটেম)
    if (cartItemCount >= MAX_CART_ITEMS) {
        printf("[!] Your cart is full! Remove an item to add a new one.\n");
        return;
    }

    // নতুন আইটেম কার্টে যোগ করা
    cart[cartItemCount].menuItemId = item.id;
    strcpy(cart[cartItemCount].name, item.name);
    cart[cartItemCount].price = item.price;
    cart[cartItemCount].qty = qty;
    cartItemCount++;

    printf("[+] Added %s (Qty: %d) to your cart successfully.\n", item.name, qty);
}

// ২. কার্ট থেকে আইটেম বাদ দেওয়ার ফাংশন
void removeFromCart(int index) {
    if (index < 0 || index >= cartItemCount) {
        printf("[!] Invalid index! Item not found in cart.\n");
        return;
    }

    printf("[-] Removed '%s' from your cart.\n", cart[index].name);

    // আইটেম রিমুভ করে বাকি আইটেমগুলো বামে শিফট করা
    for (int i = index; i < cartItemCount - 1; i++) {
        cart[i] = cart[i + 1];
    }
    cartItemCount--;
}

// ৩. কার্টের আইটেমগুলো সুন্দর করে স্ক্রিনে দেখানোর ফাংশন
void viewCart() {
    if (cartItemCount == 0) {
        printf("\n================== YOUR CART ==================\n");
        printf("               Cart is empty!\n");
        printf("===============================================\n");
        return;
    }

    printf("\n================== YOUR CART ==================\n");
    printf("%-4s | %-22s | %-5s | %-7s | %-8s\n", "Idx", "Item Name", "Qty", "Price", "Subtotal");
    printf("-----------------------------------------------\n");
    
    for (int i = 0; i < cartItemCount; i++) {
        float subtotal = cart[i].price * cart[i].qty;
        printf("%-4d | %-22s | %-5d | %-7.2f | %-8.2f\n", 
               i, cart[i].name, cart[i].qty, cart[i].price, subtotal);
    }
    
    printf("-----------------------------------------------\n");
    printf("Grand Total: %.2f BDT\n", calculateTotal());
    printf("===============================================\n");
}

// ৪. কার্টের মোট দাম হিসাব করার ফাংশন
float calculateTotal() {
    float total = 0;
    for (int i = 0; i < cartItemCount; i++) {
        total += cart[i].price * cart[i].qty;
    }
    return total;
}

// ৫. কার্ট একবারে খালি করার ফাংশন
void clearCart() {
    cartItemCount = 0;
    printf("[+] Cart cleared successfully.\n");
}

// কাইফের অর্ডার মডিউলের জন্য হেল্পার ফাংশন
int getCartItemCount() {
    return cartItemCount;
}

CartItem* getCartItems() {
    return cart;
}