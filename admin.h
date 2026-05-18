#ifndef ADMIN_H
#define ADMIN_H
#include "structs.h"

void adminDashboard(MenuItem* globalMenu, int* menuCount);
void viewAllFeedback();
void manageSupportTickets();
void updateMenuPrice(MenuItem* globalMenu, int menuCount);

#endif
