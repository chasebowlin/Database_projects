#pragma once

#include "Database_abstraction.h"

class Calorie_counter_abstraction : Database_abstraction {
public:
	Calorie_counter_abstraction(string file_path);

	void add_user(string first, string last, int calorie_limit);
	void add_meal(string date, string meal_type, int user_id);
	void add_food(string name, string type, int calories);
	void add_into_food_in_a_meal(int food_id, int meal_id);


	int get_meal_id(string date, string meal_type, int user_id);
	int get_food_id(string name);

	void print_all_foods();
	int login(string first, string last);

	//queries
	void get_all_food_on_date(string date, int user_id);
	void total_calories_on_date(string date, int user_id);
	void total_calories_on_date_by_category(string date, int user_id);
	void total_calories_between_dates(string start_date, string end_date, int user_id);
	void total_calories_between_dates_by_category(string start_date, string end_date, int user_id);

	
private:
	void create_user_table();
	void create_meal_table();
	void create_food_table();
	void create_food_in_a_meal_table();
};