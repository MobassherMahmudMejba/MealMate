#include <stdio.h>
#include <string.h>
#include "cart.h"

void clearCart(CartItem cart[], int *itemCount) {
    *itemCount = 0;
}

int addToCart(CartItem cart[], int *itemCount, MenuItem menu[], int menuCount, int dishId, int qty) {
    int menuIdx = -1;
    for (int i = 0; i < menuCount; i++) {
        if (menu[i].id == dishId) {
            menuIdx = i;
            break;
        }
    }
    if (menuIdx == -1 || menu[menuIdx].available == 0 || menu[menuIdx].quantity < qty) return 0; 
    for (int i = 0; i < *itemCount; i++) {
        if (cart[i].menuItemId == dishId) {
            if (menu[menuIdx].quantity < (cart[i].qty + qty)) return 0;
            cart[i].qty += qty;
            return 1;
        }
    }
    if (*itemCount >= 10) return 0; 
    cart[*itemCount].menuItemId = dishId;
    snprintf(cart[*itemCount].name, sizeof(cart[*itemCount].name), "%s", menu[menuIdx].name);
    cart[*itemCount].price = menu[menuIdx].price;
    cart[*itemCount].qty = qty;
    (*itemCount)++;
    return 1;
}

int removeFromCart(CartItem cart[], int *itemCount, int dishId) {
    int idx = -1;
    for (int i = 0; i < *itemCount; i++) {
        if (cart[i].menuItemId == dishId) { idx = i; break; }
    }
    if (idx == -1) return 0;
    for (int i = idx; i < (*itemCount) - 1; i++) { cart[i] = cart[i + 1]; }
    (*itemCount)--;
    return 1;
}

void viewCart(CartItem cart[], int itemCount) {
    printf("\n=================== YOUR CART ===================\n");
    if (itemCount == 0) {
        printf("Your cart is empty.\n");
        printf("=================================================\n");
        return;
    }
    printf("%-25s | %-5s | %-10s\n", "Item Name", "Qty", "Subtotal");
    printf("-------------------------------------------------\n");
    float grandTotal = 0;
    for (int i = 0; i < itemCount; i++) {
        float sub = cart[i].price * cart[i].qty;
        printf("%-25s | %-5d | %-10.2f\n", cart[i].name, cart[i].qty, sub);
        grandTotal += sub;
    }
    printf("-------------------------------------------------\n");
    printf("Grand Total: %.2f BDT\n", grandTotal);
    printf("=================================================\n");
}

float calculateTotal(CartItem cart[], int itemCount) {
    float total = 0;
    for (int i = 0; i < itemCount; i++) { total += cart[i].price * cart[i].qty; }
    return total;
}