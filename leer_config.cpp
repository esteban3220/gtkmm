#include "leer_config.hpp"

leer_config::leer_config()
{
    conf p = new config();
    std::ifstream archivoIn("config.bin", std::ios::in | std::ios::binary);
	if (!archivoIn) {
		std::cerr << "Info: Archivo de Configuracion no encontrado... Ayudante de configuracion en ejecucion." << std::endl;
		return;
	}
	archivoIn.seekg(0, std::ios::beg);
	archivoIn.read(reinterpret_cast<char *>(&p), sizeof(config));
	while (!archivoIn.eof())
	{
		user = p->usuario;
        server = p->servidor;
        password = p->contrasena;
		archivoIn.read(reinterpret_cast<char *>(&p), sizeof(config));
	}
	archivoIn.close();
}

leer_config::~leer_config()
{
}

std::string leer_config::get_password(){
    return this->password;
}
std::string leer_config::get_user(){
    return this->user;
}
std::string leer_config::get_server(){
    return this->server;
}