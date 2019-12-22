#ifndef COMPANY_H
#define COMPANY_H
#include <iostream>
#include <string>
#include <vector>

class Company
{
private:
	struct Employee
	{
		std::string name;
		Employee(std::string name) : name(name) {}
	};

	struct Node
	{
		Employee empl;
		std::vector<Node*> subordinates;
		Node(Employee em) : empl(em){}
	};

private:
	void copyFrom(const Company& other);
	void clear();
	
	bool isLeaf(Node* elem);
	void addLeaf(Node* start, Node* newEmp, std::string name);
	void removeLeaf(Node* start, std::string name);
	int maxHeightFromEmployee(Node* start);
	int maxHeightForEmployeeSubord(std::vector<Node*> subord);
	int maxElemHelp(std::vector<int> arr);
	void removeVertex(Node* start, std::string name);

public:
	Node* boss;

	Company(std::string nameOfABoss);
	Company(const Company& other);
	Company& operator=(const Company& rhs);
	~Company();

	void appointmentWithoutSubordinates(std::string nameOfANewMember, std::string nameOfHisBoss);
	void appointmentWithSubordinates(std::string nameOfANewMember, std::string nameOfHisBoss);
	void firingEmployeeWithoutSubordinates(std::string nameOfAnEmployee);
	void firingEmployeeWithSubordinates(std::string nameOfAnEmployee);
	void risingEmployee(Node* employeeForHiring, std::vector<Node*> subord);

	std::vector<Employee> directSubordinatesOf(std::string nameOfAnEmployee);
	std::vector<Employee> allSubordinatesOf(std::string nameOfAnEmployee);
	Employee directBoss(std::string nameOfAnEmployee);

	
};

#endif