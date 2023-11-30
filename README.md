# Hotel Management System

This is a simple hotel management system implemented in C, providing basic functionalities for managing employees and rooms within a hotel.

## Features

- User authentication for accessing the system.
- Different panels for administrators and reception staff.
- Administrator panel functionalities:
    - Adding employees with their details (ID, name, age, gender, job, salary, phone, address, email).
    - Adding rooms with room-specific details (room number, status, cleaning status, price, bed type, discount percentage).

## Installation

### Prerequisites

- Make sure you have a C compiler installed (e.g., GCC).

### Steps

1. Clone the repository:
    ```bash
    git clone https://github.com/YapWH1208/Hotel-Management-System.git
    ```

2. Navigate to the project directory:
    ```bash
    cd Hotel-Management-System
    ```

3. Compile the code:
    ```bash
    gcc panel.c -o hotel_management_system
    ```

4. Run the executable:
    ```bash
    ./hotel_management_system
    ```

## Usage

Upon running the executable, the system will prompt for login credentials. Use the predefined username and password to access the main panel. From there, you can choose between admin and reception staff logins. Administrators can add employees or rooms, while reception staff can perform tasks related to front desk management.

## Contributors

- Lyu YaXing (@ASTAR)
- Yap WeiHerng (@YapWH1208)
- Lee SinTian (@Tian)
- Cao Rui (@HawkingC)

## License

This project is licensed under the [Apache License 2.0](LICENSE).

