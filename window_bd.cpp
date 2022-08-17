#include "window_bd.hpp"
#include "builder.cpp"

window_bd::window_bd(std::string usuario, std::string rol, std::string passsword)
{
    establece_widgets();
    conecta_senales();
    lbl_user_ad->set_text(usuario);
    lbl_rol->set_text(rol);
    lbl_usuario->set_text(usuario);
    bd = new coneccion(usuario, passsword);
    for (size_t i = 1960; i < 2030; i++)
    {
        cb_anio_pro->append(std::to_string(i));
        cb_anio_propro->append(std::to_string(i));
    }
    for (std::string marca : bd->lee_marca())
    {
        cb_marcapro->append(marca);
    }
    llenar_proveedor();
    llenar_productos();
}

void window_bd::establece_widgets()
{
    _window_bd = new builder();
    _window_bd->constructor->get_widget("Window_BD", Window_BD);
    _window_bd->constructor->get_widget("lbl_usuario", lbl_usuario);
    _window_bd->constructor->get_widget("lbl_rol", lbl_rol);
    _window_bd->constructor->get_widget("lbl_elepro", lbl_elepro);
    _window_bd->constructor->get_widget("lbl_info", lbl_info);
    _window_bd->constructor->get_widget("lbl_totalpos", lbl_totalpos);
    _window_bd->constructor->get_widget("lbl_elementos_pro", lbl_elementos_pro);
    _window_bd->constructor->get_widget("lbl_tickettotal", lbl_tickettotal);
    _window_bd->constructor->get_widget("lbl_ticketrecibido", lbl_ticketrecibido);
    _window_bd->constructor->get_widget("lbl_ticketcambio", lbl_ticketcambio);
    _window_bd->constructor->get_widget("lbl_ventadia", lbl_ventadia);
    _window_bd->constructor->get_widget("lbl_clientes_dia", lbl_clientes_dia);
    _window_bd->constructor->get_widget("lbl_ventames", lbl_ventames);
    _window_bd->constructor->get_widget("lbl_ventames_min", lbl_ventames_min);
    _window_bd->constructor->get_widget("lbl_ventames_max", lbl_ventames_max);
    _window_bd->constructor->get_widget("lbl_ventaanio", lbl_ventaanio);
    _window_bd->constructor->get_widget("lbl_ventaanio_min", lbl_ventaanio_min);
    _window_bd->constructor->get_widget("lbl_ventaanio_max", lbl_ventaanio_max);
    _window_bd->constructor->get_widget("lbl_anio_ant", lbl_anio_ant);
    _window_bd->constructor->get_widget("lbl_user_ad", lbl_user_ad);
    _window_bd->constructor->get_widget("ety_pos_producto", ety_pos_producto);
    _window_bd->constructor->get_widget("ety_producto_pos", ety_producto_pos);
    _window_bd->constructor->get_widget("ety_busca_proveedor", ety_busca_proveedor);
    _window_bd->constructor->get_widget("ety_produ_emp", ety_produ_emp);
    _window_bd->constructor->get_widget("ety_nombreemp", ety_nombreemp);
    _window_bd->constructor->get_widget("ety_nombrepro", ety_nombrepro);
    _window_bd->constructor->get_widget("ety_direccion", ety_direccion);
    _window_bd->constructor->get_widget("ety_telefono", ety_telefono);
    _window_bd->constructor->get_widget("ety_pais_emp", ety_pais_emp);
    _window_bd->constructor->get_widget("ety_rfc", ety_rfc);
    _window_bd->constructor->get_widget("ety_region", ety_region);
    _window_bd->constructor->get_widget("ety_estado_emp", ety_estado_emp);
    _window_bd->constructor->get_widget("ety_correoemp", ety_correoemp);
    _window_bd->constructor->get_widget("ety_busca_producto", ety_busca_producto);
    _window_bd->constructor->get_widget("ety_busca_proveedor_producto", ety_busca_proveedor_producto);
    _window_bd->constructor->get_widget("ety_busca_categoria", ety_busca_categoria);
    _window_bd->constructor->get_widget("ety_busca_subcategoria", ety_busca_subcategoria);
    _window_bd->constructor->get_widget("ety_cbarra", ety_cbarra);
    _window_bd->constructor->get_widget("ety_nombrepro", ety_nombrepro);
    _window_bd->constructor->get_widget("ety_marcapro", ety_marcapro);
    _window_bd->constructor->get_widget("ety_nlote", ety_nlote);
    _window_bd->constructor->get_widget("ety_cneto", ety_cneto);
    _window_bd->constructor->get_widget("ety_cat", ety_cat);
    _window_bd->constructor->get_widget("ety_subcat", ety_subcat);
    _window_bd->constructor->get_widget("ety_busquedatick", ety_busquedatick);
    _window_bd->constructor->get_widget("ety_filtraprov", ety_filtraprov);
    _window_bd->constructor->get_widget("ety_filtroprod", ety_filtroprod);
    _window_bd->constructor->get_widget("ety_cantidadtick", ety_cantidadtick);
    _window_bd->constructor->get_widget("ety_recibido", ety_recibido);
    _window_bd->constructor->get_widget("spin_piezas", spin_piezas);
    _window_bd->constructor->get_widget("spin_compra", spin_compra);
    _window_bd->constructor->get_widget("spin_venta", spin_venta);
    _window_bd->constructor->get_widget("ety_cantidadtick2", ety_cantidadtick2);
    _window_bd->constructor->get_widget("cb_busca_estado", cb_busca_estado);
    _window_bd->constructor->get_widget("cb_pais_emp", cb_pais_emp);
    _window_bd->constructor->get_widget("cb_estado_emp", cb_estado_emp);
    _window_bd->constructor->get_widget("cb_productos_proveedor", cb_productos_proveedor);
    _window_bd->constructor->get_widget("cb_bs_cat", cb_bs_cat);
    _window_bd->constructor->get_widget("cb_bs_subcat", cb_bs_subcat);
    _window_bd->constructor->get_widget("cb_marcapro", cb_marcapro);
    _window_bd->constructor->get_widget("cb_dia_pro", cb_dia_pro);
    _window_bd->constructor->get_widget("cb_mes_pro", cb_mes_pro);
    _window_bd->constructor->get_widget("cb_anio_pro", cb_anio_pro);
    _window_bd->constructor->get_widget("cb_dia_propro", cb_dia_propro);
    _window_bd->constructor->get_widget("cb_mes_propro", cb_mes_propro);
    _window_bd->constructor->get_widget("cb_anio_propro", cb_anio_propro);
    _window_bd->constructor->get_widget("cb_dia_propro4", cb_dia_propro4);
    _window_bd->constructor->get_widget("cb_mes_propro4", cb_mes_propro4);
    _window_bd->constructor->get_widget("cb_anio_propro4", cb_anio_propro4);
    _window_bd->constructor->get_widget("cb_filtraprov", cb_filtraprov);
    _window_bd->constructor->get_widget("cb_filtraudticket", cb_filtraudticket);
    _window_bd->constructor->get_widget("cb_filtroprod", cb_filtroprod);
    _window_bd->constructor->get_widget("btn_vp", btn_vp);
    _window_bd->constructor->get_widget("btn_servicios", btn_servicios);
    _window_bd->constructor->get_widget("btn_venta", btn_venta);
    _window_bd->constructor->get_widget("btn_proveedorpdf", btn_proveedorpdf);
    _window_bd->constructor->get_widget("inserta_datos_empresa", inserta_datos_empresa);
    _window_bd->constructor->get_widget("cancela_and_factura3", cancela_and_factura3);
    _window_bd->constructor->get_widget("actualiza_datos_empresa", actualiza_datos_empresa);
    _window_bd->constructor->get_widget("btn_borrar_emp", btn_borrar_emp);
    _window_bd->constructor->get_widget("btn_borrar_pro", btn_borrar_pro);
    _window_bd->constructor->get_widget("btn_exportaproductopdf", btn_exportaproductopdf);
    _window_bd->constructor->get_widget("btn_inventario", btn_inventario);
    _window_bd->constructor->get_widget("inserta_datos_productos", inserta_datos_productos);
    _window_bd->constructor->get_widget("cancela_and_factura2", cancela_and_factura2);
    _window_bd->constructor->get_widget("btn_act", btn_act);
    _window_bd->constructor->get_widget("btn_borrar_pro", btn_borrar_pro);
    _window_bd->constructor->get_widget("btn_copia_producto", btn_copia_producto);
    _window_bd->constructor->get_widget("btn_resetfecha", btn_resetfecha);
    _window_bd->constructor->get_widget("btn_eliminaticket", btn_eliminaticket);
    _window_bd->constructor->get_widget("btn_pagar", btn_pagar);
    _window_bd->constructor->get_widget("btn_cambiar_contrasena", btn_cambiar_contrasena);
    _window_bd->constructor->get_widget("btn_4cb", btn_4cb);
    _window_bd->constructor->get_widget("btn_8cb", btn_8cb);
    _window_bd->constructor->get_widget("btn_13cb", btn_13cb);
    _window_bd->constructor->get_widget("btn_buscar_pos", btn_buscar_pos);
    _window_bd->constructor->get_widget("btn_edit_proveedor", btn_edit_proveedor);
    _window_bd->constructor->get_widget("btn_edit_productos", btn_edit_productos);
    _window_bd->constructor->get_widget("pop_busqueda_pos", pop_busqueda_pos);
    _window_bd->constructor->get_widget("pop_generar_sku", pop_generar_sku);
    _window_bd->constructor->get_widget("stack_menu_pos", stack_menu_pos);
    _window_bd->constructor->get_widget("stack_pos", stack_pos);
    _window_bd->constructor->get_widget("stack_header", stack_header);
    _window_bd->constructor->get_widget("stack_actualiza", stack_actualiza);
    _window_bd->constructor->get_widget("stack_actualiza2", stack_actualiza2);
    _window_bd->constructor->get_widget("stack_otros", stack_otros);
    _window_bd->constructor->get_widget("stack_pdf", stack_pdf);
    _window_bd->constructor->get_widget("stack_pop_producto", stack_pop_producto);
    _window_bd->constructor->get_widget("stack_sku", stack_sku);
    _window_bd->constructor->get_widget("reveal_proveedor", reveal_proveedor);
    _window_bd->constructor->get_widget("reveal_productos", reveal_productos);
    _window_bd->constructor->get_widget("reveal_consulta", reveal_consulta);
    _window_bd->constructor->get_widget("info_bar", info_bar);
    _window_bd->constructor->get_widget("mark_bajostck", mark_bajostck);
    _window_bd->constructor->get_widget("mark_impresion", mark_impresion);
    _window_bd->constructor->get_widget("view", view);
    _window_bd->constructor->get_widget("view2", view2);
    _window_bd->constructor->get_widget("view3", view3);
    _window_bd->constructor->get_widget("view4", view4);
    _window_bd->constructor->get_widget("view5", view5);
    _window_bd->constructor->get_widget("view6", view6);
    _window_bd->constructor->get_widget("treeview_pos", treeview_pos);
    _window_bd->constructor->get_widget("view_venta", view_venta);
    _window_bd->constructor->get_widget("view_inventario_alt", view_inventario_alt);
    _window_bd->constructor->get_widget("view_descinve", view_descinve);
    _window_bd->constructor->get_widget("view_corte", view_corte);
    _window_bd->constructor->get_widget("bar", bar);
}

void window_bd::conecta_senales()
{
    Window_BD->signal_delete_event().connect(sigc::mem_fun(*this, &window_bd::cierra_app));
    btn_edit_proveedor->signal_toggled().connect(sigc::mem_fun(*this, &window_bd::on_btn_edit_proveedor_toggled));
    btn_edit_productos->signal_toggled().connect(sigc::mem_fun(*this, &window_bd::reveal_producto));
    inserta_datos_empresa->signal_clicked().connect(sigc::mem_fun(*this, &window_bd::set_proveedor));
    inserta_datos_productos->signal_clicked().connect(sigc::mem_fun(*this, &window_bd::set_productos));
    bar->signal_response().connect(sigc::mem_fun(*this, &window_bd::cierra_info));
}

void window_bd::cierra_info(int)
{
    info_bar->set_reveal_child(false);
}

void window_bd::show()
{
    Window_BD->show();
}

bool window_bd::cierra_app(GdkEventAny *event)
{
    Gtk::Main::quit();
    return true;
}
void window_bd::llenar_proveedor()
{
    ListProveedor = Gtk::ListStore::create(columns_proveedor);
    view->set_model(ListProveedor);
    view->append_column("Empresa", columns_proveedor.Empresa);
    view->append_column("Nombre", columns_proveedor.Nombre);
    view->append_column("Direccion", columns_proveedor.Direccion);
    view->append_column("Telefono", columns_proveedor.Telefono);
    view->append_column("Region", columns_proveedor.Region);
    view->append_column("Pais", columns_proveedor.Pais);
    view->append_column("RFC", columns_proveedor.RFC);
    view->append_column("Estado", columns_proveedor.Estado);
    view->append_column("Correo", columns_proveedor.Correo);

    for (size_t i = 0; i < bd->get_proveedor()->Empresa.size(); i++)
    {
        row = *(ListProveedor->append());
        row[columns_proveedor.Empresa] = bd->get_proveedor()->Empresa[i];
        row[columns_proveedor.Nombre] = bd->get_proveedor()->Nombre[i];
        row[columns_proveedor.RFC] = bd->get_proveedor()->RFC[i];
        row[columns_proveedor.Direccion] = bd->get_proveedor()->Direccion[i];
        row[columns_proveedor.Telefono] = bd->get_proveedor()->Telefono[i];
        row[columns_proveedor.Correo] = bd->get_proveedor()->Correo[i];
        row[columns_proveedor.Pais] = bd->get_proveedor()->Pais[i];
        row[columns_proveedor.Estado] = bd->get_proveedor()->Estado[i];
        row[columns_proveedor.Region] = bd->get_proveedor()->Region[i];
    }
}

void window_bd::llenar_productos()
{
    ListProductos = Gtk::ListStore::create(columns_productos);
    view3->set_model(ListProductos);
    view3->append_column("SKU", columns_productos.SKU);
    view3->append_column("Nombre", columns_productos.Nombre);
    view3->append_column("Marca", columns_productos.Marca);
    view3->append_column("Fecha Produccion", columns_productos.FechaP);
    view3->append_column("Fecha Caducidad", columns_productos.FechaC);
    view3->append_column("Numero de Lote", columns_productos.Lote);
    view3->append_column("Nota", columns_productos.Nota);
    view3->append_column("Cantidad de Piezas", columns_productos.Piezas);
    view3->append_column("Compra", columns_productos.Compra);
    view3->append_column("Precio de Venta U.", columns_productos.Venta);
    view3->append_column("Categoria", columns_productos.Categoria);
    view3->append_column("Subcategoria", columns_productos.Subcategoria);
    for (size_t i = 0; i < bd->get_productos()->SKU.size(); i++)
    {
        row = *(ListProductos->append());
        row[columns_productos.SKU] = bd->get_productos()->SKU[i];
        row[columns_productos.Nombre] = bd->get_productos()->Nombre[i];
        row[columns_productos.Marca] = bd->get_productos()->Marca[i];
        row[columns_productos.FechaP] = bd->get_productos()->FechaP[i];
        row[columns_productos.FechaC] = bd->get_productos()->FechaC[i];
        row[columns_productos.Lote] = bd->get_productos()->Lote[i];
        row[columns_productos.Nota] = bd->get_productos()->Nota[i];
        row[columns_productos.Piezas] = bd->get_productos()->Piezas[i];
        row[columns_productos.Compra] = bd->get_productos()->Compra[i];
        row[columns_productos.Venta] = bd->get_productos()->Venta[i];
        row[columns_productos.Categoria] = bd->get_productos()->Categoria[i];
        row[columns_productos.Subcategoria] = bd->get_productos()->Subcategoria[i];
    }
}

void window_bd::on_btn_edit_proveedor_toggled()
{
    if (btn_edit_proveedor->get_active())
    {
        reveal_proveedor->set_reveal_child(true);
    }
    else
    {
        reveal_proveedor->set_reveal_child(false);
    }
}

void window_bd::reveal_producto()
{
    if (btn_edit_productos->get_active())
    {
        reveal_productos->set_reveal_child(true);
    }
    else
    {
        reveal_productos->set_reveal_child(false);
    }
}

void window_bd::vacia_llenamarca()
{
    cb_marcapro->remove_all();
    for (std::string marca : bd->lee_marca())
    {
        cb_marcapro->append(marca);
    }
}

void window_bd::vacia_proveedor()
{
    ety_produ_emp->set_text("");
    ety_nombreemp->set_text("");
    ety_direccion->set_text("");
    ety_telefono->set_text("");
    ety_region->set_text("");
    ety_pais_emp->set_text("");
    ety_rfc->set_text("");
    ety_estado_emp->set_text("");
    ety_correoemp->set_text("");
}

void window_bd::add_proveedor(std::string empresa, std::string nombre, std::string direccion, std::string telefono, std::string region, std::string pais, std::string rfc, std::string estado, std::string correo)
{
    row = *(ListProveedor->append());
    row[columns_proveedor.Empresa] = empresa;
    row[columns_proveedor.Nombre] = nombre;
    row[columns_proveedor.Direccion] = direccion;
    row[columns_proveedor.Telefono] = telefono;
    row[columns_proveedor.Region] = region;
    row[columns_proveedor.Pais] = pais;
    row[columns_proveedor.RFC] = rfc;
    row[columns_proveedor.Estado] = estado;
    row[columns_proveedor.Correo] = correo;
}

void window_bd::set_proveedor()
{
    info_bar->set_reveal_child(false);
    if (!ety_produ_emp->get_text().empty() && !ety_nombreemp->get_text().empty() && !ety_telefono->get_text().empty())
    {
        try
        {
            bd->set_proveedor(ety_produ_emp->get_text(), ety_nombreemp->get_text(), ety_direccion->get_text(), ety_telefono->get_text(), ety_region->get_text(), ety_pais_emp->get_text(), ety_rfc->get_text(), ety_estado_emp->get_text(), ety_correoemp->get_text());
            add_proveedor(ety_produ_emp->get_text(), ety_nombreemp->get_text(), ety_direccion->get_text(), ety_telefono->get_text(), ety_region->get_text(), ety_pais_emp->get_text(), ety_rfc->get_text(), ety_estado_emp->get_text(), ety_correoemp->get_text());
            vacia_proveedor();
            lbl_info->set_text("Proveedor agregado");
            bar->set_message_type(Gtk::MESSAGE_INFO);
            info_bar->set_reveal_child(true);
            vacia_llenamarca();
        }
        catch (sql::SQLException &e)
        {
            lbl_info->set_text(e.what());
            std::cerr << "ERROR: " << e.what();
            bar->set_message_type(Gtk::MESSAGE_ERROR);
            info_bar->set_reveal_child(true);
        }
    }
    else
    {
        lbl_info->set_text("Uno o mas campos estan vacios");
        bar->set_message_type(Gtk::MESSAGE_WARNING);
        info_bar->set_reveal_child(true);
    }
}

void window_bd::set_productos()
{
    info_bar->set_reveal_child(false);
    if (ety_cbarra->get_text().empty() && ety_nombrepro->get_text().empty() && ety_marcapro->get_text().empty())
    {
        lbl_info->set_text("Uno o mas campos estan vacios");
        bar->set_message_type(Gtk::MESSAGE_WARNING);
        info_bar->set_reveal_child(true);
    }
    else
    {
        try
        {
            std::string fecha_p, fecha_c;
            fecha_p = cb_anio_pro->get_active_text() + "-" + cb_mes_pro->get_active_text() + "-" + cb_dia_pro->get_active_text();
            fecha_c = cb_dia_propro->get_active_text() + "-" + cb_mes_propro->get_active_text() + "-" + cb_dia_propro->get_active_text();
            bd->set_producto(ety_cbarra->get_text(), ety_nombrepro->get_text(), ety_marcapro->get_text(), fecha_p, fecha_c, ety_nlote->get_text(), ety_cneto->get_text(), spin_piezas->get_text(), spin_compra->get_text(), spin_venta->get_text(), ety_cat->get_text(), ety_subcat->get_text());
            lbl_info->set_text("Proveedor agregado");
            bar->set_message_type(Gtk::MESSAGE_INFO);
            info_bar->set_reveal_child(true);
            ety_cbarra->set_text("");
            ety_nombrepro->set_text("");
            ety_marcapro->set_text("");
            ety_cneto->set_text("");
            ety_nlote->set_text("");
            spin_piezas->set_text("");
            spin_compra->set_text("");
            spin_venta->set_text("");
            ety_cat->set_text("");
            ety_subcat->set_text("");
        }
        catch (sql::SQLException &e)
        {
            lbl_info->set_text(e.what());
            std::cerr << "ERROR: " << e.what();
            bar->set_message_type(Gtk::MESSAGE_ERROR);
            info_bar->set_reveal_child(true);
        }
    }
}