#pragma once

#include <cstring>
#include <mariadb/conncpp.hpp>
#include "leer_config.cpp"

class coneccion
{
private:
    leer_config *configuracion = new leer_config();
protected:
    sql::Driver *driver;
    sql::SQLString url;
    sql::Properties properties;
public:
    coneccion();
    bool conecta(std::string user,std::string password);
    bool comprueba_configuracion();
    bool comprueba_configuracion_bienvenida(std::string user,std::string password,std::string server);
    void instala_bd(std::string user,std::string password,std::string server);
    void instala_bd_part2(std::string user, std::string password, std::string server);
}*hola;
