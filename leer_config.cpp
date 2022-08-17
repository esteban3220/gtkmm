#include "leer_config.hpp"
#include <fstream>

void config::escribe_configuracion(std::string _user, std::string _server, std::string _password)
{
	std::cout << std::endl;
	std::ifstream archivo("config.bin");
	if (archivo.good())
	{
		if (remove("config.bin") != 0)
			perror("Error al borrar archivo!.");
		else
		{
			puts("El archivo conexíon reescriot!");
			myFile.adding_string(_user.c_str());
			myFile.adding_string(_server.c_str());
			myFile.adding_string(_password.c_str());
			myFile.save();
		}
	}
	else
	{
		puts("El archivo conexíon creado con exito!");
		myFile.adding_string(_user.c_str());
		myFile.adding_string(_server.c_str());
		myFile.adding_string(_password.c_str());
		myFile.save();
	}
}

void config::lee_configuracion()
{
	myFile.init();
	this->user = myFile.get_string(1);
	this->server = myFile.get_string(2);
	this->password = myFile.get_string(3);
}

config::config()
{
	std::ifstream archivo("config.bin");
	if (archivo.good())
	{
		std::cout << "Info: Archivo de configuracíon encontrado." << std::endl;
		lee_configuracion();
	}
	else
	{
		std::cerr << "Info: No hay archivo de configuracíon." << std::endl;
	}
}
std::string config::get_password()
{
	return password;
}
std::string config::get_user()
{
	return user;
}
std::string config::get_server()
{
	return server;
}