#include <cstring>
#include <mariadb/conncpp.hpp>

class coneccion
{
protected:
    sql::Driver *driver;
    sql::SQLString url;
    sql::Properties properties;
public:
    coneccion();
    bool conecta(std::string user,std::string password);
}*hola;
