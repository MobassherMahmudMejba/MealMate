// order.h — Day 3: Order Management System
#ifndef ORDER_H
#define ORDER_H

#include "structs.h"

// রোডম্যাপ এবং এসআরএস অনুযায়ী রিকোয়ার্ড ফাংশনসমূহ
int generatePickupCode();
void placeOrder(char* studentId);
void displayOrderHistory(char* studentId);

#endif