#include <iostream>
#include <string>
#include <fstream>

#include "tube.h"

using namespace std;

tube::tube()
{
	name = "Unknown tube";
	length = 0;
	diameter = 0;
	status = false;
}

void tube::info()
{
	cout << "[ " << id << " ] " << name << ": " << endl;
	cout << "\t �����: " << length << ";" << endl;
	cout << "\t �������: " << diameter << ";" << endl;
	if (status)
		cout << "\t ������: � ������;" << endl;
	else
		cout << "\t ������: � �������;" << endl;
}

void tube::finfo(ofstream& file)
{
	file << id << endl;
	file << name << endl;
	file << length << " ";
	file << diameter << " ";
	file << status << endl;
}
