#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

struct Account {
    string pin;
    double balance;
};

unordered_map<string, Account> accounts = {
    {"1001", {"1234", 500.00}},
    {"1002", {"2345", 1500.50}},
    {"1003", {"3456", 230.75}},
    {"1004", {"4567", 1200.00}},
    {"1005", {"5678", 3000.25}},
    {"1006", {"6789", 50.00}}
};

void saveAccounts() {
    ofstream file("accounts.txt");
    for (auto &entry : accounts) {
        file << entry.first << " " << entry.second.pin << " " << entry.second.balance << endl;
    }
    file.close();
}

void atmMenu(string accountNumber) {
    int choice;
    do {
        cout << "\n1. Проверить баланс\n2. Внести деньги\n3. Снять деньги\n4. Выйти\nВыберите опцию: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Ваш баланс: " << accounts[accountNumber].balance << " USD\n";
                break;
            case 2: {
                double amount;
                cout << "Введите сумму для внесения: ";
                cin >> amount;
                accounts[accountNumber].balance += amount;
                cout << "Деньги успешно внесены!\n";
                saveAccounts();
                break;
            }
            case 3: {
                double amount;
                cout << "Введите сумму для снятия: ";
                cin >> amount;
                if (amount > accounts[accountNumber].balance) {
                    cout << "Недостаточно средств!\n";
                } else {
                    accounts[accountNumber].balance -= amount;
                    cout << "Деньги успешно сняты!\n";
                    saveAccounts();
                }
                break;
            }
            case 4:
                cout << "Выход из системы...\n";
                break;
            default:
                cout << "Неверный выбор, попробуйте снова!\n";
        }
    } while (choice != 4);
}

int main() {
    saveAccounts();
    string accountNumber, pin;
    cout << "Введите номер счета: ";
    cin >> accountNumber;
    
    if (accounts.find(accountNumber) == accounts.end()) {
        cout << "Аккаунт не найден!\n";
        return 0;
    }
    
    cout << "Введите PIN-код: ";
    cin >> pin;
    
    if (accounts[accountNumber].pin != pin) {
        cout << "Неверный PIN-код!\n";
        return 0;
    }
    
    cout << "Вход выполнен успешно!\n";
    atmMenu(accountNumber);
    return 0;
}
