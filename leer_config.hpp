#include <iostream>
#include "binary_file.hpp"
class config
{
private:
    std::binaryfile myFile = "config.bin";
    std::string user;
    std::string server;
    std::string password;
public:
    std::string get_server();
    std::string get_user();
    std::string get_password();
    void escribe_configuracion(std::string _user, std::string _server, std::string _password);
    void lee_configuracion();
    void inserta_usuario(std::string tipo,std::string nombre, std::string password);
    config();
    ~config();
};
