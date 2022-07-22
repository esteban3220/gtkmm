#include "coneccion.hpp"
#include <fstream>
#include <unistd.h>

coneccion::coneccion()
{
    // properties["hostName"] = configuracion->get_server();
    properties["userName"] = configuracion->get_user();
    properties["password"] = configuracion->get_password();
    url = ("jdbc:mariadb://" + configuracion->get_server() + ":3306/Tienda");
    driver = sql::mariadb::get_driver_instance();
}

bool coneccion::conecta(std::string user, std::string password)
{
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("select nombre from usuarios where nombre=? and contrasena=md5(?)"));

    stmnt->setString(1, user);
    stmnt->setString(2, password);
    conn->close();
    return (stmnt->executeQuery()->first());
}

bool coneccion::comprueba_configuracion()
{
    if (configuracion->get_password() == "" || configuracion->get_user() == "" || configuracion->get_server() == "")
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool coneccion::comprueba_configuracion_bienvenida(std::string user, std::string password, std::string server)
{
    properties["userName"] = user;
    properties["password"] = password;
    url = ("jdbc:mariadb://" + server + ":3306/test");
    driver = sql::mariadb::get_driver_instance();
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    sql::ResultSet *res = stmnt->executeQuery("show tables");
    return (res->next());
}

void coneccion::instala_bd(std::string user, std::string password, std::string server)
{
    properties["userName"] = user;
    properties["password"] = password;
    url = ("jdbc:mariadb://" + server + ":3306/");
    driver = sql::mariadb::get_driver_instance();
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    stmnt->execute("create database if not exists Tienda");
    stmnt->execute("use Tienda");
    stmnt->execute("DROP TABLE IF EXISTS Aud_producto");
    stmnt->execute("CREATE TABLE Aud_producto ("
                   "Id bigint(20) NOT NULL AUTO_INCREMENT,"
                   "Id_producto bigint(20) DEFAULT NULL,"
                   "Ant_nombre varchar(80),"
                   "Ant_descripcion varchar(80),"
                   "Ant_precio double(9,2) DEFAULT NULL,"
                   "Ant_cantidad bigint(20) DEFAULT NULL,"
                   "Ant_imagen varchar(80),"
                   "New_nombre varchar(80),"
                   "New_descripcion varchar(80),"
                   "New_precio double(9,2) DEFAULT NULL,"
                   "New_cantidad bigint(20) DEFAULT NULL,"
                   "New_imagen varchar(80),"
                   "Usuario varchar(100),"
                   "Fecha_mod timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),"
                   "Accion varchar(30),"
                   "PRIMARY KEY (Id)) ");
    stmnt->execute("DROP TABLE IF EXISTS Aud_proveedor");
    stmnt->execute("CREATE TABLE Aud_proveedor ("
                   "Id bigint(20) NOT NULL AUTO_INCREMENT,"
                   "Empresa varchar(45),"
                   "Nombre_ant varchar(60),"
                   "Direccion_ant varchar(90),"
                   "Telefono_ant bigint(20) DEFAULT NULL,"
                   "Region_ant varchar(50),"
                   "Pais_ant varchar(45),"
                   "RFC_ant varchar(45),"
                   "Estado_ant varchar(45),"
                   "Correo_ant varchar(60),"
                   "Nombre_new varchar(60),"
                   "Direccion_new varchar(90),"
                   "Telefono_new bigint(20) DEFAULT NULL,"
                   "Region_new varchar(50),"
                   "Pais_new varchar(45),"
                   "RFC_new varchar(45),"
                   "Estado_new varchar(45),"
                   "Correo_new varchar(60),"
                   "Usuario varchar(100),"
                   "Fecha_mod timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),"
                   "Accion varchar(30),"
                   " PRIMARY KEY (Id)) ");
    stmnt->execute("DROP TABLE IF EXISTS Aud_ticket");
    stmnt->execute(" CREATE TABLE Aud_ticket ("
                   "Id bigint(20) NOT NULL AUTO_INCREMENT,"
                   "Id_ticket bigint(20) DEFAULT NULL,"
                   "Ant_usuario varchar(80),"
                   "Ant_total double(9,2) DEFAULT NULL,"
                   "Ant_recibido double(9,2) DEFAULT NULL,"
                   "Ant_cambio double(9,2) DEFAULT NULL,"
                   "Ant_pago varchar(45),"
                   "Ant_hora varchar(45),"
                   "New_usuario varchar(80),"
                   "New_total double(9,2) DEFAULT NULL,"
                   "New_recibido double(9,2) DEFAULT NULL,"
                   "New_cambio double(9,2) DEFAULT NULL,"
                   "New_pago varchar(45),"
                   "New_hora varchar(45),"
                   "Usuario varchar(100),"
                   "Fecha_mod timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),"
                   "Accion varchar(30),"
                   "PRIMARY KEY (Id)) ");
    stmnt->execute("DROP TABLE IF EXISTS Carrito_compra");
    stmnt->execute("CREATE TABLE Carrito_compra ("
                   "No double(9,3) DEFAULT NULL,"
                   "Producto varchar(80) NOT NULL,"
                   "P_unitario double(9,2) DEFAULT NULL,"
                   "Subtotal double(9,2) DEFAULT NULL,"
                   "SKU bigint(20) NOT NULL,"
                   "PRIMARY KEY (SKU)) ");
    stmnt->execute("DROP TABLE IF EXISTS Corte_z");
    stmnt->execute("CREATE TABLE Corte_z ("
                   "Id bigint(20) NOT NULL AUTO_INCREMENT,"
                   "Gerente varchar(99),"
                   "Cajero varchar(99),"
                   "Ingreso double(9,2) DEFAULT NULL,"
                   "Balance double(9,2) DEFAULT NULL,"
                   "Status varchar(50),"
                   "Fecha varchar(45),"
                   "F_pago varchar(30),"
                   "PRIMARY KEY (Id))");
    stmnt->execute("DROP TABLE IF EXISTS Inventario");
    stmnt->execute("CREATE TABLE Inventario ("
                   "Cantidad bigint(20) DEFAULT NULL,"
                   "Balance_f int(11) DEFAULT NULL,"
                   "Balance double(9,2) DEFAULT NULL,"
                   "Usuario varchar(100),"
                   "Fecha timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),"
                   "Query varchar(100)) ");
    stmnt->execute("DROP TABLE IF EXISTS Inventario_temp");
    stmnt->execute("CREATE TABLE Inventario_temp ("
                   "SKU bigint(20) NOT NULL,"
                   "Nombre varchar(100),"
                   "Piezas double(9,3) DEFAULT NULL,"
                   "Valor double(9,2) DEFAULT NULL,"
                   "Ingreso double(9,3) DEFAULT NULL,"
                   "Fisico double(9,3) DEFAULT NULL,"
                   "Balance double(9,3) DEFAULT NULL,"
                   "PRIMARY KEY (SKU)) ");
    stmnt->execute("DROP TABLE IF EXISTS Proveedor");
    stmnt->execute("CREATE TABLE Proveedor ("
                   "Empresa varchar(45) ,"
                   "Nombre varchar(60),"
                   "Direccion varchar(90),"
                   "Telefono bigint(20) DEFAULT NULL,"
                   "Region varchar(50),"
                   "Pais varchar(45),"
                   "RFC varchar(45),"
                   "Estado varchar(45),"
                   "Correo varchar(60),"
                   "PRIMARY KEY (Empresa)) ");
    stmnt->execute("DROP TABLE IF EXISTS Producto");
    stmnt->execute("CREATE TABLE Producto ("
                   "SKU bigint(20) NOT NULL,"
                   "Nombre varchar(100),"
                   "Marca varchar(45),"
                   "Fecha_proc date DEFAULT NULL,"
                   "Fecha_cad date DEFAULT NULL,"
                   "Numero_lote int(11) DEFAULT NULL,"
                   "Nota varchar(100),"
                   "Piezas double(9,3) DEFAULT NULL,"
                   "Compra double(9,2) DEFAULT NULL,"
                   "Venta double(9,2) DEFAULT NULL,"
                   "Categoria varchar(30),"
                   "Subcategoria varchar(45),"
                   "PRIMARY KEY (SKU),"
                   "FOREIGN KEY (Marca) REFERENCES Proveedor (Empresa) ON DELETE CASCADE ON UPDATE CASCADE)");
    stmnt->execute("DROP TABLE IF EXISTS Ticket");
    stmnt->execute("CREATE TABLE Ticket ("
                   "Id_ticket bigint(20) unsigned zerofill NOT NULL AUTO_INCREMENT,"
                   "Usuario varchar(80),"
                   "Total double(9,2) DEFAULT NULL,"
                   "Recibido double(9,2) DEFAULT NULL,"
                   "Cambio double(9,2) DEFAULT NULL,"
                   "Tipo_pago varchar(45),"
                   "Query varchar(45),"
                   "Fecha_hora timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),"
                   "PRIMARY KEY (Id_ticket))");
    stmnt->execute("DROP TABLE IF EXISTS usuarios;"
                   "CREATE TABLE usuarios ("
                   "id int(11) NOT NULL AUTO_INCREMENT,"
                   "nombre varchar(50),"
                   "rol varchar(30),"
                   "contrasena varchar(30),"
                   "PRIMARY KEY (id),"
                   "UNIQUE KEY nombre (nombre))");
    conn->close();
}

void coneccion::instala_bd_part2(std::string user, std::string password, std::string server)
{
    properties["userName"] = user;
    properties["password"] = password;
    url = ("jdbc:mariadb://" + server + ":3306/");
    driver = sql::mariadb::get_driver_instance();
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    stmnt->execute("use Tienda");
    stmnt->execute("DROP TABLE IF EXISTS Tienda");
    stmnt->execute("CREATE TABLE Tienda ("
                   "Id_tienda int(3) unsigned zerofill NOT NULL AUTO_INCREMENT,"
                   "Nombre varchar(80),"
                   "RFC varchar(45),"
                   "Telefono bigint(20) DEFAULT NULL,"
                   "icono varchar(45),"
                   "PRIMARY KEY (Id_tienda)) ");
    stmnt->execute("DROP TABLE IF EXISTS Venta_ini");
    stmnt->execute("CREATE TABLE Venta_ini ("
                   "V_dia double(9,2) DEFAULT NULL,"
                   "User varchar(126) NOT NULL,"
                   "PRIMARY KEY (User)) ");
    stmnt->execute("DROP TABLE IF EXISTS Venta_total");
    stmnt->execute("CREATE TABLE Venta_total ("
                   "V_dia double(9,2) DEFAULT NULL,"
                   "fecha date NOT NULL,"
                   "PRIMARY KEY (fecha))");
    conn->close();

}