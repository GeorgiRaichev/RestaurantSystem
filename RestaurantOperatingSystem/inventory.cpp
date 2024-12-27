#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Функция за проверка на складовите наличности
void checkInventory() {
    ifstream inventoryFile("data/inventory.txt");

    if (!inventoryFile) {
        cout << "Error: Inventory file not found.\n";
        return;
    }

    string item;
    int quantity;

    cout << "\n--- Current Inventory ---\n";
    while (inventoryFile >> item >> quantity) {
        cout << item << " - " << quantity << " available\n";
    }

    inventoryFile.close();
}

// Функция за изписване на продукт от склада
void issueProduct() {
    ifstream inventoryFile("data/inventory.txt");
    ofstream tempFile("data/temp.txt");

    if (!inventoryFile || !tempFile) {
        cout << "Error: Unable to open inventory file.\n";
        return;
    }

    string itemName, currentItem;
    int quantity, amountToIssue;
    bool itemFound = false;

    cout << "Enter item name to issue: ";
    cin >> itemName;
    cout << "Enter quantity to issue: ";
    cin >> amountToIssue;

    while (inventoryFile >> currentItem >> quantity) {
        if (currentItem == itemName) {
            itemFound = true;
            if (quantity >= amountToIssue) {
                quantity -= amountToIssue;
                cout << amountToIssue << " " << itemName << " issued. Remaining: " << quantity << endl;
            }
            else {
                cout << "Error: Not enough " << itemName << " in stock.\n";
            }
        }
        tempFile << currentItem << " " << quantity << endl;
    }

    if (!itemFound) {
        cout << "Error: Item " << itemName << " not found in inventory.\n";
    }

    inventoryFile.close();
    tempFile.close();

    // Заместване на стария файл с новия
    remove("data/inventory.txt");
    rename("data/temp.txt", "data/inventory.txt");
}

// Функция за добавяне на продукт в склада
void addInventory() {
    ifstream inventoryFile("data/inventory.txt");
    ofstream tempFile("data/temp.txt");

    if (!inventoryFile || !tempFile) {
        cout << "Error: Unable to open inventory file.\n";
        return;
    }

    string itemName, currentItem;
    int quantity, existingQuantity;
    bool itemFound = false;

    cout << "Enter item name to add: ";
    cin >> itemName;
    cout << "Enter quantity to add: ";
    cin >> quantity;

    while (inventoryFile >> currentItem >> existingQuantity) {
        if (currentItem == itemName) {
            existingQuantity += quantity;
            itemFound = true;
        }
        tempFile << currentItem << " " << existingQuantity << endl;
    }

    // Ако продуктът не е намерен, добавяме нов ред
    if (!itemFound) {
        tempFile << itemName << " " << quantity << endl;
        cout << itemName << " added to inventory with quantity " << quantity << endl;
    }
    else {
        cout << quantity << " units of " << itemName << " added to existing stock.\n";
    }

    inventoryFile.close();
    tempFile.close();

    // Заместване на стария файл с новия
    remove("data/inventory.txt");
    rename("data/temp.txt", "data/inventory.txt");
}
