#include "functions.h"

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

void generateEmployees(Person* employees, int size)
{
	for (int i = 0; i < size; i++)
		employees[i] = generatePerson();
}

BirthDate generateBirthDate()
{
	int max_age = 70;
	int min_age = 18;

	BirthDate date;

	// �������� ������� ���
	std::time_t t = std::time(NULL);
	std::tm cur_time;
	localtime_s(&cur_time, &t);
	int cur_year = 1900 + cur_time.tm_year;

	date.year = rand() % (max_age - min_age) + (cur_year - max_age);

	date.month = (Month)(rand() % 12 + 1);

	if (date.month == Month::FEBRUARY)
		date.day = rand() % 28 + 1;
	else if (date.month == Month::APRIL
		|| date.month == Month::JUNE
		|| date.month == Month::SEPTEMBER
		|| date.month == Month::NOVEMBER)
		date.day = rand() % 30 + 1;
	else
		date.day = rand() % 31 + 1;

	return date;
}

std::string generateName(Sex sex)
{
	std::vector<std::string> names;			// �����
	std::vector<std::string> middle_names;	// ��������
	std::vector<std::string> surnames;		// �������

	if (sex == Sex::FEMALE)
	{
		names = { "����", "������", "���������", "�������" };
		middle_names = { "��������", "��������", "������������", "��������" };
		surnames = { "��������", "��������", "���������", "����������"};
	}
	else
	{
		names = { "�����", "��������", "������", "����", "����������" };
		middle_names = { "�������������", "�����", "���������", "������������", "���������" };
		surnames = { "������", "�����", "������", "��������", "��������" };
	}

	return std::string(surnames[rand() % surnames.size()] + " "
		+ names[rand() % names.size()] + " "
		+ middle_names[rand() % middle_names.size()]);
}

Person generatePerson()
{
	Person p;
	p.sex = (Sex)(rand() % 2);
	p.name = generateName(p.sex);
	p.birth_date = generateBirthDate();

	return p;
}

void fillEmployees(Person* employees, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << "Input a name: ";
		std::cin.ignore();	// ���������� ��������� ������� ������ (\n)
		std::getline(std::cin, employees[i].name);
		std::cout << "\n";

		char sex = 0;
		std::cout << "Input a sex [M]ale, [F]emale: ";
		std::cin >> sex;
		std::cout << "\n";

		int loop = true;
		while (loop)
		{
			switch (sex)
			{
			case 'M':
				loop = false;
				employees[i].sex = Sex::MALE;
				break;
			case 'F':
				loop = false;
				employees[i].sex = Sex::FEMALE;
				break;
			default:
				std::cout << "Ooops, wrong input. Choose one from [M, F]: ";
				std::cin >> sex;
				std::cout << "\n";
				break;
			}
		}

		int day = 0, month = 0, year = 0;
		std::cout << "Input a birth date in numbers (day, month, year): ";
		std::cin >> day >> month >> year;
		std::cout << "\n";

		employees[i].birth_date = BirthDate{ day, (Month)month, year };
	}
}

void printEmployees(Person* employees, int size)
{
	for (int i = 0; i < size; i++)
		printPersonInfo(employees[i]);
}

inline void printPersonInfo(Person person)
{
	std::cout << "Name: " << person.name << "\n";
	std::cout << "Sex: " << ((int)person.sex == 0 ? "MALE" : "FEMALE") << "\n";

	std::tm time;
	time.tm_year = person.birth_date.year - 1900;
	time.tm_mon = (int)person.birth_date.month - 1;
	time.tm_mday = person.birth_date.day;

	std::cout << "Birth Date: " << std::put_time(&time, "%d.%m.%Y") << "\n\n";
}

Person* searchByName(std::string name, Person* employees, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (employees[i].name == name)
			return &employees[i];
	}

	return nullptr;
}

void formCrossSectionByYearOfBirth(int year, char type, Person* employees, int size)
{
	if (type == 'A')
	{
		for (int i = 0; i < size; i++)
			if (employees[i].birth_date.year > year)
				printPersonInfo(employees[i]);
	}
	else
	{
		for (int i = 0; i < size; i++)
			if (employees[i].birth_date.year < year)
				printPersonInfo(employees[i]);
	}
}

void employeesStatisticsBySex(Sex sex, Person* employees, int size)
{
	for (int i = 0; i < size; i++)
		if (employees[i].sex == sex)
			printPersonInfo(employees[i]);
}

void sortByAge(char type, Person* employees, int size)
{
	customCompareByDate compare;
	compare.m_type = type;

	std::sort(employees, employees + size, compare);
}