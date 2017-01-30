#include <iostream>
#include <vector>
#include <string>

#include "Northwind_database_abstraction.h"

using namespace std;

Northwind_database_abstraction::Northwind_database_abstraction(string path)
	: Database_abstraction(path) {	//call the base class constructor
}


//----------------------------------------------query_1()
void Northwind_database_abstraction::query_1() {
	//query
	string sql = "SELECT COUNT(*) AS Num_of_country FROM Customers WHERE Customers.Country = 'USA' OR Customers.Country = 'UK' OR Customers.Country = 'Spain';";

	//statement pointer
	sqlite3_stmt* my_statement;

	//iterate through
	if (execute_query_results(sql, my_statement)) {
		//grab a row from the table
		int statusOfStep = sqlite3_step(my_statement);

		//go through all the other rows
		while (statusOfStep == SQLITE_ROW) {
			//grab the count from the row
			int count = sqlite3_column_int(my_statement, 0);

			//print out
			cout << count << endl;

			//get next row
			statusOfStep = sqlite3_step(my_statement);
		}

		//clean and destroy
		sqlite3_finalize(my_statement);
		my_statement = NULL;
	}
}


//----------------------------------------------query_2()
void Northwind_database_abstraction::query_2() {
	//query
	string sql = "SELECT Suppliers.CompanyName, Suppliers.Phone FROM Suppliers WHERE Suppliers.Phone LIKE '%(514)%';";

	//statement pointer
	sqlite3_stmt* my_statement;

	//execute querey
	if (execute_query_results(sql, my_statement)) {
		//get the 1st row
		int statusOfStep = sqlite3_step(my_statement);

		//grab the rest of the rows
		while (statusOfStep = sqlite3_step(my_statement)) {
			//get the company name
			string company_name((char*)sqlite3_column_text(my_statement, 0));
			//get the phone number
			string phone((char*)sqlite3_column_text(my_statement, 1));

			//print out info
			cout << company_name << "......" << phone << endl;
			
			//grab the next row
			int statusOfStep = sqlite3_step(my_statement);
		}

		//clean up & destroy
		sqlite3_finalize(my_statement);
		my_statement = NULL;
	}
}
//----------------------------------------------query_3()
void Northwind_database_abstraction::query_3() {
	//query
	string sql = "SELECT COUNT (*) as NumUnitsInGreaterThanUnitsOn FROM Products WHERE Products.UnitsInStock > Products.UnitsOnOrder;";

	//create statement pointer
	sqlite3_stmt* my_statement;

	//execute qeuery
	if (execute_query_results(sql, my_statement)) {
		//get the 1st row
		int statusOfStep = sqlite3_step(my_statement);

		//go through all rows
		while (statusOfStep == SQLITE_ROW) {
			//grab the number of units
			int num_of_units = sqlite3_column_int(my_statement, 0);

			//print out
			cout << num_of_units << endl;

			//grab next row
			statusOfStep = sqlite3_step(my_statement);
		}

		//clean up & destroy
		sqlite3_finalize(my_statement);
		my_statement = NULL;
	}
}

//----------------------------------------------query_4()
void Northwind_database_abstraction::query_4() {
	//query
	string sql = "SELECT Products.ProductName, Orders.OrderID FROM Products, Orders, [Order Details] WHERE Products.ProductID = [Order Details].ProductID AND [Order Details].OrderID = Orders.OrderID AND Orders.OrderID = 10275;";

	//create statement pointer
	sqlite3_stmt* my_statement;

	//execute
	if (execute_query_results(sql, my_statement)) {
		//grab the 1st row
		int statusOfStep = sqlite3_step(my_statement);

		//loop through the rows
		while (statusOfStep == SQLITE_ROW) {
			//get the product name
			string product_name((char*)sqlite3_column_text(my_statement, 0));

			//print out
			cout << product_name << endl;

			//grab next row
			statusOfStep = sqlite3_step(my_statement);
		}

		//clean & destroy
		sqlite3_finalize(my_statement);
		my_statement = NULL;
	}
}


//----------------------------------------------query_5()
void Northwind_database_abstraction::query_5() {
	//query
	string sql = "SELECT Employees.FirstName, Employees.LastName, ReportsTo, COUNT (*) FROM Employees GROUP BY ReportsTo;";


	//create statement pointer
	sqlite3_stmt* my_statement;

	//execute
	if (execute_query_results(sql, my_statement)) {
		//grab the 1st row
		int statusOfStep = sqlite3_step(my_statement);

		//loop through the other rows
		while (statusOfStep == SQLITE_ROW) {
			//get the first name and last name
			string first((char*)sqlite3_column_text(my_statement, 0));
			string last((char*)sqlite3_column_text(my_statement, 1));

			//grab how many people report to them
			int incharge = sqlite3_column_int(my_statement, 3);

			//print
			cout << first << "  " << last << "    " << incharge << endl;

			//grab next row
			statusOfStep = sqlite3_step(my_statement);
		}
		//clean & destroy
		statusOfStep = sqlite3_finalize(my_statement);
		my_statement = NULL;
	}
}

//----------------------------------------------query_6()
void Northwind_database_abstraction::query_6() {
	//query
	string sql = "SELECT DISTINCT Products.ProductName FROM Orders, [Order Details], Products, Customers WHERE Orders.CustomerID = 'THEBI' AND Customers.CompanyName = 'The Big Cheese' AND Customers.CustomerID = Orders.CustomerID AND Orders.OrderID = [Order Details].OrderID AND [Order Details].ProductID = Products.ProductID AND [Order Details].Quantity >= 10;";

	//create statment pointer
	sqlite3_stmt* my_statement;

	//execute
	if (execute_query_results(sql, my_statement)) {
		//grab 1st row
		int statusOfStep = sqlite3_step(my_statement);

		//loop through rows
		while (statusOfStep == SQLITE_ROW) {
			//get product name
			string product_name((char*)sqlite3_column_text(my_statement, 0));

			//print
			cout << product_name << endl;


			//get next row
			statusOfStep = sqlite3_step(my_statement);
		}
		//clean & destroy
		sqlite3_finalize(my_statement);
		my_statement = NULL;
	}
}

//----------------------------------------------query_7()
void Northwind_database_abstraction::query_7() {
	//query
	string sql = "SELECT SUM([Order Details].UnitPrice  * [Order Details].Quantity * (1.0 - [Order Details].Discount)) AS FinalUnitPrice FROM Customers, [Order Details], Orders WHERE Customers.CustomerID = 'SIMOB' AND Customers.CustomerID = Orders.CustomerID AND Orders.OrderID = [Order Details].OrderID AND Orders.OrderDate = '1/16/1997 12:00:00 AM';";
	
	//create statment pointer
	sqlite3_stmt* my_statement;

	//execute
	if (execute_query_results(sql, my_statement)) {
		//grab 1st row
		int statusOfStep = sqlite3_step(my_statement);

		//loop through rows
		while (statusOfStep == SQLITE_ROW) {
			//grap unit price
			double unit_price = sqlite3_column_double(my_statement, 0);

			//print 
			cout << "$ " << unit_price << endl;

			//get next row
			statusOfStep = sqlite3_step(my_statement);
		}
		//clean & destroy
		sqlite3_finalize(my_statement);
		my_statement = NULL;
	}
}

//----------------------------------------------query_8()
void Northwind_database_abstraction::query_8() {
	//query
	string sql = "SELECT Products.ProductName, MAX(Products.UnitsInStock) AS UnitsInStock FROM Products, [Order Details] WHERE [Order Details].Discount >= '0.25';";


	//create statment pointer
	sqlite3_stmt* my_statement;

	//execute
	if (execute_query_results(sql, my_statement)) {
		//grab 1st row
		int statusOfStep = sqlite3_step(my_statement);

		//loop through rows
		while (statusOfStep == SQLITE_ROW) {
			//get product name
			string product_name((char*)sqlite3_column_text(my_statement, 0));
			//get num of unit in stock
			int unit_in_stock = sqlite3_column_int(my_statement, 1);

			//print
			cout << product_name << "     " << unit_in_stock << endl;

			//get next row
			statusOfStep = sqlite3_step(my_statement);
		}
		//clean & destroy
		sqlite3_finalize(my_statement);
		my_statement = NULL;
	}
}

//----------------------------------------------query_9()
void Northwind_database_abstraction::query_9() {
	//query
	string sql = "SELECT Company, OrderTotal, MAX(DiscountedPrice) AS Discount, Paid FROM Customers, Orders, [Order Details], ( SELECT Customers. CompanyName AS Company, SUM([Order Details].UnitPrice * [Order Details].Quantity * [Order Details].Discount) AS DiscountedPrice, SUM([Order Details].UnitPrice * [Order Details].Quantity) AS OrderTotal, SUM([Order Details].UnitPrice * [Order Details].Quantity * (1 - [Order Details].Discount)) AS Paid, [Order Details].OrderID AS ID FROM Customers, Orders, [Order Details] WHERE Customers.CustomerID = Orders.CustomerID AND Orders.OrderID = [Order Details].OrderID GROUP BY Orders.OrderID ) WHERE Customers.CustomerID = Orders.CustomerID AND Orders.OrderID = [Order Details].OrderID;";


	//create statment pointer
	sqlite3_stmt* my_statement;

	//execute
	if (execute_query_results(sql, my_statement)) {
		//grab 1st row
		int statusOfStep = sqlite3_step(my_statement);

		//loop through rows
		while (statusOfStep == SQLITE_ROW) {
			//grab company name
			string company((char*)sqlite3_column_text(my_statement, 0));
			//grab order total
			double order_total = sqlite3_column_double(my_statement, 1);
			//grab the discount
			double discount = sqlite3_column_double(my_statement, 2);
			//grab amount paid
			double paid = sqlite3_column_double(my_statement, 3);

			//print
			cout << company << "   " << order_total << "   " << discount << "   " << paid << endl;


			//get next row
			statusOfStep = sqlite3_step(my_statement);
		}
		//clean & destroy
		sqlite3_finalize(my_statement);
		my_statement = NULL;
	}
}

//----------------------------------------------query_10()
void Northwind_database_abstraction::query_10() {
	//query
	string sql = "SELECT CompanyName FROM Products, Suppliers WHERE Suppliers.SupplierID = Products.SupplierID GROUP BY Suppliers.CompanyName HAVING SUM(Products.UnitsOnOrder) > 100;";


	//create statment pointer
	sqlite3_stmt* my_statement;

	//execute
	if (execute_query_results(sql, my_statement)) {
		//grab 1st row
		int statusOfStep = sqlite3_step(my_statement);

		//loop through rows
		while (statusOfStep == SQLITE_ROW) {
			//grab company name
			string company((char*)sqlite3_column_text(my_statement, 0));

			cout << company << endl;


			//get next row
			statusOfStep = sqlite3_step(my_statement);
		}
		//clean & destroy
		sqlite3_finalize(my_statement);
		my_statement = NULL;
	}
}

//----------------------------------------------~Northwind_database_abstraction()
Northwind_database_abstraction::~Northwind_database_abstraction() {
}


