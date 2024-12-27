#include <iostream>
#include <fstream>
#include <string>
#include <ctime> 

using namespace std;

// Function to add an order
void addOrder() {
	ifstream menuFile("menu.txt");  // Open the menu file
	ofstream orderFile("orders.txt", ios::app);  // Append the order to the file

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

	// Search for the item in the menu
	while (menuFile >> menuItem >> price) {
		if (menuItem == itemName) {
			itemFound = true;
			orderFile << itemName << " " << price << " lv." << endl;
			cout << itemName << " added to orders for " << price << " lv.\n";
			break;
		}
	}

	if (!itemFound) {
		cout << "Error: " << itemName << " is not available in the menu. Order canceled.\n";
	}

	menuFile.close();
	orderFile.close();
}

// Function to cancel an order
void cancelOrder() {
	ifstream orderFile("orders.txt");
	ofstream tempFile("temp.txt");

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

	// Transfer orders except the one to be deleted
	while (orderFile >> orderItem >> price) {
		if (orderItem == itemName) {
			cout << itemName << " order canceled successfully.\n";
			orderFound = true;
		}
		else {
			tempFile << orderItem << " " << price << " lv." << endl;
		}
	}

	if (!orderFound) {
		cout << "Error: Order for " << itemName << " not found.\n";
	}

	orderFile.close();
	tempFile.close();

	// Replace the old file with the new one
	if (rename("temp.txt", "orders.txt") != 0) {
		cout << "Error: Failed to rename orders file.\n";
	}
}

// Function to view all past orders
void viewOrders() {
	ifstream orderFile("orders.txt");

	if (!orderFile) {
		cout << "Error: Orders file not found.\n";
		return;
	}

	string item;
	double price;
	bool hasOrders = false;

	cout << "\n--- Past Orders ---\n";
	while (orderFile >> item >> price) {
		cout << item << " - " << price << " lv." << endl;
		hasOrders = true;
	}

	if (!hasOrders) {
		cout << "No orders found.\n";
	}

	orderFile.close();
}

struct OrderItem {
	string name;
	int count = 0;
};

// Function to sort orders alphabetically
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

// Function to view sorted orders by item name and count
void viewSortedOrders() {
	ifstream orderFile("orders.txt");

	if (!orderFile) {
		cout << "Error: Orders file not found.\n";
		return;
	}

	OrderItem orders[100];  // Array to store orders
	int orderCount = 0;

	string item;
	double price;

	// Read orders and add to the array
	while (orderFile >> item >> price) {
		bool found = false;

		// Check if the item is already added
		for (int i = 0; i < orderCount; i++) {
			if (orders[i].name == item) {
				orders[i].count++;
				found = true;
				break;
			}
		}

		// Add new item if not found
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

	// Sort items alphabetically
	sortOrders(orders, orderCount);

	// Display the result
	cout << "\n--- Sorted Orders ---\n";
	for (int i = 0; i < orderCount; i++) {
		cout << orders[i].name << " - " << orders[i].count << " orders\n";
	}
}

// Function to view daily revenue
void viewDailyRevenue() {
	ifstream orderFile("orders.txt");

	if (!orderFile) {
		cout << "Error: Orders file not found.\n";
		return;
	}

	string item;
	double price;
	double totalRevenue = 0;

	// Sum prices from all orders
	while (orderFile >> item >> price) {
		totalRevenue += price;
	}

	orderFile.close();

	// Display the result
	cout << "\n--- Daily Revenue ---\n";
	cout << "Total Revenue: " << totalRevenue << " lv.\n";
}

// Function to generate a daily report
void generateReport() {
	ifstream orderFile("orders.txt");

	if (!orderFile) {
		cout << "Error: Orders file not found.\n";
		return;
	}

	double totalRevenue = 0;
	string item;
	double price;

	// Calculate total revenue
	while (orderFile >> item >> price) {
		totalRevenue += price;
	}
	orderFile.close();

	// Get current date using localtime_s
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);

	int day = ltm.tm_mday;
	int month = 1 + ltm.tm_mon;
	int year = 1900 + ltm.tm_year;

	// Write the report to file
	ofstream reportFile("report.txt", ios::app);
	reportFile << "Date: " << day << "/" << month << "/" << year
		<< " - Total Revenue: " << totalRevenue << " lv.\n";
	reportFile.close();

	// Clear orders.txt (reset daily revenue)
	ofstream clearOrders("orders.txt", ofstream::trunc);
	clearOrders.close();

	cout << "\n--- Report Generated ---\n";
	cout << "Total Revenue for " << day << "/" << month << "/" << year
		<< ": " << totalRevenue << " lv.\n";
	cout << "Orders have been cleared.\n";
}

void viewTotalRevenueByDate() {
	ifstream reportFile("report.txt");

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

		sscanf_s(line.c_str(), "Date: %d/%d/%d - Total Revenue: %lf lv.",
			&reportDay, &reportMonth, &reportYear, &revenue);

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
