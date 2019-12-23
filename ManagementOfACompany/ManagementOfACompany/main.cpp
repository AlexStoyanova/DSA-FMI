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
	//c.firingEmployeeWithoutSubordinates("Alexandra");
	
	//c.firingEmployeeWithSubordinates("Ivan");
	std::vector<std::string> subord = { "Gosho", "Greta", "Lada" };
	c.appointmentWithSubordinates("Vania", "Tanya", subord);
}

int main()
{
	test();


	return 0;
}