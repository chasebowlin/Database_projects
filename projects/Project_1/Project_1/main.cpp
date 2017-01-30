#include <iostream>
#include <string>
#include <cstdlib>

#include "sqlite3.h"
#include "Northwind_database_abstraction.h"

using namespace std;

int main() {
	//grab the path to the database and create the abstraction object
	Northwind_database_abstraction database("C:/Users/FGSPB/Desktop/DataBase/projects/Project_1/Northwind.db");

	//holds the users answer
	int answer = 0;

	while (answer != -1) {
		cout << "  Select a Query\n" << endl;
		cout << "1.......Query #1" << endl;
		cout << "2.......Query #2" << endl;
		cout << "3.......Query #3" << endl;
		cout << "4.......Query #4" << endl;
		cout << "5.......Query #5" << endl;
		cout << "6.......Query #6" << endl;
		cout << "7.......Query #7" << endl;
		cout << "8.......Query #8" << endl;
		cout << "9.......Query #9" << endl;
		cout << "10......Query #10\n" << endl;
		cout << endl;

		cout << "Enter which query you would like to run (-1 to exit):  ";
		cin >> answer;

		if (answer == 1) {
			cout << "1. How many companies are in the UK, USA, and Spain?\n" << endl;
			database.query_1();
			cout << endl;
			system("PAUSE");
			system("CLS");
		}
		else if (answer == 2) {
			cout << "2. What are the names and phone numbers of suppliers who are in the 514 area code?\n" << endl;
			database.query_2();
			cout << endl;
			system("PAUSE");
			system("CLS");
		}
		else if (answer == 3) {
			cout << "3. How many products have a greater value of in-stock items compared to the value of items on order?\n" << endl;
			database.query_3();
			cout << endl;
			system("PAUSE");
			system("CLS");
		}
		else if (answer == 4) {
			cout << "4. What are the names of the products in order #10275?\n" << endl;
			database.query_4();
			cout << endl;
			system("PAUSE");
			system("CLS");
		}
		else if (answer == 5) {
			cout << "5. Who are all the employees who manage others and how many people do they manage?\n" << endl;
			database.query_5();
			cout << endl;
			system("PAUSE");
			system("CLS");
		}
		else if (answer == 6) {
			cout << "6. What are the names of the products that were ever ordered by the customer 'The Big Cheese' in quantities of 10 or more?\n" << endl;
			database.query_6();
			cout << endl;
			system("PAUSE");
			system("CLS");
		}
		else if (answer == 7) {
			cout << "7. What was the final order price for all items ordered by the customer 'Simons bistro' on January 16th 1997?\n" << endl;
			database.query_7();
			system("PAUSE");
			system("CLS");
		}
		else if (answer == 8) {
			cout << "8. Which product that was ever sold at a discount of 25% or more has the most units in stock (and how many units are in stock)?\n" << endl;
			database.query_8();
			cout << endl;
			system("PAUSE");
			system("CLS");
		}
		else if (answer == 9) {
			cout << "9. What is the name of the company that had the largest discount on any order, how much was that discount, how much did the company pay minus the discount, and how much would they have paid without the discount?\n" << endl;
			database.query_9();
			cout << endl;
			system("PAUSE");
			system("CLS");
		}
		else if (answer == 10) {
			cout << "10. Who are the suppliers whose products have more than 100 units on order?\n" << endl;
			database.query_10();
			cout << endl;
			system("PAUSE");
			system("CLS");
		}
		else if (answer == -1) {
			//database.~Database_abstraction();
		}
	}
	return 0;
}