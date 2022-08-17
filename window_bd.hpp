#include <gtkmm.h>
#include <vector>

class window_bd
{
private:
    bool cierra_app(GdkEventAny *event);
    coneccion *bd;
    Gtk::Window *Window_BD;
    Gtk::Label *lbl_usuario, *lbl_rol, *lbl_elepro, *lbl_info, *lbl_totalpos, *lbl_elementos_pro, *lbl_tickettotal, *lbl_ticketrecibido,
        *lbl_ticketcambio, *lbl_ventadia, *lbl_clientes_dia, *lbl_ventames, *lbl_ventames_min, *lbl_ventames_max, *lbl_ventaanio, *lbl_ventaanio_min,
        *lbl_ventaanio_max, *lbl_anio_ant, *lbl_user_ad;
    Gtk::Entry *ety_pos_producto, *ety_produ_emp, *ety_producto_pos, *ety_busca_proveedor, *ety_nombreemp, *ety_direccion, *ety_telefono, *ety_region, *ety_pais_emp, *ety_rfc,
        *ety_estado_emp, *ety_correoemp, *ety_busca_producto, *ety_busca_proveedor_producto, *ety_busca_categoria, *ety_busca_subcategoria, *ety_cbarra, *ety_nombrepro,
        *ety_marcapro, *ety_nlote, *ety_cneto, *ety_cat, *ety_subcat, *ety_busquedatick, *ety_filtraprov, *ety_filtroprod, *ety_cantidadtick;
    Gtk::SpinButton *ety_recibido, *spin_piezas, *spin_compra, *spin_venta, *ety_cantidadtick2;
    Gtk::ComboBoxText *cb_busca_estado, *cb_pais_emp, *cb_estado_emp, *cb_productos_proveedor, *cb_bs_cat, *cb_bs_subcat, *cb_marcapro, *cb_dia_pro, *cb_mes_pro, *cb_anio_pro,
        *cb_dia_propro, *cb_mes_propro, *cb_anio_propro, *cb_cat, *cb_subcat, *cb_dia_propro4, *cb_mes_propro4, *cb_anio_propro4,
        *cb_filtraprov, *cb_filtroprod, *cb_filtraudticket;
    Gtk::Button *btn_vp, *btn_servicios, *btn_venta, *btn_proveedorpdf, *inserta_datos_empresa, *cancela_and_factura3, *actualiza_datos_empresa,
        *btn_borrar_emp, *btn_exportaproductopdf, *btn_inventario, *inserta_datos_productos, *cancela_and_factura2, *btn_act, *btn_borrar_pro, *btn_copia_producto,
        *btn_resetfecha, *btn_eliminaticket, *btn_pagar, *btn_cambiar_contrasena, *btn_4cb, *btn_8cb, *btn_13cb;
    Gtk::ToggleButton *btn_buscar_pos, *btn_edit_proveedor, *btn_edit_productos;
    Gtk::Popover *pop_busqueda_pos, *pop_generar_sku;
    Gtk::Stack *stack_menu_pos, *stack_pos, *stack_header, *stack_actualiza, *stack_actualiza2, *stack_otros, *stack_pdf, *stack_pop_producto, *stack_sku;
    Gtk::Revealer *reveal_proveedor, *reveal_productos, *reveal_consulta, *info_bar;
    Gtk::CheckButton *mark_bajostck, *mark_impresion;
    Gtk::TreeView *view, *treeview_pos, *view2, *view3, *view_venta, *view4, *view6, *view5, *view_inventario_alt, *view_descinve, *view_corte;
    Gtk::InfoBar *bar;
    Glib::RefPtr<Gtk::ListStore> ListProveedor;
    Glib::RefPtr<Gtk::ListStore> ListProductos;
    Gtk::TreeModel::Row row;
    void establece_widgets();
    void llenar_proveedor();
    void llenar_productos();
    void set_proveedor();
    void set_productos();
    void conecta_senales();
    void on_btn_edit_proveedor_toggled();
    void reveal_producto();
    void cierra_info(int valor);
    void vacia_llenamarca();
    void vacia_proveedor();
    void add_proveedor(std::string empresa, std::string nombre, std::string direccion, std::string telefono, std::string region, std::string pais, std::string rfc, std::string estado, std::string correo);
    class ModelProveedor : public Gtk::TreeModel::ColumnRecord
    {
    public:
        ModelProveedor()
        {
            add(Empresa);
            add(Nombre);
            add(Direccion);
            add(Telefono);
            add(Region);
            add(Pais);
            add(RFC);
            add(Estado);
            add(Correo);
        }

        Gtk::TreeModelColumn<Glib::ustring> Empresa;
        Gtk::TreeModelColumn<Glib::ustring> Nombre;
        Gtk::TreeModelColumn<Glib::ustring> Direccion;
        Gtk::TreeModelColumn<Glib::ustring> Telefono;
        Gtk::TreeModelColumn<Glib::ustring> Region;
        Gtk::TreeModelColumn<Glib::ustring> Pais;
        Gtk::TreeModelColumn<Glib::ustring> RFC;
        Gtk::TreeModelColumn<Glib::ustring> Estado;
        Gtk::TreeModelColumn<Glib::ustring> Correo;
    }columns_proveedor;

    class ModelProductos : public Gtk::TreeModel::ColumnRecord
    {
    public:
        ModelProductos()
        {
            add(SKU);
            add(Nombre);
            add(Marca);
            add(FechaP);
            add(FechaC);
            add(Lote);
            add(Nota);
            add(Piezas);
            add(Compra);
            add(Venta);
            add(Categoria);
            add(Subcategoria);
        }

        Gtk::TreeModelColumn<Glib::ustring> SKU;
        Gtk::TreeModelColumn<Glib::ustring> Nombre;
        Gtk::TreeModelColumn<Glib::ustring> Marca;
        Gtk::TreeModelColumn<Glib::ustring> FechaP;
        Gtk::TreeModelColumn<Glib::ustring> FechaC;
        Gtk::TreeModelColumn<Glib::ustring> Lote;
        Gtk::TreeModelColumn<Glib::ustring> Nota;
        Gtk::TreeModelColumn<Glib::ustring> Piezas;
        Gtk::TreeModelColumn<Glib::ustring> Compra;
        Gtk::TreeModelColumn<Glib::ustring> Venta;
        Gtk::TreeModelColumn<Glib::ustring> Categoria;
        Gtk::TreeModelColumn<Glib::ustring> Subcategoria;
    }columns_productos;

public:
    window_bd(std::string usuario, std::string rol ,std::string password);
    ~window_bd();
    void show();
} * w_main;
