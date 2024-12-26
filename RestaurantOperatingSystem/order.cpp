#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Функция за добавяне на поръчка
void addOrder() {
    ifstream menuFile("data/menu.txt");  // Отваряне на менюто
    ofstream orderFile("data/orders.txt", ios::app);  // Запис на поръчка в края на файла

    if (!menuFile) {
        cout << "Error: Menu file not found.\n";
        return;
    }

    string itemName;
    cout << "Enter item name to order: ";
    cin >> itemName;

    string menuItem;
    double price;
    bool itemFound = false;

    // Търсене на артикул в менюто
    while (menuFile >> menuItem >> price) {
        if (menuItem == itemName) {
            itemFound = true;
            orderFile << itemName << " " << price << " лв." << endl;
            cout << itemName << " added to orders for " << price << " лв.\n";
            break;
        }
    }

    if (!itemFound) {
        cout << "Error: " << itemName << " is not available in the menu. Order canceled.\n";
    }

    menuFile.close();
    orderFile.close();
}
