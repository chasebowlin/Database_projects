#include <iostream>
#include "Database_abstraction.h"
#include "sqlite3.h"

using namespace std;

Database_abstraction::Database_abstraction(string path) {
	
	//try to open the database
	int statusOpen = sqlite3_open(path.c_str(), &dp_pointer);

	//if it couldnot open the database
	if (statusOpen != SQLITE_OK) {
		dp_pointer = NULL;
	}

	//else the pointer is connected to the open database
}

//----------------------------------------------Database_abstraction()
Database_abstraction::~Database_abstraction() {
	//make sure the pointer is still pointing to an open database
	if (dp_pointer != NULL) {
		//close the database
		sqlite3_close(dp_pointer);

		//nullify the pointer
		dp_pointer = NULL;
	}
}

//----------------------------------------------execute_query_no_results(string sql)
bool Database_abstraction::execute_query_no_results(string sql) {
	//assume something went wrong executing the query
	bool return_val = false;

	//create a statement pointer
	sqlite3_stmt* my_statement;

	//create the statement object using prepare()
	int status_of_prepare = sqlite3_prepare_v2(dp_pointer, sql.c_str(), -1, &my_statement, NULL);

	//check to see if the prepared statement was created
	if (status_of_prepare == SQLITE_OK) {
		//execute the query with step()
		int status_of_step = sqlite3_step(my_statement);


		//SQLITE_DONE for queries that don't return a value
		if (status_of_step == SQLITE_DONE) {
			return_val = true;
		}

		//clean and destroy the statement
		sqlite3_finalize(my_statement);
	}

	//return success of query
	return return_val;
}

//----------------------------------------------execute_query_no_results(sqlite3_stmt*& my_statement)
bool Database_abstraction::execute_query_no_results(sqlite3_stmt*& my_statement) {
	//assume there was a problem executing query
	bool return_val = false;

	//execute the query with step()
	int status_of_step = sqlite3_step(my_statement);

	//SQLITE_DONE for queries that don't return a value
	if (status_of_step == SQLITE_DONE) {
		return_val = true;
	}

	//clean and destroy the statement
	sqlite3_finalize(my_statement);

	//return success of query
	return return_val;
}

//----------------------------------------------execute_query_results(string sql, sqlite3_stmt*& my_statement)
bool Database_abstraction::execute_query_results(string sql, sqlite3_stmt*& my_statement) {
	//assume there was a problem executing query
	bool return_val = false;

	//create the statement objuect using prepare()
	int status_of_prep = sqlite3_prepare_v2(dp_pointer, sql.c_str(), -1, &my_statement, NULL);

	//check to see if the prepared statement was created
	if (status_of_prep == SQLITE_OK) {
		return_val = true;
	}

	//return the success of the query
	return return_val;
}