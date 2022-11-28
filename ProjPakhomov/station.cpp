#include <iostream>
#include <string>
#include <fstream>

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
	cout << "\t �����: " << aworks << " / " << tworks << ";" << endl;
	cout << "\t �������������: " << efficiency << ";" << endl;
	cout << "\t ��������� �������: ";
	for (int i = 0; i < adjacent.size(); i++)
		cout << adjacent[i].id << " ";
	cout << endl;
}

void station::finfo(ofstream& file)
{
	file << id << endl;
	file << name << endl;
	file << tworks << " ";
	file << aworks << " ";
	file << efficiency << endl;
}
