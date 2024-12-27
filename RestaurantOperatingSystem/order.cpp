#include <iostream>
#include <fstream>
#include <string>
#include <ctime> 

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

void viewDailyRevenue() {
	ifstream orderFile("data/orders.txt");

	if (!orderFile) {
		cout << "Error: Orders file not found.\n";
		return;
	}

	string item;
	double price;
	double totalRevenue = 0;

	// Сумиране на цените от всички поръчки
	while (orderFile >> item >> price) {
		totalRevenue += price;
	}

	orderFile.close();

	// Показване на резултата
	cout << "\n--- Daily Revenue ---\n";
	cout << "Total Revenue: " << totalRevenue << " лв.\n";
}

void generateReport() {
	ifstream orderFile("data/orders.txt");

	if (!orderFile) {
		cout << "Error: Orders file not found.\n";
		return;
	}

	double totalRevenue = 0;
	string item;
	double price;

	// Изчисляване на общия оборот
	while (orderFile >> item >> price) {
		totalRevenue += price;
	}
	orderFile.close();

	// Получаване на текущата дата
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int day = ltm->tm_mday;
	int month = 1 + ltm->tm_mon;
	int year = 1900 + ltm->tm_year;

	// Записване на отчета във файл
	ofstream reportFile("data/report.txt", ios::app);
	reportFile << "Date: " << day << "/" << month << "/" << year
		<< " - Total Revenue: " << totalRevenue << " лв.\n";
	reportFile.close();

	// Изчистване на orders.txt (зануляване на оборота)
	ofstream clearOrders("data/orders.txt", ofstream::trunc);
	clearOrders.close();

	cout << "\n--- Report Generated ---\n";
	cout << "Total Revenue for " << day << "/" << month << "/" << year
		<< ": " << totalRevenue << " лв.\n";
	cout << "Orders have been cleared.\n";
}

void viewTotalRevenueByDate() {
	ifstream reportFile("data/report.txt");

	if (!reportFile) {
		cout << "Error: Report file not found.\n";
		return;
	}

	int startDay, startMonth, startYear;
	char slash;

	cout << "Enter start date (dd/mm/yyyy): ";
	cin >> startDay >> slash >> startMonth >> slash >> startYear;

	string line;
	bool found = false;

	cout << "\n--- Reports from " << startDay << "/" << startMonth << "/" << startYear << " to now ---\n";

	while (getline(reportFile, line)) {
		int reportDay, reportMonth, reportYear;
		double revenue;

		// Извличане на датата и оборота от реда
		sscanf(line.c_str(), "Date: %d/%d/%d - Total Revenue: %lf лв.",
			&reportDay, &reportMonth, &reportYear, &revenue);

		// Проверка дали датата е след или равна на началната дата
		if (reportYear > startYear ||
			(reportYear == startYear && reportMonth > startMonth) ||
			(reportYear == startYear && reportMonth == startMonth && reportDay >= startDay)) {
			cout << line << endl;
			found = true;
		}
	}

	if (!found) {
		cout << "No reports found from this date.\n";
	}

	reportFile.close();
}


