#define backtube tubes.back()
#define backstation stations.back()

#include <iostream>
#include <fstream>
#include <locale>
#include <stdlib.h>
#include <string>
#include <vector>

#include "station.h"
#include "tube.h"

using namespace std;

template <typename T>
void read(T& value, istream& stream = cin, string comment = "Введите значение", float min = 0, float max = -1)
{
	if (typeid(stream) != typeid(ifstream))
		cout << comment << ": ";
	stream >> value;

	if (typeid(T) == typeid(int) || typeid(T) == typeid(float))
	{
		while (!stream || value < min || (value > max && max >= min))
		{
			if (typeid(stream) != typeid(ifstream))
				cout << comment << ": ";
			stream.clear();
			stream.ignore(numeric_limits<streamsize>::max(), '\n');
			stream >> value;
		}
	}

	if (typeid(T) == typeid(bool))
	{
		while (!stream)
		{
			if (typeid(stream) != typeid(ifstream))
				cout << comment << ": ";
			stream.clear();
			stream.ignore(numeric_limits<streamsize>::max(), '\n');
			stream >> value;
		}
	}
}

void read(string& value, istream& stream = cin, string comment = "Введите значение")
{
	if (typeid(stream) != typeid(ifstream))
		cout << comment << ": ";
	stream >> ws;
	getline(stream, value);
}

void menu(int blockid = 0) // 0 - END, 1 - MAIN MENU, 2 - CREATE MENU, 3 - VIEW MENU, 4 - TUBE MENU, 5 - STATION MENU
{
	system("CLS");
	switch (blockid)
	{
	case 1:
		cout << "1. Добавить элемент;" << endl;
		cout << "2. Просмотреть элементы;" << endl;
		cout << "3. Сохранить;" << endl;
		cout << "4. Загрузить;" << endl;
		cout << "5. Топологическая сортировка;" << endl;
		cout << "0. Выход;" << endl;
		break;

	case 2:
		cout << "1. Добавить трубу;" << endl;
		cout << "2. Добавить компрессорную станцию;" << endl;
		cout << "0. Выход;" << endl;
		break;

	case 3:
		cout << "1. Просмотр труб;" << endl;
		cout << "2. Просмотр компрессорных станций;" << endl;
		cout << "0. Выход;" << endl;
		break;

	case 4:
		cout << "1. Фильтровать трубы;" << endl;
		cout << "2. Сбросить фильтр;" << endl;
		cout << "3. Изменить трубы;" << endl;
		cout << "0. Выход;" << endl;
		break;

	case 5:
		cout << "1. Фильтровать компрессорные станции;" << endl;
		cout << "2. Сбросить фильтр;" << endl;
		cout << "3. Изменить компрессорную станцию;" << endl;
		cout << "4. Соединить компрессорные станции;" << endl;
		cout << "0. Выход;" << endl;
		break;
	}
}

pair <vector<tube>, vector<station>> load(string filename)
{
	pair <vector<tube>, vector<station>> data;

	ifstream file;
	file.open(filename);
	if (file)
	{
		int totalt, totals;
		read<int>(totalt, file);
		read<int>(totals, file);
		for (int i = 0; i < totalt; i++)
		{
			data.first.push_back(tube());
			read<int>(data.first.back().id, file);
			read(data.first.back().name, file);
			read<int>(data.first.back().length, file);
			read<int>(data.first.back().diameter, file);
			read<bool>(data.first.back().status, file);
		}
		for (int i = 0; i < totals; i++)
		{
			data.second.push_back(station());
			read<int>(data.second.back().id, file);
			read(data.second.back().name, file);
			read<int>(data.second.back().tworks, file);
			read<int>(data.second.back().aworks, file);
			read<float>(data.second.back().efficiency, file);
		}
		file.close();
	}
	else
		perror("Requested file not found. Empty file loaded instead.");
	return data;
}

void save(vector<tube> tubes, vector<station> stations, string filename) {
	ofstream file;
	file.open(filename);
	if (file)
	{
		file << tubes.size() << " " << stations.size() << endl;
		for (int i = 0; i < tubes.size(); i++)
			tubes[i].finfo(file);
		for (int i = 0; i < stations.size(); i++)
			stations[i].finfo(file);
	}
	else
		perror("Requested file not found. Empty file loaded instead.");

}

int min(vector <int> values)
{
	int min = values.back();
	for (int i = 0; i < values.size(); i++)
		min = (min < values[i]) ? min : values[i];
	return min;
}

vector <int> topology(station point, vector<int> colors)
{
	if (colors[point.id - 1] == 0)
		for (int i = 0; i < colors.size(); i ++)
			colors[i] = 0;
	if (colors[point.id - 1] > 0)
	{
		colors[point.id - 1] = 0;
		for (int i = 0; i < point.adjacent.size(); i++)
			colors = topology(point.adjacent[i], colors);
		colors[point.id - 1] = min(colors) - 1;
	}
		
	return colors;
}

void topocover(vector <station> stations)
{
	vector <int> colors;
	vector <int> backmap;
	for (int i = 0; i < stations.size(); i ++)
		colors.push_back(1);
	for (int i = 0; i < stations.size(); i ++)
		colors = topology(stations[i], colors);
	string order = "Порядок вершин: ";
	if (colors.back() == 0)
		read(order, cin, "Найден цикл. Нажмите любую клавишу, чтобы продолжить");
	else
	{
		/*for (int i = 0; i < colors.size(); i++)
			order += to_string(colors[i]) + " ";*/
		while (backmap.size() < stations.size())
		{
			for (int i = 0; i < colors.size(); i ++)
				if (backmap.size() * -1 - 1 == colors[i])
				{
					backmap.push_back(i);
					break;
				}
		}
		for (int i = backmap.size() - 1; i >= 0; i --)
			order += to_string(backmap[i] + 1) + " ";
		cout << order << endl;
		read(order, cin, "Нажмите любую клавишу, чтобы продолжить");
	}

}

int main()
{
	setlocale(LC_ALL, "Ru");

	int mode = 1; // 0 - END, 1 - MAIN MENU, 2 - CREATE MENU, 3 - VIEW MENU, 4 - TUBE MENU, 5 - STATION MENU
	int command, xcommand;
	vector <tube> tubes;
	vector <station> stations;

	string ftname = "";
	int ftstat = -1;

	string fsname = "";
	int fspers = -1;

	int edit;
	string filename;

	while (mode)
	{
		menu(mode);
		switch (mode)
		{
		case 1: // MAIN MENU
			read<int>(command, cin, "Выберите команду", 0, 5);
			switch (command)
			{
			case 1:
				mode = 2;
				break;

			case 2:
				mode = 3;
				break;

			case 3:
				read(filename, cin, "Введите название сохранения (save по умолчанию)");
				filename += ".txt";
				save(tubes, stations, filename);
				break;

			case 4:
				read(filename, cin, "Введите название сохранения (save по умолчанию)");
				filename += ".txt";
				tubes = load(filename).first;
				stations = load(filename).second;
				break;

			case 5:
				if(stations.size())
					topocover(stations);
				break;

			case 0:
				mode = 0;
				break;
			}
			break;

		case 2: // CREATE MENU
			read<int>(command, cin, "Выберите команду", 0, 2);
			switch (command)
			{
			case 1:
				tubes.push_back(tube());
				backtube.id = tubes.size();
				
				read(backtube.name, cin, "Введите название трубы");
				read<int>(backtube.length, cin, "Введите длину трубы", 1);
				read<int>(backtube.diameter, cin, "Введите диаметр трубы", 1);
				read<bool>(backtube.status, cin, "Введите статус трубы (1 - Работает, 0 - Нет)");

				break;

			case 2:
				stations.push_back(station());
				backstation.id = stations.size();

				read(backstation.name, cin, "Введите название КС");
				read<int>(backstation.tworks, cin, "Введите количество цехов");
				read<int>(backstation.aworks, cin, "Введите количество активных цехов (не более " + to_string(backstation.tworks) + ")", 0, backstation.tworks);
				read<float>(backstation.efficiency, cin, "Введите эффективность КС", 0, 1);

				break;

			case 0:
				mode = 1;
				break;
			}
			break;

		case 3: // VIEW MENU
			read<int>(command, cin, "Выберите команду", 0, 2);
			switch (command)
			{
			case 1:
				mode = 4;
				break;

			case 2:
				mode = 5;
				break;

			case 0:
				mode = 1;
				break;
			}
			break;

		case 4: // TUBE MENU

			cout << endl;

			for (int i = 0; i < tubes.size(); i++)
				if ((ftname == "" || tubes[i].name.find(ftname) != string::npos) && (ftstat == -1 || !!ftstat == tubes[i].status))
					tubes[i].info();
			if (tubes.size() == 0)
				cout << "Труб не добавлено" << endl;

			cout << endl;

			read<int>(command, cin, "Выберите команду", 0, 3);
			switch (command)
			{
			case 1:
				read<int>(command, cin, "Выберите фильтр (1 - По названию, 2 - По статусу)", 1, 2);
				if (command == 1)
					read(ftname, cin, "Введите название");
				else
					read<int>(ftstat, cin, "Введите статус (1 - Работает, 0 - Нет)");
				break;

			case 2:
				ftname = "";
				ftstat = -1;
				break;

			case 3:
				read<int>(command, cin, "Выберите тип редактирования (1 - Все выделенные, 2 - По ID)", 1, 2);
				if (command == 1)
				{
					read<int>(edit, cin, "Введите статус трубы (1 - Работает, 0 - Нет)", 0, 1);
					for (int i = 0; i < tubes.size(); i++)
						if ((ftname == "" || tubes[i].name.find(ftname) != string::npos) && (ftstat == -1 || !!ftstat == tubes[i].status))
							tubes[i].status = edit;
				}
				else
				{
					read<int>(command, cin, "Введите ID трубы", 1, tubes.size());
					for (int i = 0; i < tubes.size(); i++)
						if (tubes[i].id == command)
						{
							read<bool>(tubes[i].status, cin, "Введите статус трубы (1 - Работает, 0 - Нет)", 0, 1);
							break;
						}
				}
				break;

			case 0:
				mode = 3;
				break;
			}
			break;

		case 5: // STATION MENU

			cout << endl;

			for (int i = 0; i < stations.size(); i++)
				if ((fsname == "" || stations[i].name.find(fsname) != string::npos) && (fspers == -1 || fspers <= (100 * stations[i].aworks / stations[i].tworks)))
					stations[i].info();
			if (stations.size() == 0)
				cout << "Станций не добавлено" << endl;

			cout << endl;

			read<int>(command, cin, "Выберите команду", 0, 4);
			switch (command)
			{
			case 1:
				read<int>(command, cin, "Выберите фильтр (1 - По названию, 2 - По проценту задействованных цехов)", 1, 2);
				if (command == 1)
					read(fsname, cin, "Введите название");
				else
					read<int>(fspers, cin, "Введите целое число процентов", 0, 100);
				break;

			case 2:
				fsname = "";
				fspers = -1;
				break;

			case 3:
				read<int>(command, cin, "Введите ID компрессорной станции", 1, stations.size());
				for (int i = 0; i < stations.size(); i++)
					if (stations[i].id == command)
					{ 
						read<int>(stations[i].aworks, cin, "Введите новое число активных цехов", 0, stations[i].tworks);
						break;
					}
				break;

			case 4:
				read<int>(command, cin, "Введите ID начальной компрессорной станции", 1, stations.size());
				read<int>(xcommand, cin, "Введите ID конечной компрессорной станции", 1, stations.size());
				for (int i = 0; i < stations.size(); i ++)
					for (int j = 0; j < stations.size(); j++)
						if ((stations[i].id == command) && (stations[j].id == xcommand) && (i != j))
						{
							read<int>(command, cin, "Введите диаметр трубы для соединения", 1);
							xcommand = 1;
							for (int k = 0; k < tubes.size(); k ++)
								if (tubes[k].diameter == command)
								{
									xcommand = 0;
									stations[i].adjacent.push_back(stations[j]);
									stations[i].connections.push_back(tubes[k]);
								}
							if (xcommand)
							{
								read<int>(xcommand, cin, "Труба такого диаметра не найдена, создать новую? (1 - да, 0 - нет)", 0, 1);
								if (xcommand)
								{
									tubes.push_back(tube());
									backtube.id = tubes.size();

									read(backtube.name, cin, "Введите название трубы");
									read<int>(backtube.length, cin, "Введите длину трубы", 1);
									backtube.diameter = command;
									read<bool>(backtube.status, cin, "Введите статус трубы (1 - Работает, 0 - Нет)");
									stations[i].adjacent.push_back(stations[j]);
									stations[i].connections.push_back(backtube);
								}
							}

						}

			case 0:
				mode = 3;
				break;
			}
			break;
		}
		
		
		
	}
}
