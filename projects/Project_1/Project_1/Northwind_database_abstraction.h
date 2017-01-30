#pragma once

#include "Database_abstraction.h"

class Northwind_database_abstraction : Database_abstraction {
public:
	Northwind_database_abstraction(string path);
	~Northwind_database_abstraction();

	void query_1();
	void query_2();
	void query_3();
	void query_4();
	void query_5();
	void query_6();
	void query_7();
	void query_8();
	void query_9();
	void query_10();


private:
};
