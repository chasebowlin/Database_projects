#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "Calorie_counter_abstraction.h"

using namespace std;

Calorie_counter_abstraction::Calorie_counter_abstraction(string file_path)
	: Database_abstraction(file_path) { //call base class constructor
	//create all the tables
	create_food_table();
	create_meal_table();
	create_user_table();
	create_food_in_a_meal_table();
}

//------------------------------------------------create user table
void Calorie_counter_abstraction::create_user_table() {
	//add in the items of the user table (user_id, first, last, calorie_limit)
	string sql = "CREATE TABLE IF NOT EXISTS User (user_id INTEGER PRIMARY KEY NOT NULL, first TEXT, last TEXT, calorie_limit INTEGER);";

	//execute the query to create the table
	if (!execute_query_no_results(sql)) {
		cout << "Error creating the USERS table" << endl;
	}
}

//------------------------------------------------create meal table
void Calorie_counter_abstraction::create_meal_table() {
	//add in the items of the meal table (meal id, date, meal_type)
	string sql = "CREATE TABLE IF NOT EXISTS Meal (meal_id INTEGER PRIMARY KEY NOT NULL, date TEXT, meal_type TEXT, user_id INTEGER);"; 

	//execute the query to create the table
	if (!execute_query_no_results(sql)) {
		cout << "Error creating MEALS table" << endl;
	}
}

//------------------------------------------------create food table
void Calorie_counter_abstraction::create_food_table() {
	//add in the food table(food_id, type, food_name, calories)
	string sql = "CREATE TABLE IF NOT EXISTS Food (food_id INTEGER PRIMARY KEY NOT NULL, type TEXT, name TEXT, calories INTEGER);";

	//execute the query to create the table
	if (!execute_query_no_results(sql)) {
		cout << "Error creating FOOD table" << endl;
	}
}

//------------------------------------------------create food in a meal table
void Calorie_counter_abstraction::create_food_in_a_meal_table() {
	//add in the items of the food in a meal table (food_id, meal_id)
	string sql = "CREATE TABLE IF NOT EXISTS Food_in_a_meal (food_id INTEGER, meal_id INTEGER);";

	if (!execute_query_no_results(sql)) {
		cout << "Error creating FOOD IN A MEAL table" << endl;
	}
}




//------------------------------------------------add user
void Calorie_counter_abstraction::add_user(string first, string last, int calorie_limit) {
	//query to insert a user
	string sql = "INSERT INTO User (first, last, calorie_limit) VALUES (?, ?, ?);";

	//create a statement pointer
	sqlite3_stmt* my_statement;

	//create the statement object using the prepare()
	int status_of_prep = sqlite3_prepare_v2(dp_pointer, sql.c_str(), -1, &my_statement, NULL);

	//check to see if the prepared statement was created
	if (status_of_prep == SQLITE_OK) {
		//add the parameters
		sqlite3_bind_text(my_statement, 1, first.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(my_statement, 2, last.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(my_statement, 3, calorie_limit);
		
		//execute the query to insert a new user
		if (!execute_query_no_results(my_statement)) {
			cout << "Error inserting into Users" << endl;
		}
	}
}

//------------------------------------------------add food
void Calorie_counter_abstraction::add_food(string name, string type, int calories) {
	//query
	string sql = "INSERT INTO Food (name, type, calories) VALUES (?, ?, ?);";

	//statement pointer
	sqlite3_stmt* my_statement;

	//create the statement object using the prepare()
	int status_of_prep = sqlite3_prepare_v2(dp_pointer, sql.c_str(), -1, &my_statement, NULL);

	//check to see if the prepared statement was created
	if (status_of_prep == SQLITE_OK) {
		//add the parameters
		sqlite3_bind_text(my_statement, 1, name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(my_statement, 2, type.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(my_statement, 3, calories);

		//execute the query to insert a new user
		if (!execute_query_no_results(my_statement)) {
			cout << "Error inserting into Food" << endl;
		}
	}

}

//------------------------------------------------add meal
void Calorie_counter_abstraction::add_meal(string date, string meal_type, int user_id) {
	//query
	string sql = "INSERT INTO meal(date, meal_type, user_id) VALUES (?, ?, ?);";

	//statement pointer
	sqlite3_stmt* my_statement;

	//create the statement object using the prepare()
	int status_of_prep = sqlite3_prepare_v2(dp_pointer, sql.c_str(), -1, &my_statement, NULL);

	//check to see if the prepared statement was created
	if (status_of_prep == SQLITE_OK) {
		//add the parameters
		sqlite3_bind_text(my_statement, 1, date.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(my_statement, 2, meal_type.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(my_statement, 3, user_id);

		//execute the query to insert a new user
		if (!execute_query_no_results(my_statement)) {
			cout << "Error inserting into Meal" << endl;
		}
	}

}

//------------------------------------------------add into food in a meal table
void Calorie_counter_abstraction::add_into_food_in_a_meal(int food_id, int meal_id) {
	//query
	string sql = "INSERT INTO Food_in_a_meal (food_id, meal_id) VALUES (?, ?);";

	//statement pointer
	sqlite3_stmt* my_statement;

	//create the statement object using the prepare()
	int status_of_prep = sqlite3_prepare_v2(dp_pointer, sql.c_str(), -1, &my_statement, NULL);

	//check to see if the prepared statement was created
	if (status_of_prep == SQLITE_OK) {
		//add the parameters
		sqlite3_bind_int(my_statement, 1, food_id);
		sqlite3_bind_int(my_statement, 2, meal_id);
	}

	//execute the query to insert a new user
	if (!execute_query_no_results(my_statement)) {
		cout << "Error inserting into Meal" << endl;
	}

}



//------------------------------------------------get meal id
int Calorie_counter_abstraction::get_meal_id(string date, string meal_type, int user_id) {
	
	int meal_id = -1;

	//query
	string sql = "SELECT meal_id FROM Meal WHERE Meal.date = ? AND Meal.meal_type = ? AND Meal.user_id = ?;";

	//statement pointer
	sqlite3_stmt* my_statement;

	if (execute_query_results(sql, my_statement)) {
		//bind parameters
		sqlite3_bind_text(my_statement, 1, date.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(my_statement, 2, meal_type.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(my_statement, 3, user_id);

		//get row from query
		int status_of_step = sqlite3_step(my_statement);

		//if there is a row
		if (status_of_step == SQLITE_ROW) {
			//get meal id
			
			meal_id = sqlite3_column_int(my_statement, 0);
		}

		//clean and destroy
		sqlite3_finalize(my_statement);
	}
	
	return meal_id;
}

//------------------------------------------------get food id
int Calorie_counter_abstraction::get_food_id(string name) {
	
	int food_id;

	//query
	string sql = "SELECT food_id FROM Food WHERE Food.name = ?;";

	//statement pointer
	sqlite3_stmt* my_statement;

	if (execute_query_results(sql, my_statement)) {
		//bind parameters
		sqlite3_bind_text(my_statement, 1, name.c_str(), -1, SQLITE_STATIC);

		//get row from query
		int status_of_step = sqlite3_step(my_statement);

		//if there is a row
		if (status_of_step == SQLITE_ROW) {
			//get food id
			food_id = sqlite3_column_int(my_statement, 0);
		}

		//clean and destroy
		sqlite3_finalize(my_statement);
	}
	return food_id;
}





//------------------------------------------------print all foods
void Calorie_counter_abstraction::print_all_foods() {
	//query
	string sql = "SELECT Food.name FROM Food";

	//create a statement pointer
	sqlite3_stmt* my_statement;

	//get a statement to iterate through
	if (execute_query_results(sql, my_statement)) {
		//get a row from the query
		int statusOfStep = sqlite3_step(my_statement);

		while (statusOfStep == SQLITE_ROW) {
			//get food name
			string food_name((char*)sqlite3_column_text(my_statement, 0));

			cout << food_name << endl;

			//get the next row
			statusOfStep = sqlite3_step(my_statement);
		}

	}
}

//------------------------------------------------Login
int Calorie_counter_abstraction::login(string first, string last) {
	//returns whether or not the user is in the system
	int ret_val = -1;

	//query
	string sql = "SELECT User.user_id FROM User WHERE User.first = ?  AND User.last = ?;";

	//statement pointer
	sqlite3_stmt* my_statement;

	//execute
	if (execute_query_results(sql, my_statement)) {
		//bind parameters
		sqlite3_bind_text(my_statement, 1, first.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(my_statement, 2, last.c_str(), -1, SQLITE_STATIC);

		//get row from query
		int status_of_step = sqlite3_step(my_statement);

		//if there is a row
		if (status_of_step == SQLITE_ROW) {
			//get user id
			ret_val = sqlite3_column_int(my_statement, 0);
		}
		//clean and destory
		sqlite3_finalize(my_statement);
	}
	
	if (ret_val == -1) {
		cout << " \n  " << endl;
		cout << "ERROR USER IS NOT IN SYSTEM ENTER IN A VALID USER\n" << endl;
	}

	return ret_val; 
}


//------------------------------------------------get all food on a certain date
void Calorie_counter_abstraction::get_all_food_on_date(string date, int user_id) {
	//query
	string sql = "SELECT Food.name FROM Food, User, Food_in_a_meal, Meal WHERE User.user_id = Meal.user_id AND Meal.meal_id = Food_in_a_meal.meal_id AND Food.food_id = Food_in_a_meal.food_id AND Meal.date = ? AND User.user_id = ?;";

	//statement pointer 
	sqlite3_stmt* my_statement;

	if (execute_query_results(sql, my_statement)) {
		//bind parameters
		sqlite3_bind_text(my_statement, 1, date.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(my_statement, 2, user_id);

		//get a row from query
		int status_of_step = sqlite3_step(my_statement);
		
		cout << "food eaten on " << date << ":" << endl;


		//if there is a row
		while (status_of_step == SQLITE_ROW) {
			//print out all the food eaten that day
			string food((char*)sqlite3_column_text(my_statement, 0));
			cout << food << endl;

			//get next row
			status_of_step = sqlite3_step(my_statement);
		}

		//clean and destroy
		sqlite3_finalize(my_statement);
	}
}

//------------------------------------------------total calories on a certain date
void Calorie_counter_abstraction::total_calories_on_date(string date, int user_id) {
	int calorie_count = 0;
	//query
	string sql = "SELECT SUM(Food.calories) FROM Food, User, Food_in_a_meal, Meal WHERE User.user_id = Meal.user_id AND Meal.meal_id = Food_in_a_meal.meal_id AND Food.food_id = Food_in_a_meal.food_id AND Meal.date = ? AND User.user_id = ?;";

	//statement pointer
	sqlite3_stmt* my_statement;

	//execute
	if (execute_query_results(sql, my_statement)) {
		//bind parameters
		sqlite3_bind_text(my_statement, 1, date.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(my_statement, 2, user_id);
		
		
		//get 1st row
		int status_of_step = sqlite3_step(my_statement);

		cout << "Total calories eaten on " << date << ":";

		//go through rows
		if (status_of_step == SQLITE_ROW) {
			calorie_count = sqlite3_column_int(my_statement, 0);
			//print out total calories
			cout << "\n\n        " << calorie_count << endl;
		}

		//clean and destroy
		sqlite3_finalize(my_statement);

	}
}

//------------------------------------------------total calories on a certain date by category
void Calorie_counter_abstraction::total_calories_on_date_by_category(string date, int user_id) {
	//query
	string sql = "SELECT Food.type, SUM(Food.calories) FROM Food, User, Food_in_a_meal, Meal WHERE User.user_id = Meal.user_id AND Meal.meal_id = Food_in_a_meal.meal_id AND Food.food_id = Food_in_a_meal.food_id AND Meal.date = ? AND User.user_id = ? GROUP BY Food.type;";

	//statement pointer
	sqlite3_stmt* my_statement;

	//execute
	if (execute_query_results(sql, my_statement)) {
		//bind parameters
		sqlite3_bind_text(my_statement, 1, date.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(my_statement, 2, user_id);


		//get 1st row
		int status_of_step = sqlite3_step(my_statement);

		cout << "Total calories on " << date << " by category:\n\n" << endl;

		while (status_of_step == SQLITE_ROW) {
			//get the category and calories
			string category((char*)sqlite3_column_text(my_statement, 0));
			int calories = sqlite3_column_int(my_statement, 1);

			//print out results
			cout << category << setw(10) << calories << endl;

			//get next row
			status_of_step = sqlite3_step(my_statement);
		}

		//clean and destroy
		sqlite3_finalize(my_statement);
	}

}

//------------------------------------------------total calories between two dates
void Calorie_counter_abstraction::total_calories_between_dates(string start_date, string end_date, int user_id) {
	//query
	string sql = "SELECT SUM(Food.calories) AS total_calories FROM Food, User, Food_in_a_meal, Meal WHERE Meal.meal_id = Food_in_a_meal.meal_id AND User.user_id = Meal.user_id AND Food_in_a_meal.food_id = Food.food_id AND User.user_id = ? AND Meal.date >= ? AND Meal.date <= ?;";


	//statment pointer
	sqlite3_stmt*  my_statement;

	//execute
	if (execute_query_results(sql, my_statement)) {
		//bind parameters
		sqlite3_bind_int(my_statement, 1, user_id);
		sqlite3_bind_text(my_statement, 2, start_date.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(my_statement, 3, end_date.c_str(), -1, SQLITE_STATIC);

		//get 1st row
		int status_of_step = sqlite3_step(my_statement);

		cout << "Total calories between " << start_date << " and " << end_date << endl;

		//if there is a row
		if (status_of_step == SQLITE_ROW) {
			//get total calories
			int calories = sqlite3_column_int(my_statement, 0);
			
			//print out total
			cout << "\n\n         " << calories << endl;
		}
		//clean and destory
		sqlite3_finalize(my_statement);
	}


}

//------------------------------------------------total calories between two dates by category
void Calorie_counter_abstraction::total_calories_between_dates_by_category(string start_date, string end_date, int user_id) {
	//query
	string sql = "SELECT Food.type, SUM(Food.calories) AS total_calories FROM Food, User, Food_in_a_meal, Meal WHERE Meal.meal_id = Food_in_a_meal.meal_id AND User.user_id = Meal.user_id AND Food_in_a_meal.food_id = Food.food_id AND Meal.date >= ? AND Meal.date <= ? AND User.user_id = 1 GROUP BY Food.type;";

	//statement pointer
	sqlite3_stmt* my_statement;

	//execute
	if (execute_query_results(sql, my_statement)) {
		//bind parameters
		sqlite3_bind_text(my_statement, 1, start_date.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(my_statement, 2, end_date.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(my_statement, 3, user_id);

		//get row from query
		int status_of_step = sqlite3_step(my_statement);

		cout << "Total calories between " << start_date << " and " << end_date << "by category:\n\n" << endl;

		//go through the rows
		while (status_of_step == SQLITE_ROW) {
			//get the category and calories
			string category((char*)sqlite3_column_text(my_statement, 0));
			int calories = sqlite3_column_int(my_statement, 1);

			//print out
			cout << category << setw(10) << calories << endl;

			//get next row
			status_of_step = sqlite3_step(my_statement);
		}
		//clean and destroy
		sqlite3_finalize(my_statement);
	}

}