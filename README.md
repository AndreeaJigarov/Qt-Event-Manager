# 📅 Event Management System (C++ & Qt)

A desktop application for managing public events, featuring separate **Administrative** and **User** modes. The project focuses on structured C++ development, file-based persistence, and custom UI components using the Qt framework.

---

### 🛠️ Technical Implementation

* **Tiered Architecture** 🏗️: The project is organized into four layers: **Domain**, **Repository**, **Service**, and **UI**. This separation ensures that business logic, such as event filtering, remains independent of the storage layer or graphical interface.
* **Persistent Storage** 💾: Supports data persistence using **CSV** and **HTML** formats. The repository handles file I/O to save and load event data between sessions.
* **Custom Graphics with QPainter** 📊: Instead of using external libraries, the monthly event distribution chart is implemented manually. It uses `QPainter` to calculate scaling and render bars, axes, and rotated labels directly.
* **Memory Management** 🧠: Demonstrates manual memory management in C++ through the use of **destructors** for service/repository cleanup, alongside the **Qt Parent-Child system** for automatic widget lifecycle management.



---

### 📂 Feature Overview

* **Admin Mode**: Provides full CRUD (Create, Read, Update, Delete) capabilities for the event database and access to the statistical visualization chart.
* **User Mode**: Includes month-based filtering, sequential event browsing with integrated browser-link opening, and personal list management exported to CSV/HTML.
* **Validation Engine**: Centralized validation for `DateTime` objects and string inputs using a custom exception hierarchy to ensure data integrity.

