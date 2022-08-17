#include "coneccion.hpp"
#include <fstream>
#include <unistd.h>


coneccion::coneccion()
{
    properties["userName"] = configuracion->get_user();
    properties["password"] = configuracion->get_password();
    url = ("jdbc:mariadb://" + configuracion->get_server() + ":3306/Tienda");
    driver = sql::mariadb::get_driver_instance();
}

coneccion::coneccion(std::string usuario, std::string contrasena)
{
    properties["userName"] = usuario;
    properties["password"] = contrasena;
    url = ("jdbc:mariadb://" + configuracion->get_server() + ":3306/Tienda");
    driver = sql::mariadb::get_driver_instance();
}

bool coneccion::comprueba_gerente()
{
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    sql::ResultSet *res = stmnt->executeQuery("select nombre from usuarios where rol='Gerente'");
    conn->close();
    return (res->next());
}

bool coneccion::comprueba_configuracion()
{
    if (configuracion->get_password().empty() || configuracion->get_user().empty() || configuracion->get_server().empty())
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
    url = ("jdbc:mariadb://" + server + ":3306");
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    sql::ResultSet *res = stmnt->executeQuery("show databases");
    stmnt->execute("create database if not exists Tienda");
    conn->close();
    return (res->next());
}

void coneccion::instala_bd()
{
    configuracion->lee_configuracion();
    properties["userName"] = configuracion->get_user();
    properties["password"] = configuracion->get_password();
    url = ("jdbc:mariadb://" + configuracion->get_server() + ":3306/Tienda");
    driver = sql::mariadb::get_driver_instance();
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
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
                   "PRIMARY KEY (id),"
                   "UNIQUE KEY nombre (nombre))");
    conn->close();
}

void coneccion::instala_bd_part2()
{
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    stmnt->execute("DROP TABLE IF EXISTS Tienda");
    stmnt->execute("create table Tienda (id int unsigned zerofill AUTO_INCREMENT primary key, Nombre varchar(80), Telefono bigint, Direccion varchar(100), RFC varchar(100))");
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
    stmnt->execute("create OR REPLACE role Gerente");
    stmnt->execute("grant ALL PRIVILEGES on *.* to Gerente with grant option");
    stmnt->execute("create OR REPLACE role Lider");
    stmnt->execute("grant ALL on *.* to Lider");
    stmnt->execute("create OR REPLACE role Cajero");
    stmnt->execute("grant select,update,insert on *.Carrito_compra to Cajero");
    stmnt->execute("grant select,update on *.Producto to Cajero");
    stmnt->execute("grant select,update,insert on *.Venta_ini to Cajero");
    stmnt->execute("grant select,insert on *.Ticket to Cajero");
    stmnt->execute("grant select on *.Tienda to Cajero");
    conn->close();
}

// recibe "Gerente" o "Lider" o "Cajero" , nombre de usuario y contraseña
void coneccion::anade_usuario(std::string rol, std::string nombre, std::string password)
{
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    if (rol == "Gerente" || rol == "Lider" || rol == "Cajero")
    {
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert usuarios values (null,?,?)"));
        stmnt->setString(1, nombre);
        stmnt->setString(2, rol);
        stmnt->execute();
        std::unique_ptr<sql::PreparedStatement> stmnt2(conn->prepareStatement("CREATE USER ?@localhost IDENTIFIED BY ?"));
        stmnt2->setString(1, nombre);
        stmnt2->setString(2, password);
        stmnt2->execute();
        std::unique_ptr<sql::PreparedStatement> stmnt3(conn->prepareStatement("GRANT ? TO ?@localhost"));
        stmnt3->setString(1, rol);
        stmnt3->setString(2, nombre);
        stmnt3->execute();
    }
    else
    {
        std::cout << "Rol no valido" << std::endl;
    }
    conn->close();
}


std::vector <std::string> coneccion::lee_usuarios()
{
    std::vector <std::string> usuarios;
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery("select nombre from usuarios"));
    while (res->next())
    {
        usuarios.push_back(res->getString("nombre").c_str());
    }
    conn->close();
    return usuarios;
}

std::vector <std::string> coneccion::lee_marca()
{
    std::vector <std::string> marca;
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery("select Empresa from Proveedor"));
    while (res->next())
    {
        marca.push_back(res->getString("Empresa").c_str());
    }
    conn->close();
    return marca;
}

//Recibe nombre telefono y direccion de la tienda (opcional rfc (si es vacio ""))
void coneccion::datos_tienda(std::string nombre, std::string telefono, std::string direccion, std::string rfc)
{
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into Tienda values (null,?,?,?,?)"));
    stmnt->setString(1, nombre);
    stmnt->setString(2, telefono);
    stmnt->setString(3, direccion);
    stmnt->setString(4, rfc);
    stmnt->executeQuery();
    conn->close();
}

//devuelve un vector con los datos del usuario ya comprobado
std::vector<std::string> coneccion::conecta(std::string user, std::string password)
{
    std::vector<std::string> datos;
    properties["userName"] = user;
    properties["password"] = password;
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("select nombre,rol from usuarios where nombre=?"));
    stmnt->setString(1, user);
    std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
    while (res->next())
    {
        datos.push_back(res->getString("nombre").c_str());
        datos.push_back(res->getString("rol").c_str());
    }
    return datos;
}

coneccion::provedor *coneccion::get_proveedor()
{
        pro = new provedor();
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery("select * from Proveedor"));
        while (res->next())
        {
            pro->Empresa.push_back(res->getString("Empresa").c_str());
            pro->Nombre.push_back(res->getString("Nombre").c_str());
            pro->Direccion.push_back(res->getString("Direccion").c_str());
            pro->Telefono.push_back(res->getString("Telefono").c_str());
            pro->Region.push_back(res->getString("Region").c_str());
            pro->Pais.push_back(res->getString("Pais").c_str());
            pro->RFC.push_back(res->getString("RFC").c_str());
            pro->Estado.push_back(res->getString("Estado").c_str());
            pro->Correo.push_back(res->getString("Correo").c_str());
        }
        conn->close();
        return pro;
}

coneccion::productos *coneccion::get_productos()
{
    prod = new productos();
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery("select * from Producto"));
    while (res->next())
    {
        prod->SKU.push_back(res->getString("SKU").c_str());
        prod->Nombre.push_back(res->getString("Nombre").c_str());
        prod->Marca.push_back(res->getString("Marca").c_str());
        prod->FechaP.push_back(res->getString("Fecha_proc").c_str());
        prod->FechaC.push_back(res->getString("Fecha_cad").c_str());
        prod->Lote.push_back(res->getString("Numero_lote").c_str());
        prod->Nota.push_back(res->getString("Nota").c_str());
        prod->Piezas.push_back(res->getString("Piezas").c_str());
        prod->Compra.push_back(res->getString("Compra").c_str());
        prod->Venta.push_back(res->getString("Venta").c_str());
        prod->Categoria.push_back(res->getString("Categoria").c_str());
        prod->Subcategoria.push_back(res->getString("Subcategoria").c_str());
    }
    conn->close();
    return prod;
}

void coneccion::set_proveedor(std::string empresa, std::string nombre, std::string direccion, std::string telefono, std::string region, std::string pais, std::string rfc, std::string estado, std::string correo)
{
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into Proveedor values (?,?,?,?,?,?,?,?,?)"));
    stmnt->setString(1, empresa);
    stmnt->setString(2, nombre);
    stmnt->setString(3, direccion);
    stmnt->setBigInt(4, telefono);
    stmnt->setString(5, region);
    stmnt->setString(6, pais);
    stmnt->setString(7, rfc);
    stmnt->setString(8, estado);
    stmnt->setString(9, correo);
    stmnt->executeQuery();
    conn->close();
}

void coneccion::set_producto(std::string sku,std::string nombre,std::string marca,std::string fecha_p,std::string fecha_c,std::string lote,std::string nota,
                    std::string piezas,std::string compra,std::string venta,std::string categoria,std::string subcategoria){
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into Producto values (?,?,?,?,?,?,?,?,?,?,?,?)"));
    stmnt->setBigInt(1,sku);
    stmnt->setString(2,nombre);
    stmnt->setString(3,marca);
    stmnt->setString(4,fecha_p);
    stmnt->setString(5,fecha_c);
    stmnt->setString(6,lote);
    stmnt->setString(7,nota);
    stmnt->setDouble(8,atof(piezas.c_str()));
    stmnt->setDouble(9,atof(compra.c_str()));
    stmnt->setDouble(10,atof(venta.c_str()));
    stmnt->setString(11,categoria);
    stmnt->setString(12,subcategoria);
    stmnt->executeQuery();
    stmnt->close();
}