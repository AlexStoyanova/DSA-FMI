#include "Company.h"

void test()
{
	//Make company with boss Alexandra
	Company c("Alexandra");

	//Add new employees without subordinates
	c.appointmentWithoutSubordinates("Sian", "Alexandra");
	c.appointmentWithoutSubordinates("Tanya", "Alexandra");
	c.appointmentWithoutSubordinates("Ivan", "Alexandra");
	c.appointmentWithoutSubordinates("Lada", "Sian");
	c.appointmentWithoutSubordinates("Lyuba", "Sian");
	c.appointmentWithoutSubordinates("Petya", "Tanya");
	c.appointmentWithoutSubordinates("Gosho", "Ivan");
	c.appointmentWithoutSubordinates("Nia", "Ivan");
	c.appointmentWithoutSubordinates("Greta", "Nia");
	c.appointmentWithoutSubordinates("Stefan", "Nia");
	c.appointmentWithoutSubordinates("Maria", "Gosho");
	c.appointmentWithoutSubordinates("Silvia", "Gosho");

	//Firing an employee without subordinates
	c.firingEmployeeWithoutSubordinates("Maria");
	
	//Firing an employee with subordinates 
	c.firingEmployeeWithSubordinates("Ivan");

	//Firing an employee with subordinares with balance 
	c.firingEmployeeWithSubordinates("Gosho");

	//Try to fire the boss of the company... we can't (nothing happens)
	c.firingEmployeeWithSubordinates("Alexandra");

	//Add employee and give him subordinates, Gosho is not in the company anymore 
	//so only Greta and Lada will become Vania's subordinates
	std::vector<std::string> subord = { "Gosho", "Greta", "Lada" };
	c.appointmentWithSubordinates("Vania", "Tanya", subord);

	//Hiring an employee, for Gosho is the same like the previous one
	c.hiringEmployee("Silvia", subord);

	//Take all subordinates of someone in the company, sorted by levels
	std::vector<std::string> subordAll = c.allSubordinatesOf("Alexandra");
	int sizeAll = subordAll.size();
	std::cout << "All subordinates of Alexandra:" << std::endl;
	for (int i = 0; i < sizeAll; ++i)
	{
		std::cout << subordAll[i] << std::endl;
	}

	//Take direct subordinates of someone in the company
	std::vector<std::string> subordDir = c.directSubordinatesOf("Tanya");
	int sizeDir = subordDir.size();
	std::cout << "\nDirect subordinates of Tanya:" << std::endl;
	for (int i = 0; i < sizeDir; ++i)
	{
		std::cout << subordDir[i] << std::endl;
	}

	//Take direct boss of someone in the company
	std::cout << "\nThe direct boss of Stefan is:" << std::endl;
	std::cout << c.directBoss("Stefan") << std::endl;

	//Show that the direct boss of the boss is the boss himself
	std::cout << "\nThe direct boss of Alexandra is:" << std::endl;
	std::cout << c.directBoss("Alexandra") << std::endl;

	//Show copy constructor
	Company d(c);

	std::cout << "\nThe direct boss of Sian in the original company is:" << std::endl;
	std::cout << c.directBoss("Sian") << std::endl;

	std::cout << "\nThe direct boss of Sian in the copy company is:" << std::endl;
	std::cout << d.directBoss("Sian") << std::endl;

	//Show operator=
	Company b("Someone");
	b = c;
}

int main()
{
	test();
	return 0;
}