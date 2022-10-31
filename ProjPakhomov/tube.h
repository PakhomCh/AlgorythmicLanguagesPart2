#pragma once
#include <string>
#include <fstream>

using namespace std;

class tube
{
public:
	tube();
	void info();
	void finfo(ofstream& file);

	string name;
	int id;
	int length;
	int diameter;
	bool status;
};

