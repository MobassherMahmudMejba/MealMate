#ifndef CART_H
#define CART_H
#include "structs.h"

void clearCart(CartItem cart[], int *itemCount);
int addToCart(CartItem cart[], int *itemCount, MenuItem menu[], int menuCount, int dishId, int qty);
int removeFromCart(CartItem cart[], int *itemCount, int dishId);
void viewCart(CartItem cart[], int itemCount);
float calculateTotal(CartItem cart[], int itemCount);

#endif