#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "tube.h"

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
	vector<station> adjacent;
	vector<tube> connections;
};

