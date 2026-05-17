// cart.h — Day 3: Cart Management Function Declarations
#ifndef CART_H
#define CART_H

#include "structs.h"

// ফাংশন ডিক্লেয়ারেশন
void addToCart(MenuItem item, int qty);
void removeFromCart(int index);
void viewCart();
float calculateTotal();
void clearCart();

int getCartItemCount();
CartItem* getCartItems();

#endif