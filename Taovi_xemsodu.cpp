#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <set>
#include <limits>

using namespace std;

struct Wallet {
    string username;
    string id;
    long balance = 50000;
    int points = 50;
    bool created = false;
};

// Danh sach cac ID da tao de tranh trung
set<string> usedIDs;

// Ham tao ma dinh danh duy nhat gom 6 chu so
string generateUniqueID() {
    string id;
    do {
        id = to_string(rand() % 900000 + 100000);
    } while (usedIDs.count(id));
    usedIDs.insert(id);
    return id;
}

// Ham tao vi nguoi dung
bool createWallet(Wallet &wallet, const string &loggedInUser) {
    string inputUser;
    do {
        cout << "Nhap Username: ";
        getline(cin, inputUser);
        if (inputUser != loggedInUser) {
            cout << "Username khong dung. Vui long nhap lai.\n";
        }
    } while (inputUser != loggedInUser);

    wallet.username = loggedInUser;
    wallet.id = generateUniqueID();
    wallet.balance = 50000;
    wallet.points = 50;
    wallet.created = false;

    cout << "\n=== THONG TIN VI DUOC TAO ===\n";
    cout << "Ten nguoi dung: " << wallet.username << endl;
    cout << "Ma dinh danh Username: " << wallet.id << endl;
    cout << "So du tai khoan: " << wallet.balance << " VND\n";
    cout << "Diem vi nguoi dung: " << wallet.points << " diem\n";

    string confirmID;
    cout << "\nNhap lai ma dinh danh de xac nhan: ";
    getline(cin, confirmID);

    if (confirmID == wallet.id) {
        wallet.created = true;
        cout << "Tao vi nguoi dung thanh cong.\n";
        return true;
    } else {
        cout << "Ma dinh danh khong dung. Huy tao vi.\n";
        return false;
    }
}

// Menu tao vi
bool walletCreationMenu(Wallet &wallet, const string &loggedInUser) {
    int choice;
    do {
        cout << "\n====== MENU THAO TAC TAO VI TIEN ======\n";
        cout << "1. Tao vi nguoi dung\n";
        cout << "2. Quay ve menu truoc\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            return createWallet(wallet, loggedInUser);
        } else if (choice == 2) {
            return false;
        } else {
            cout << "Lua chon khong hop le. Vui long nhap lai.\n";
        }
    } while (true);
}

// Ham yeu cau nhap va xac thuc ma dinh danh
bool verifyWalletID(const Wallet &wallet) {
    string inputID;
    int attempts = 3;
    while (attempts--) {
        cout << "Nhap ma dinh danh cua ban: ";
        getline(cin, inputID);
        if (inputID == wallet.id) return true;
        cout << "Ma dinh danh sai. Con " << attempts << " lan thu lai.\n";
    }
    return false;
}

// Menu thao tac su dung vi tien
void walletMainMenu(Wallet &wallet, const string &loggedInUser) {
    int choice;
    while (true) {
        cout << "\n====== MENU THAO TAC SU DUNG VI TIEN ======\n";
        cout << "1. Nap\n";
        cout << "2. Rut\n";
        cout << "3. Chuyen khoan\n";
        cout << "4. Xem so du\n";
        cout << "5. Lich su giao dich\n";
        cout << "6. Quay ve menu truoc\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice >= 1 && choice <= 5) {
            if (!wallet.created) {
                cout << "Ban chua co vi. Vui long tao vi truoc khi su dung chuc nang nay.\n";
                bool created = walletCreationMenu(wallet, loggedInUser);
                if (!created) continue; // quay lai menu chinh neu khong tao
            }

            if (!verifyWalletID(wallet)) {
                cout << "Nhap sai qua 3 lan. Thoat chuong trinh.\n";
                exit(0);
            }
        }

        switch (choice) {
            case 1:
                cout << "Chuc nang nap tien dang duoc phat trien...\n";
                break;
            case 2:
                cout << "Chuc nang rut tien dang duoc phat trien...\n";
                break;
            case 3:
                cout << "Chuc nang chuyen khoan dang duoc phat trien...\n";
                break;
            case 4:
                cout << "So du hien tai: " << wallet.balance << " VND\n";
                break;
            case 5:
                cout << "Chuc nang xem lich su giao dich dang duoc phat trien...\n";
                break;
            case 6:
                cout << "Quay ve menu truoc.\n";
                return;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    }
}

// Chuong trinh chinh mo phong nguoi dung da dang nhap
int main() {
    srand(time(0));
    string loggedInUser = "nguyenvana";
    Wallet wallet;

    cout << "Dang nhap thanh cong voi tai khoan: " << loggedInUser << "\n";

    walletMainMenu(wallet, loggedInUser);

    cout << "Ket thuc chuong trinh.\n";
    return 0;
}

