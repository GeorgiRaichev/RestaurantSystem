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
void cancelOrder() {
	ifstream orderFile("data/orders.txt");
	ofstream tempFile("data/temp.txt");

	if (!orderFile) {
		cout << "Error: Orders file not found.\n";
		return;
	}

	string itemName;
	cout << "Enter item name to cancel: ";
	cin >> itemName;

	string orderItem;
	double price;
	bool orderFound = false;

	// Прехвърляне на поръчките, без тази за изтриване
	while (orderFile >> orderItem >> price) {
		if (orderItem == itemName) {
			cout << itemName << " order canceled successfully.\n";
			orderFound = true;
		}
		else {
			tempFile << orderItem << " " << price << " лв." << endl;
		}
	}

	if (!orderFound) {
		cout << "Error: Order for " << itemName << " not found.\n";
	}

	orderFile.close();
	tempFile.close();

	// Заместване на стария файл с новия
	remove("data/orders.txt");
	rename("data/temp.txt", "data/orders.txt");
