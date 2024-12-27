﻿#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>  // For output formatting

using namespace std;

// Function to display the current menu with price formatting
void displayMenu() {
    ifstream file("data/menu.txt");

    if (!file) {
        cout << "Error: Menu file not found.\n";
        return;
    }

    string item;
    double price;

    cout << "\n--- Current Menu ---\n";
    cout << left << setw(20) << "Item" << right << setw(10) << "Price (lv.)" << endl;
    cout << "-------------------------------\n";

    while (file >> item >> price) {
        cout << left << setw(20) << item
            << right << setw(8) << fixed << setprecision(2) << price << " lv." << endl;
    }

    file.close();
}

// Function to add a new item to the menu
void addItemToMenu() {
    ofstream menuFile("data/menu.txt", ios::app);  // Append to the end of the file

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

    // Write to the menu
    menuFile << itemName << " " << itemPrice << endl;
    cout << itemName << " added to the menu for " << itemPrice << " lv.\n";

    menuFile.close();
}

// Function to remove an item from the menu
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

    // Transfer items except the one to be removed
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

    // Replace the old file with the new one
    if (rename("data/temp.txt", "data/menu.txt") != 0) {
        cout << "Error: Failed to rename menu file.\n";
    }

    if (!itemFound) {
        cout << "Error: Item " << itemName << " not found in the menu.\n";
    }
}
