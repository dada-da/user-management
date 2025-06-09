#include <iostream>
#include <fstream>
#include <regex>
#include "UserManager.h"

const std::string LOGIN_LOG_PATH = "C:\\Users\\ADMIN\\Desktop\\BaitapnhomHN\\users.txt";

// Kiem tra username hop le
bool isValidUsername(const std::string& username) {
    std::regex pattern("^[a-zA-Z0-9_]{4,20}$");
    return std::regex_match(username, pattern);
}

// Kiem tra password hop le
bool isValidPassword(const std::string& password) {
    std::regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{6,}$");
    return std::regex_match(password, pattern);
}

// Nhap username hop le v� chua ton tai
std::string inputNewUsername(UserManager& manager) {
    std::string username;
    do {
        std::cout << "Nhap Username: ";
        std::getline(std::cin, username);

        if (!isValidUsername(username)) {
            std::cout << "Username khong hop le. Chi duoc dung chu, so, dau gach duoi, tu 4-20 ky tu.\n";
        } else if (manager.usernameExists(username)) {
            std::cout << "Username da ton tai. Vui long chon ten khac.\n";
        } else {
            break;
        }
    } while (true);
    return username;
}

// Nhap username khi dang nhap
std::string inputUsername() {
    std::string username;
    do {
        std::cout << "Nhap Username: ";
        std::getline(std::cin, username);
        if (!isValidUsername(username)) {
            std::cout << "Username khong hop le. Chi duoc dung chu, so, dau gach duoi, tu 4-20 ky tu.\n";
        }
    } while (!isValidUsername(username));
    return username;
}

// Nhap mat khau hop le
std::string inputPassword() {
    std::string password;
    do {
        std::cout << "Nhap Password: ";
        std::getline(std::cin, password);
        if (!isValidPassword(password)) {
            std::cout << "Password phai it nhat 6 ky tu, co chu hoa, chu thuong va so.\n";
        }
    } while (!isValidPassword(password));
    return password;
}

// Ghi log nguoi dung da dang nhap v�o file
void logUsername(const std::string& username) {
    std::ofstream out(LOGIN_LOG_PATH, std::ios::app);
    if (out.is_open()) {
        out << "Dang nhap: " << username << "\n";
        out.close();
    } else {
        std::cerr << "Khong the mo file log de ghi.\n";
    }
}

int main() {
    UserManager manager("users.txt");

    while (true) {
        std::cout << "\n=== MENU ===\n";
        std::cout << "1. Dang nhap\n";
        std::cout << "2. Dang ky\n";
        std::cout << "3. Thoat chuong trinh\n";
        std::cout << "Chon: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::cout << "\n--- Dang nhap ---\n";
            std::string username = inputUsername();
            std::string password = inputPassword();

            Role role;
            if (manager.loginUser(username, password, role)) {
                std::cout << "Dang nhap thanh cong! Vai tro: " << (role == Role::ADMIN ? "Admin" : "User") << "\n";
                logUsername(username); // Ghi log
            } else {
                std::cout << "Dang nhap that bai. Ten dang nhap hoac mat khau sai.\n";
            }

        } else if (choice == 2) {
            std::cout << "\n--- Dang ky ---\n";
            std::string username = inputNewUsername(manager); // kiem tra ton tai
            std::string password = inputPassword();

            int roleChoice;
            std::cout << "Nhap vai tro (1 = Admin, 0 = User): ";
            std::cin >> roleChoice;
            std::cin.ignore();

            Role role = roleChoice == 1 ? Role::ADMIN : Role::USER;
            if (manager.registerUser(username, password, role)) {
                std::cout << "Dang ky thanh cong!\n";
            }

        } else if (choice == 3) {
            std::cout << "Tam biet!\n";
            break;
        } else {
            std::cout << "Lua chon khong hop le. Moi chon lai.\n";
        }
    }

    return 0;
}

