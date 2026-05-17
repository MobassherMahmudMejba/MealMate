#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int   id;
    char  name[50];
    char  category[20]; 
    float price;
    int   quantity;
    char  description[100];
    int   available;     
} MenuItem;

typedef struct {
    int   menuItemId;
    char  name[50];
    float price;
    int   qty;
} CartItem;

typedef struct {
    int      orderId;
    char     studentId[20];
    CartItem items[10];
    int      itemCount;
    float    total;
    int      pickupCode;
    char     status[20]; 
    char     date[20];
} Order;

typedef struct {
    char  studentId[20];
    char  password[30];
    char  name[50];
    float walletBalance;
} User;

typedef struct {
    int  ticketId;
    char studentId[20];
    char issue[200];
    char status[20]; 
} IssueTicket;

#endif