#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>  // За форматиране на изхода

using namespace std;

// Функция за показване на текущото меню с формат за лева
void displayMenu() {
    ifstream file("data/menu.txt");

    if (!file) {
        cout << "Error: Menu file not found.\n";
        return;
    }

    string item;
    double price;

    cout << "\n--- Current Menu ---\n";
    cout << left << setw(20) << "Item" << right << setw(10) << "Price (лв.)" << endl;
    cout << "-------------------------------\n";

    while (file >> item >> price) {
        cout << left << setw(20) << item
            << right << setw(8) << fixed << setprecision(2) << price << " лв." << endl;
    }

    file.close();
}

void addItemToMenu() {
    ofstream menuFile("data/menu.txt", ios::app);  // Добавяне към края на файла

    if (!menuFile) {
        cout << "Error: Unable to open menu file.\n";
        return;
    }

    string itemName;
    double itemPrice;

    cout << "Enter item name: ";
    cin >> itemName;
    cout << "Enter item price: ";
    cin >> itemPrice;

    // Записване в менюто
    menuFile << itemName << " " << itemPrice << endl;
    cout << itemName << " added to the menu for " << itemPrice << " лв.\n";

    menuFile.close();
}

void removeItemFromMenu() {
    ifstream menuFile("data/menu.txt");
    ofstream tempFile("data/temp.txt");

    if (!menuFile || !tempFile) {
        cout << "Error: Unable to open menu file.\n";
        return;
    }

    string itemName, currentItem;
    double price;
    bool itemFound = false;

    cout << "Enter item name to remove: ";
    cin >> itemName;

    // Прехвърляне на артикулите без този, който трябва да се премахне
    while (menuFile >> currentItem >> price) {
        if (currentItem == itemName) {
            itemFound = true;
            cout << currentItem << " removed from the menu.\n";
        }
        else {
            tempFile << currentItem << " " << price << endl;
        }
    }

    menuFile.close();
    tempFile.close();

    // Заместване на стария файл с новия
    remove("data/menu.txt");
    rename("data/temp.txt", "data/menu.txt");

    if (!itemFound) {
        cout << "Error: Item " << itemName << " not found in the menu.\n";
    }
}
