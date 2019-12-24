#include "Company.h"

void Company::copyFrom(const Company & other)
{

}

void Company::clear()
{
    clearHelp(boss);
	delete boss;
}

void Company::clearHelp(Node* start)
{
	int size = start->subordinates.size();
	for (int i = 0; i < size; ++i)
	{
		if (isLeaf(start->subordinates[i]))
		{
			delete start->subordinates[i];
		}
		else
		{
			clearHelp(start->subordinates[i]);
			delete start->subordinates[i];
		}
	}
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
			delete start->subordinates[i];
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
			delete start->subordinates[i];
			start->subordinates.erase(start->subordinates.begin() + i);
		}
		else if(!isLeaf(start->subordinates[i]))
		{
			removeVertex(start->subordinates[i], name);
		}
	}
}


void Company::transferOfSubord(Node * newEmp, std::vector<std::string> subord)
{
	int size = subord.size();
	Node* empl;
	for (int i = 0; i < size; ++i)
	{
		if (isEmployeeInCompany(boss, subord[i]))
		{
			Employee em(subord[i]);
			empl = new Node(em);
			newEmp->subordinates.push_back(empl);
		}
	}
}



bool Company::isEmployeeInCompany(Node * start, std::string name)
{
	int size = start->subordinates.size();                       //bez da proverqvam za imeto na boss
	for (int i = 0; i < size; ++i)
	{
		if (start->subordinates[i]->empl.name == name)
		{
			if (isLeaf(start->subordinates[i]))
			{
				delete start->subordinates[i];
				start->subordinates.erase(start->subordinates.begin() + i);
			}
			else
			{
				int sizeSub = start->subordinates[i]->subordinates.size();
				for (int j = 0; j < sizeSub; ++j)
				{
					start->subordinates.push_back(start->subordinates[i]->subordinates[j]);
				}
				delete start->subordinates[i];
				start->subordinates.erase(start->subordinates.begin() + i);
			}
			return true;
		}
		else if (!isLeaf(start->subordinates[i]))
		{
			if (isEmployeeInCompany(start->subordinates[i], name))
			{
				return true;
			}
		}
	}
	return false;
}

bool Company::isEmployeeDifferentFromFirstLevel(std::string name)
{
	int size = boss->subordinates.size();
	for (int i = 0; i < size; ++i)
	{
		if (name == boss->subordinates[i]->empl.name)
		{
			return false;
		}
	}
	return true;
}

void Company::hireEmployee(Node* start, std::string name, std::vector<std::string> subord)
{
	int size = start->subordinates.size();
	bool hasThisEmployee = false;
	Node* hiredEmpl = new Node(Employee(name));
	for (int i = 0; i < size; ++i)
	{
		if (start->subordinates[i]->empl.name == name)
		{
			Node* bossOfTheBoss;
			findBossOfTheBoss(boss, bossOfTheBoss, start->empl.name);
			int sizeSub = start->subordinates[i]->subordinates.size();
			for (int j = 0; j < sizeSub; ++j)
			{
				start->subordinates.push_back(start->subordinates[i]->subordinates[j]);
			}
			bossOfTheBoss->subordinates.push_back(hiredEmpl);
			delete start->subordinates[i];
			start->subordinates.erase(start->subordinates.begin() + i);
			hasThisEmployee = true;
		}
		else if(!isLeaf(start->subordinates[i]))
		{
			hireEmployee(start->subordinates[i], name, subord);
		}
	}
	if (hasThisEmployee)
	{
		transferOfSubord(hiredEmpl, subord);
		return;
	}
	delete hiredEmpl;
}

void Company::findBossOfTheBoss(Node * start, Node*& bossOfTheBoss, std::string name)
{
	int size = start->subordinates.size();
	for (int i = 0; i < size; ++i)
	{
		if (start->subordinates[i]->empl.name == name)
		{
			bossOfTheBoss = start;
			return;
		}
		findBossOfTheBoss(start->subordinates[i], bossOfTheBoss, name);
	}
}

std::vector<std::string> Company::directSubExceptBoss(Node * start, std::string name)
{
	int size = start->subordinates.size();
	std::vector<std::string> directSub;
	for (int i = 0; i < size; ++i)
	{
		if (start->subordinates[i]->empl.name == name)
		{
			int sizeSub = start->subordinates[i]->subordinates.size();
			for (int j = 0; j < sizeSub; ++j)
			{
				directSub.push_back(start->subordinates[i]->subordinates[j]->empl.name);
			}
			return directSub;
		}
		else if (!isLeaf(start->subordinates[i]))
		{
			directSub = directSubExceptBoss(start->subordinates[i], name);
			if (!directSub.empty())
			{
				return directSub;
			}
		}
	}
	return directSub;
}

std::vector<std::string> Company::allSub(Node * empl)
{
	std::vector<std::string> all = directSubordinatesOf(empl->empl.name);
	int size = empl->subordinates.size();
	std::vector<std::string> newV;
	for (int i = 0; i < size; ++i)
	{
		if (!isLeaf(empl->subordinates[i]))
		{
			newV = allSub(empl->subordinates[i]);
			all.insert(all.end(), newV.begin(), newV.end());
		}
	}
	return all;
}

void Company::findEmployee(Node * start, Node*& empl, std::string name)
{
	if (start->empl.name == name)
	{
		empl = start;
		return;
	}
	int size = start->subordinates.size();
	for (int i = 0; i < size; ++i)
	{
		if (start->subordinates[i]->empl.name == name)
		{
			empl = start->subordinates[i];
			return;
		}
		findEmployee(start->subordinates[i], empl, name);
	}
}

std::string Company::findDirBoss(Node* start, std::string name)
{
	int size = start->subordinates.size();
	std::string bossOfEmpl;
	for (int i = 0; i < size; ++i)
	{
		if (start->subordinates[i]->empl.name == name)
		{
			return start->empl.name;
		}
		else if (!isLeaf(start->subordinates[i]))
		{
			bossOfEmpl = findDirBoss(start->subordinates[i], name);
			if (!bossOfEmpl.empty())
			{
				return bossOfEmpl;
			}
		}	
	}
	return bossOfEmpl;
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

void Company::appointmentWithSubordinates(std::string nameOfANewMember, std::string nameOfHisBoss, std::vector<std::string> subord)
{
	Employee newEm(nameOfANewMember);
	Node* newNode = new Node(newEm);
	if (nameOfHisBoss == boss->empl.name)
	{
		boss->subordinates.push_back(newNode);
	}
	else
	{
		addLeaf(boss, newNode, nameOfHisBoss);
	}
	transferOfSubord(newNode, subord);
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

void Company::hiringEmployee(std::string nameOfAnEmployee, std::vector<std::string> subord)
{
	if (nameOfAnEmployee != boss->empl.name && isEmployeeDifferentFromFirstLevel(nameOfAnEmployee))
	{
		hireEmployee(boss, nameOfAnEmployee, subord);
	}
}

std::vector<std::string> Company::directSubordinatesOf(std::string nameOfAnEmployee)
{
	std::vector<std::string> directSub;
	if (nameOfAnEmployee == boss->empl.name)
	{
		int size = boss->subordinates.size();
		for (int i = 0; i < size; ++i)
		{
			directSub.push_back(boss->subordinates[i]->empl.name);
		}
	}
	else
	{
		directSub = directSubExceptBoss(boss, nameOfAnEmployee);
	}
	return directSub;
}

std::vector<std::string> Company::allSubordinatesOf(std::string nameOfAnEmployee)
{
	Node* empl;
	findEmployee(boss, empl, nameOfAnEmployee);
	return allSub(empl);
}

std::string Company::directBoss(std::string nameOfAnEmployee)
{
	if (nameOfAnEmployee == boss->empl.name)
	{
		return boss->empl.name;
	}
	return findDirBoss(boss, nameOfAnEmployee);
}


