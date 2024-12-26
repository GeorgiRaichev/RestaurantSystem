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
