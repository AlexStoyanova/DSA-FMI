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


int Company::maxHeightFromEmployee(Node* start)
{
	return 1 + maxHeightForEmployeeSubord(start->subordinates);
}

int Company::maxHeightForEmployeeSubord(std::vector<Node*> subord)
{
	if (subord.empty())
	{
		return 0;
	}
	std::vector<int> heights(subord.size());
	int size = subord.size();
	for (int i = 0; i < size; ++i)
	{
		heights[i] = maxHeightFromEmployee(subord[i]);
	}
	return maxElemHelp(heights);
}

int Company::maxElemHelp(std::vector<int> arr)
{
	int size = arr.size();
	int max = arr[0];
	for (int i = 0; i < size; ++i)
	{
		if (max < arr[i])
		{
			max = arr[i];
		}
	}
	return max;
}

void Company::removeVertex(Node * start, std::string name)
{
	int size = start->subordinates.size();
	int maxHeight = 0;
	int currHeight = 0;
	for (int i = 0; i < size; ++i)
	{
		if (start->subordinates[i]->empl.name == name)
		{
			int sizeSub = start->subordinates[i]->subordinates.size();
			Node* employeeForHiring;
			for (int j = 0; j < sizeSub; ++j)
			{
				currHeight = maxHeightFromEmployee(start->subordinates[i]->subordinates[j]);
				if (maxHeight < currHeight)
				{
					maxHeight = currHeight;
					employeeForHiring = start->subordinates[i]->subordinates[j];
				}
			}
			start->subordinates.push_back(employeeForHiring);
			for (int j = 0; j < sizeSub; ++j)
			{
				if (start->subordinates[i]->subordinates[j] != employeeForHiring)
				{
					employeeForHiring->subordinates.push_back(start->subordinates[i]->subordinates[j]);
				}				
			}
			start->subordinates.erase(start->subordinates.begin() + i);
		}
		else
		{
			removeVertex(start->subordinates[i], name);
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
	if (nameOfAnEmployee != boss->empl.name)
	{
		removeLeaf(boss, nameOfAnEmployee);
	}	
}

void Company::firingEmployeeWithSubordinates(std::string nameOfAnEmployee)
{
	if (nameOfAnEmployee != boss->empl.name)
	{
		removeVertex(boss, nameOfAnEmployee);
	}
}

void Company::risingEmployee(Node* employeeForHiring, std::vector<Node*> subord)
{
	
}
