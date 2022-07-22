#include <fstream>
#include <iostream>

class leer_config
{
private:
    typedef struct config
    {
        char *usuario;
        char *servidor;
        char *contrasena;
    } *conf;
    std::string user;
    std::string server;
    std::string password;
public:
    std::string get_server();
    std::string get_user();
    std::string get_password();
    leer_config();
    ~leer_config();
};
