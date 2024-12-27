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
}
void viewOrders() {
	ifstream orderFile("data/orders.txt");

	if (!orderFile) {
		cout << "Error: Orders file not found.\n";
		return;
	}

	string item;
	double price;
	bool hasOrders = false;

	cout << "\n--- Past Orders ---\n";
	while (orderFile >> item >> price) {
		cout << item << " - " << price << " лв." << endl;
		hasOrders = true;
	}

	if (!hasOrders) {
		cout << "No orders found.\n";
	}

	orderFile.close();
}

struct OrderItem {
	string name;
	int count;
};

// Функция за сортиране на поръчките
void sortOrders(OrderItem orders[], int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (orders[i].name > orders[j].name) {
				OrderItem temp = orders[i];
				orders[i] = orders[j];
				orders[j] = temp;
			}
		}
	}
}

void viewSortedOrders() {
	ifstream orderFile("data/orders.txt");

	if (!orderFile) {
		cout << "Error: Orders file not found.\n";
		return;
	}

	OrderItem orders[100]; // Масив за поръчките
	int orderCount = 0;

	string item;
	double price;

	// Четене на поръчките и добавяне към масива
	while (orderFile >> item >> price) {
		bool found = false;

		// Проверка дали артикулът вече е добавен
		for (int i = 0; i < orderCount; i++) {
			if (orders[i].name == item) {
				orders[i].count++;
				found = true;
				break;
			}
		}

		// Добавяне на нов артикул, ако не е намерен
		if (!found) {
			orders[orderCount].name = item;
			orders[orderCount].count = 1;
			orderCount++;
		}
	}

	orderFile.close();

	if (orderCount == 0) {
		cout << "No orders found.\n";
		return;
	}

	// Сортиране на артикулите по азбучен ред
	sortOrders(orders, orderCount);

	// Извеждане на резултата
	cout << "\n--- Sorted Orders ---\n";
	for (int i = 0; i < orderCount; i++) {
		cout << orders[i].name << " - " << orders[i].count << " orders\n";
	}
}


