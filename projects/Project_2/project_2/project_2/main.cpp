#include <iostream>
#include <iomanip>
#include <string>

#include "Calorie_counter_abstraction.h"

using namespace std;

int main() {
	//create the calorie abstraction
	Calorie_counter_abstraction database("C:/Users/FGSPB/Desktop/DataBase/projects/Project_2/Counter.sqlite");

	string answer;
	string first;
	string last;
	int choice = -1;
	int user_id = -1;

	//FIRST SCREEN WELCOME=============================================================
	//ask if they would like to add in a new user
	//or log in as an existing one

	while (choice == -1) {
		cout << "WELCOME TO CALORIE COUNTER\n\n" << endl;
		cout << "Would you like to\n";
		cout << "add in a new user(add) or log in(login):  ";
		cin >> answer;
		system("CLS");

		//THIRD SCREEN NEW USER=============================================================
		//if they choose to add in a new user
		if (answer == "add") {
			string first;
			string last;
			int calorie_limit;
			//add a user into the data base
			//take in the First name, last name,
			//and the user's calorie limit
			cout << "ADD NEW USER\n\n" << endl;
			cout << "Enter in your First name:  ";
			cin >> first;
			cout << endl;
			cout << "Enter in your Last name:  ";
			cin >> last;
			cout << endl;
			cout << "What is your daily calorie limit?:  ";
			cin >> calorie_limit;
			cout << endl;

			//go and add the user information to the table
			database.add_user(first, last, calorie_limit);
			cout << "your information has been added!" << endl;
			system("PAUSE");
			system("CLS");
		}


		//SECOND SCREEN LOGIN=============================================================
		//if they choose to login as an existing user
		else if (answer == "login") {
			cout << "LOGIN\n\n" << endl;
			cout << "Enter in your First name:  ";
			cin >> first;
			cout << endl;
			cout << "Enter in your Last name:  ";
			cin >> last;

			//go and check to see if the user info is in the database
			user_id = database.login(first, last);

			if (user_id == -1) {
				cout << "ERROR NOT A VALID USER" << endl;
				cout << "PLEASE ADD A NEW USER OR" << endl;
				cout << "TRY LOGGING IN AGAIN (Capital letters matter)" << endl;
				system("PAUSE");
			}
			else {
				choice = 1;
			}
			system("CLS");
		}
		else {
			cout << "\n ERROR INVALID INPUT" << endl;
			cout << "PLEASE ENTER A VALID OPTION" << endl;
		}
	}
	//reset choice to -1
	choice = -1;


//FOURTH SCREEN OPTIONS MENU=============================================================
	while (choice == -1) {
		cout << "Hello " << first << " " << last << ", what would you like to do?\n\n" << endl;
		cout << "Enter in a new food (1)" << endl;
		cout << "Enter in a new meal (2)" << endl;
		cout << "See the foods you at on a certain day (3)" << endl;
		cout << "See the total calories you at on a certain day (4)" << endl;
		cout << "See the foods you at on a certain day by category (5)" << endl;
		cout << "Find out how many calories you had between to days (6)" << endl;
		cout << "Find out how many calories you had between to days by category (7)" << endl;
		cout << "Change user (8)" << endl;
		cout << "Exit calorie counter (9)\n\n" << endl;

		cout << "enter in the number of the option you would like to preform:  ";
		cin >> choice;
		system("CLS");

		//FIFTH SCREEN ADD A FOOD=============================================================
		while (choice == 1) {
			string name, type;
			int calories;
			cout << "ADD A NEW FOOD\n\n" << endl;
			cout << "Enter in the name of the food:  ";
			cin >> name;
			cout << "\nWhat type of food is it:  ";
			cin >> type;
			cout << "\nHow many calories is it:  ";
			cin >> calories;

			database.add_food(name, type, calories);
			cout << "\n\nFood was added succefully!" << endl;
			cout << "would you like to enter another? (y or n):  ";
			char temp;
			cin >> temp;

			if (temp == 'n') {
				choice = -1;
			}
			else if (temp == 'y') {
				choice = 1;
			}
			system("CLS");
		}

		//FIFTH SCREEN ADD A MEAL=============================================================
		while (choice == 2) {
			string date, type, food;
			int food_id, meal_id;
			bool val = true;

			cout << "ADD A NEW MEAL\n\n" << endl;
			cout << "What is the date of the meal (YYYY/MM/DD):  ";
			cin >> date;
			cout << "\n\nWhat was the type of meal (lunch, dinner, snack):  ";
			cin >> type;
			

			//add the meal into the meal table
			database.add_meal(date, type, user_id);
			system("CLS");

			while (val == true) {
				cout << "Choose a food for the meal:\n" << endl;
				//print out all the foods to choose from
				database.print_all_foods();
				cout << "\n" << endl;
				cin >> food;

				//grab the food id, and meal id,
				//then add both ids into the linker table
				food_id = database.get_food_id(food);
				meal_id = database.get_meal_id(date, type, user_id);
				database.add_into_food_in_a_meal(food_id, meal_id);

				cout << "\n\nWould you like to add another" << endl;
				cout << "food for this meal? (y or n):  ";
				cin >> answer;

				if (answer == "n") {
					val = false;
				}
				else if (answer == "y") {
					val = true;
				}
				system("CLS");
			}
			cout << "\n\n\nWould you like to add another meal? (y or n):  ";
			cin >> answer;

			if (answer == "n") {
				choice = -1;
			}
			else if (answer == "y") {
				choice = 2;
			}
			system("CLS");
		}



		//SIXTH SCREEN FOODS ON CERTAIN DAY=============================================================
		while (choice == 3) {
			string date;

			cout << "Foods eaten on a certain day\n\n" << endl;
			cout << "Enter the day you would like to look atday(YYYY/MM/DD):  ";
			cin >> date;
			cout << "\n" << endl;

			database.get_all_food_on_date(date, user_id);

			cout << "\n\nWould you like to look at another day? (y or n):  ";
			cin >> answer;

			if (answer == "n") {
				choice = -1;
			}
			else if (answer == "y") {
				choice = 3;
			}

			system("CLS");
		}

		//SEVENTH SCREEN FOODS ON CERTAIN DAY BY CATEGORY=============================================================
		while (choice == 4) {
			string date;

			cout << "Total calories on a certain day\n\n" << endl;
			cout << "Enter the day you would like to look atday(YYYY/MM/DD):  ";
			cin >> date;
			cout << "\n" << endl;

			database.total_calories_on_date(date, user_id);

			cout << "\n\nWould you like to look at another day? (y or n):  ";
			cin >> answer;

			if (answer == "n") {
				choice = -1;
			}
			else if (answer == "y") {
				choice = 4;
			}
			system("CLS");
		}


		//EIGTH SCREEN FOODS ON CERTAIN DAY=============================================================
		while (choice == 5) {
			string date;

			cout << "Total calories on a certain day by category\n\n" << endl;
			cout << "Enter the day you would like to look atday(YYYY/MM/DD):  ";
			cin >> date;
			cout << "\n" << endl;

			database.total_calories_on_date_by_category(date, user_id);

			cout << "\n\nWould you like to look at another day? (y or n):  ";
			cin >> answer;

			if (answer == "n") {
				choice = -1;
			}
			else if (answer == "y") {
				choice = 5;
			}
			system("CLS");
		}

		//NINTH SCREEN CALORIES BETWEEN DATES=============================================================
		while (choice == 6) {
			string start_date, end_date;

			cout << "Total calories between two date\n\n" << endl;
			cout << "Enter the day you would like start(YYYY/MM/DD):  ";
			cin >> start_date;
			cout << "\n" << endl;
			cout << "\nEnter the day you would like to end(YYYY/MM/DD):  ";
			cin >> end_date;

			database.total_calories_between_dates(start_date, end_date, user_id);

			cout << "\n\nWould you like to look at another day? (y or n):  ";
			cin >> answer;

			if (answer == "n") {
				choice = -1;
			}
			else if (answer == "y") {
				choice = 6;
			}
			system("CLS");
		}
		
		//TENTH SCREEN CALORIES BETWEEN DATES BY CATEGORY=============================================================
		while (choice == 7) {
			string start_date, end_date;

			cout << "Total calories between two dates by category\n\n" << endl;
			cout << "Enter the day you would like start(YYYY/MM/DD):  ";
			cin >> start_date;
			cout << "\n" << endl;
			cout << "\nEnter the day you would like to end(YYYY/MM/DD):  ";
			cin >> end_date;

			database.total_calories_between_dates(start_date, end_date, user_id);

			cout << "\n\nWould you like to look at another day? (y or n):  ";
			cin >> answer;

			if (answer == "n") {
				choice = -1;
			}
			else if (answer == "y") {
				choice = 7;
			}
			system("CLS");
		}

		//ELEVENTH SCREEN CHANGE USER ==================
		if (choice == 8) {
			cout << "Change user\n\n  " << endl;
			cout << "Enter in your First name:  ";
			cin >> first;
			cout << endl;
			cout << "Enter in your Last name:  ";
			cin >> last;

			//go and check to see if the user info is in the database
			user_id = database.login(first, last);

			if (user_id == -1) {
				cout << "ERROR NOT A VALID USER" << endl;
				cout << "PLEASE ADD A NEW USER OR" << endl;
				cout << "TRY LOGGING IN AGAIN (Capital letters matter)" << endl;
				system("PAUSE");
			}
			else {
				choice = 1;
			}
			system("CLS");

			choice = -1;
		}

		//TWELVTH SCREEN EXIT ========================
		if (choice == 9) {
			exit;
		}

	}
	system("PAUSE");
	return 0;
}