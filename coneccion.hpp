#pragma once

#include <mariadb/conncpp.hpp>
#include "leer_config.cpp"
#include <vector>
class coneccion
{

private:
    sql::Driver *driver;
    sql::SQLString url;
    sql::Properties properties;
public:
    coneccion();
    coneccion(std::string usuario, std::string contrasena);
    ~coneccion();
    class provedor
    {
    public:
        provedor(){

        }
        ~provedor();
        std::vector<std::string> Empresa;
        std::vector<std::string> Nombre;
        std::vector<std::string> Direccion;
        std::vector<std::string> Telefono;
        std::vector<std::string> Region;
        std::vector<std::string> Pais;
        std::vector<std::string> RFC;
        std::vector<std::string> Estado;
        std::vector<std::string> Correo;
    } * pro;
    class productos
    {
    public:
        productos(){

        }
        ~productos();
        std::vector<std::string> SKU;
        std::vector<std::string> Nombre;
        std::vector<std::string> Marca;
        std::vector<std::string> FechaP;
        std::vector<std::string> FechaC;
        std::vector<std::string> Lote;
        std::vector<std::string> Nota;
        std::vector<std::string> Piezas;
        std::vector<std::string> Compra;
        std::vector<std::string> Venta;
        std::vector<std::string> Categoria;
        std::vector<std::string> Subcategoria;
    } * prod;
    config *configuracion = new config();
    std::vector<std::string> conecta(std::string user, std::string password);
    bool comprueba_configuracion();
    bool comprueba_configuracion_bienvenida(std::string user, std::string password, std::string server);
    void instala_bd();
    void instala_bd_part2();
    bool comprueba_gerente();
    void anade_usuario(std::string rol, std::string nombre, std::string password);
    void datos_tienda(std::string nombre, std::string numero, std::string direccion, std::string rfc);
    void set_proveedor(std::string empresa, std::string nombre, std::string direccion, std::string telefono, std::string region, std::string pais, std::string rfc, std::string estado, std::string correo);
    void set_producto(std::string sku,std::string nombre,std::string marca,std::string fecha_p,std::string fecha_c,std::string lote,std::string nota,std::string piezas,std::string compra,std::string venta,std::string categoria,std::string subcategoria);
    std::vector<std::string> lee_usuarios();
    std::vector<std::string> lee_marca();
    provedor *get_proveedor();
    productos *get_productos();
} * hola;