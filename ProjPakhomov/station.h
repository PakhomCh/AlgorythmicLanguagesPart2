#pragma once
#include <string>

using namespace std;

class station
{
public:
	station();
	void info();

	string name;
	int id;
	int tworks;
	int aworks;
	float efficiency;
};

