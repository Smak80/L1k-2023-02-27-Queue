#include <iostream>
#include <fstream>
#include <ctime>
#include "queue.h"

using namespace std;
void distribute(const char* filename, queue& empl_q, queue& unempl_q);
man create_man(char* man_data);
bool is_employable(man m);
void save(const char* filename, queue& q);

void distribute(const char* filename, queue& empl_q, queue& unempl_q)
{
	ifstream f(filename);
	if (f.is_open())
	{
		const int linelen = 256;
		char* line = new char[linelen];
		while (!f.eof())
		{
			f.getline(line, linelen);
			auto man = create_man(line);
			if (is_employable(man))
			{
				enqueue(empl_q, man);
			} else
			{
				enqueue(unempl_q, man);
			}
		}
		delete[] line;
		f.close();
	}
}

man create_man(char* man_data)
{
	man m;
	char* name = new char[50];
	sscanf_s(man_data, "%s %d", name, 50, &m.year);
	strcpy_s(m.name, name);
	delete[] name;
	return m;
}

bool is_employable(man m)
{
	auto now = time(nullptr);
	tm* dt = new tm;
	localtime_s(dt, &now);
	auto current_year = dt->tm_year + 1900;
	auto age = current_year - m.year;
	delete dt;
	return age >= 14 && age < 65;
}

void save(const char* filename, queue& q)
{
	ofstream f(filename);
	if (f.is_open())
	{
		man m;
		while (dequeue(q, m))
		{
			f << m.name << " " << m.year << endl;
		}
		f.close();
	}
}

void main()
{
	queue q1, q2;
	distribute("List.txt", q1, q2);
	save("employable.txt", q1);
	save("uneployable.txt", q2);
}