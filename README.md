# 🍔 MealMate: The Ultimate CLI Cafeteria Manager 🚀

![Version](https://img.shields.io/badge/Version-1.0_Production-brightgreen?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)
![Architecture](https://img.shields.io/badge/Architecture-Modular-orange?style=for-the-badge)

> **No more waiting in chaotic cafeteria lines. No more lost paper tickets. Order your food at the speed of logic.**

Welcome to **MealMate** — a lightning-fast, highly modular, and fully persistent Command Line Interface (CLI) Cafeteria Management System built entirely in C. Designed for university campuses, MealMate bridges the gap between hungry students and busy cafeteria managers through a seamless, automated terminal experience.

---

## 🔥 Key Features 

* 🔐 **Role-Based Access Control (RBAC):** A secure dual-gateway system. Students can log in to order food, while Admins get a God-Mode dashboard to manage the entire ecosystem.
* 💳 **Dynamic Wallet Subsystem:** Real-time transaction handling! Students can load funds into their digital wallets. The system verifies balances and deducts BDT instantly before confirming an order.
* 🗄️ **Persistent Text-Database:** No data is lost when you close the app. We engineered a robust File I/O architecture using `.txt` files (`users.txt`, `menu.txt`, `wallet.txt`, `issues.txt`) acting as a lightweight, blazing-fast database.
* 📝 **Support Desk & Feedback Engine:** Students can rate their completed orders and open support tickets for any issues. Admins can view these logs and mark tickets as "Resolved" in real-time.
* 🧱 **100% Modular Architecture:** Goodbye, spaghetti code! MealMate is strictly decoupled into independent sub-systems (`.h` and `.c` files) for Cart, Order, User Auth, and Admin mechanics.

---

## 🛠️ System Architecture

MealMate is powered by independent logical blocks communicating through a master loop:
1.  **`user.c`**: Handles dynamic authentication, registration, and wallet fund management.
2.  **`menu.c` & `cart.c`**: Fetches the live menu from the disk and manages volatile RAM-based staging buffers for food selection.
3.  **`order.c`**: The execution engine that deducts funds, generates unique pickup codes, and saves order history.
4.  **`admin.c`**: The manager portal for updating food prices, reading feedback, and resolving tickets.
5.  **`feedback.c` & `issues.c`**: Customer success tracking via file appending and line-by-line parsing.

---

## 🚀 How to Install & Run

You don't need heavy IDEs to run MealMate. Just a native C compiler (GCC) and your terminal.

**1. Clone the Repository:**
```bash
git clone [https://github.com/MobassherMahmudMejba/MealMate.git](https://github.com/MobassherMahmudMejba/MealMate.git)
cd MealMate
