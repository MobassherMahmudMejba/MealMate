



#ifndef MENU_H
#define MENU_H
#include "structs.h"

int loadMenu(MenuItem menu[], int maxItems);
void displayAllMenu(MenuItem menu[], int count);
void displayByCategory(MenuItem menu[], int count, const char *category);
void displayDishById(MenuItem menu[], int count, int id);

#endif