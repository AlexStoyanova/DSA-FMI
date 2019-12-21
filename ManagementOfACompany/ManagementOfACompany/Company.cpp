#include "Company.h"


void Company::copyFrom(const Company & other)
{
}

void Company::clear()
{
}

bool Company::isLeaf(Node * elem)
{
	return elem->subordinates.empty();
}

void Company::addLeaf(Node* start, Node * newEmp, std::string name)
{
	int size = start->subordinates.size();
	for (int i = 0; i < size; ++i)
	{
		if (start->subordinates[i]->empl.name == name)
		{
			start->subordinates[i]->subordinates.push_back(newEmp);
			return;
		}
		else if (!isLeaf(start->subordinates[i]))
		{
			addLeaf(start->subordinates[i], newEmp, name);
		}
	}
}

void Company::removeLeaf(Node* start, std::string name)
{
	int size = start->subordinates.size();
	for (int i = 0; i < size; ++i)
	{
		if (isLeaf(start->subordinates[i]) && start->subordinates[i]->empl.name == name)
		{
			start->subordinates.erase(start->subordinates.begin() + i);
			return;
		}
		else if (!isLeaf(start->subordinates[i]))
		{
			removeLeaf(start->subordinates[i], name);
		}
	}
}

Company::Company(std::string nameOfABoss)
{
	Employee b(nameOfABoss);
	boss = new Node(b);
}

Company::Company(const Company & other)
{
	copyFrom(other);
}

Company & Company::operator=(const Company & rhs)
{
	if (this != &rhs)
	{
		clear();
		copyFrom(rhs);
	}
	return *this;
}

Company::~Company()
{
	clear();
}

void Company::appointmentWithoutSubordinates(std::string nameOfANewMember, std::string nameOfHisBoss)
{
	Employee newEm(nameOfANewMember);
	Node* newNode = new Node(newEm);
	if (nameOfHisBoss == boss->empl.name)
	{
		boss->subordinates.push_back(newNode);
		return;
	}
	addLeaf(boss, newNode, nameOfHisBoss);
}

void Company::appointmentWithSubordinates(std::string nameOfANewMember, std::string nameOfHisBoss)
{

}

void Company::firingEmployeeWithoutSubordinates(std::string nameOfAnEmployee)
{
	if (nameOfAnEmployee == boss->empl.name)
	{
		return;
	}
	removeLeaf(boss, nameOfAnEmployee);
}

void Company::firingEmployeeWithSubordinates(std::string nameOfAnEmployee)
{
}

void Company::risingEmployee(std::string nameOfAnEmployee)
{
}
