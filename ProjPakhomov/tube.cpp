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
	cout << "\t Длина: " << length << ";" << endl;
	cout << "\t Диаметр: " << diameter << ";" << endl;
	if (status)
		cout << "\t Статус: В работе;" << endl;
	else
		cout << "\t Статус: В ремонте;" << endl;
}

void tube::finfo(ofstream& file)
{
	file << id << endl;
	file << name << endl;
	file << length << " ";
	file << diameter << " ";
	file << status << endl;
}
