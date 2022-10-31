#pragma once
#include <string>
#include <fstream>

using namespace std;

class station
{
public:
	station();
	void info();
	void finfo(ofstream& file);

	string name;
	int id;
	int tworks;
	int aworks;
	float efficiency;
};

