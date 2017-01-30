#pragma once

#include <string>
#include "sqlite3.h"

using namespace std;

class Database_abstraction {
public:
	Database_abstraction(string Path);
	~Database_abstraction();

protected:
	//the pointer to the database
	sqlite3* dp_pointer;

	//helper function
	bool execute_query_no_results(string sql);
	bool execute_query_no_results(sqlite3_stmt*& my_statement);
	bool execute_query_results(string sql, sqlite3_stmt*& my_statement);
};
