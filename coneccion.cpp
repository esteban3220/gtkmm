#include "coneccion.hpp"

coneccion::coneccion()
{
    properties["hostName"] = "127.0.0.1";
    properties["userName"] = "esteban";
    properties["password"] = "junomava3842";
    url = ("jdbc:mariadb://localhost:3306/todo");
    driver = sql::mariadb::get_driver_instance();
}

bool coneccion::conecta(std::string user,std::string password)
{
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("select id,description from tasks where id=? and description=?"));

    stmnt->setString(1, user);
    stmnt->setString(2, password);
    return(stmnt->executeQuery()->first());
}