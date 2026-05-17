#ifndef ORDER_H
#define ORDER_H
#include "structs.h"

int generatePickupCode();
int placeOrder(const char *studentId, CartItem cart[], int itemCount, float total);
void displayOrderHistory(const char *studentId);

#endif