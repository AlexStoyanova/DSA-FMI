#include "Company.h"

void Company::copyFrom(const Company & other)
{
	boss = nullptr;
	boss = new Node(other.boss->empl.name);
	copyHelp(boss, other.boss);
}

void Company::copyHelp(Node* ours, Node * theirs)
{
	int size = theirs->subordinates.size();
	for (int i = 0; i < size; ++i)
	{
		addLeafConstant(ours, theirs->subordinates[i]->empl.name);
		if (!isLeaf(theirs->subordinates[i]))
		{
			copyHelp(ours->subordinates[i], theirs->subordinates[i]);
		}
	}
}

void Company::addLeafConstant(Node * ours, const std::string& newEmpl)
{
	Node* newNode = new Node(Employee(newEmpl));
	ours->subordinates.push_back(newNode);
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

bool Company::isLeaf(const Node * elem) const
{
	return elem->subordinates.empty();
}

void Company::addLeaf(Node* start, Node * newEmp, const std::string& name)
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

void Company::removeLeaf(Node* start, const std::string& name)
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


int Company::maxHeightFromEmployee(Node* start) const
{
	return 1 + maxHeightForEmployeeSubord(start->subordinates);
}

int Company::maxHeightForEmployeeSubord(const std::vector<Node*>& subord) const
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

int Company::maxElemHelp(const std::vector<int>& arr) const
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

void Company::removeVertex(Node * start, const std::string& name)
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


void Company::transferOfSubord(Node * newEmp, const std::vector<std::string> subord)
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


bool Company::isEmployeeInCompany(Node * start, const std::string& name)
{
	int size = start->subordinates.size();                       //without checking for the boss name
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

bool Company::isEmployeeDifferentFromFirstLevel(const std::string& name) const
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

void Company::hireEmployee(Node* start, const std::string& name, const std::vector<std::string> subord)
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

void Company::findBossOfTheBoss(Node * start, Node*& bossOfTheBoss, const std::string& name) const
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

std::vector<std::string> Company::directSubExceptBoss(Node * start, const std::string& name) const
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

std::vector<std::string> Company::allSub(Node * empl) const
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

void Company::findEmployee(Node * start, Node*& empl, const std::string& name) const
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

std::string Company::findDirBoss(Node* start, const std::string& name) const
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

Company::Company(const std::string nameOfABoss)
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

void Company::appointmentWithoutSubordinates(const std::string& nameOfANewMember, const std::string& nameOfHisBoss)
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

void Company::appointmentWithSubordinates(const std::string& nameOfANewMember, const std::string& nameOfHisBoss, const std::vector<std::string> subord)
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

void Company::firingEmployeeWithoutSubordinates(const std::string& nameOfAnEmployee)
{
	if (nameOfAnEmployee != boss->empl.name)
	{
		removeLeaf(boss, nameOfAnEmployee);
	}	
}

void Company::firingEmployeeWithSubordinates(const std::string& nameOfAnEmployee)
{
	if (nameOfAnEmployee != boss->empl.name)
	{
		removeVertex(boss, nameOfAnEmployee);
	}
}

void Company::hiringEmployee(const std::string& nameOfAnEmployee, const std::vector<std::string> subord)
{
	if (nameOfAnEmployee != boss->empl.name && isEmployeeDifferentFromFirstLevel(nameOfAnEmployee))
	{
		hireEmployee(boss, nameOfAnEmployee, subord);
	}
}

std::vector<std::string> Company::directSubordinatesOf(const std::string& nameOfAnEmployee) const
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

std::vector<std::string> Company::allSubordinatesOf(const std::string& nameOfAnEmployee) const 
{
	Node* empl;
	findEmployee(boss, empl, nameOfAnEmployee);
	return allSub(empl);
}

std::string Company::directBoss(const std::string& nameOfAnEmployee) const
{
	if (nameOfAnEmployee == boss->empl.name)
	{
		return boss->empl.name;
	}
	return findDirBoss(boss, nameOfAnEmployee);
}