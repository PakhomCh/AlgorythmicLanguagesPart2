#include <iostream>
#include <string>

#include "station.h"

using namespace std;

station::station()
{
	name = "Unknown station";
	tworks = 0;
	aworks = 0;
	efficiency = 0;
}

void station::info()
{
	cout << "[ " << id << " ] " << name << ": " << endl;
	cout << "\t ÷ехов: " << aworks << " / " << tworks << ";" << endl;
	cout << "\t Ёффективность: " << efficiency << ";" << endl;
}
