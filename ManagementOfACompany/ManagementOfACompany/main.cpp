#include "Company.h"

void test()
{
	Company c("Alexandra");
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
	//c.firingEmployeeWithoutSubordinates("Maria");
	
	//c.firingEmployeeWithSubordinates("Ivan");
	//std::vector<std::string> subord = { "Gosho", "Greta", "Lada" };
	//c.appointmentWithSubordinates("Vania", "Tanya", subord);
	//c.hiringEmployee("Nia", subord);

	//std::vector<std::string> subords = c.allSubordinatesOf("Gosho");
	//std::vector<std::string> subords = c.directSubordinatesOf("Nia");
	/*for (int i = 0; i < subords.size(); ++i)
	{
		std::cout << subords[i] << std::endl;
	}*/
	//std::cout << c.directBoss("Ivan");
	Company d(c);
	std::cout << d.directBoss("Sian");
}

int main()
{
	test();

	return 0;
}