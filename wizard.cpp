#include "wizard.hpp"
#include "builder.cpp"

wizard::wizard() : m_bActivityMode(false)
{
    establece_widgets();
    conecta_senales();
}

wizard::~wizard()
{
}

void wizard::establece_widgets()
{
    wizar = new builder();
    wizar->constructor->get_widget("bienvenido", bienvenido);
    wizar->constructor->get_widget("ety_user_comp", ety_user_comp);
    wizar->constructor->get_widget("ety_contrasena_comp", ety_contrasena_comp);
    wizar->constructor->get_widget("ety_server_comp", ety_server_comp);
    wizar->constructor->get_widget("ety_user_bien", ety_user_bien);
    wizar->constructor->get_widget("ety_contrasena1", ety_contrasena1);
    wizar->constructor->get_widget("ety_contrasena2", ety_contrasena2);
    wizar->constructor->get_widget("ety_emp_bien", ety_emp_bien);
    wizar->constructor->get_widget("ety_num_bien", ety_num_bien);
    wizar->constructor->get_widget("ety_dir_bien", ety_dir_bien);
    wizar->constructor->get_widget("ety_rfc_bien", ety_rfc_bien);
    wizar->constructor->get_widget("btn_comprobar", btn_comprobar);
    wizar->constructor->get_widget("btn_instalar", btn_instalar);
    wizar->constructor->get_widget("pag_sig", pag_sig);
    wizar->constructor->get_widget("pag_atras", pag_atras);
    wizar->constructor->get_widget("btn_cancelar_stp", btn_cancelar_stp);
    wizar->constructor->get_widget("file", file);
    wizar->constructor->get_widget("image", image);
    wizar->constructor->get_widget("pila_stp", pila_stp);
    wizar->constructor->get_widget("pasos", pasos);
    wizar->constructor->get_widget("pag_bienvenido", pag_bienvenido);
    wizar->constructor->get_widget("pag_conexion", pag_conexion);
    wizar->constructor->get_widget("pag_usuarios", pag_usuarios);
    wizar->constructor->get_widget("pag_comp", pag_comp);
    wizar->constructor->get_widget("pag_sumario", pag_sumario);
    wizar->constructor->get_widget("info_bar_bien", info_bar_bien);
    wizar->constructor->get_widget("bar_bien", bar_bien);
    wizar->constructor->get_widget("lbl_info_bien", lbl_info_bien);
    wizar->constructor->get_widget("progrees_bd_container", progrees_bd_container);
    wizar->constructor->get_widget("progrees_bd", progrees_bd);
}

void wizard::run()
{
    bienvenido->show_all();
}

void wizard::siguiente()
{
    if (pasos->get_visible_child() == pag_bienvenido)
    {
        pasos->set_visible_child(*pag_conexion);
        pag_atras->set_sensitive(true);
    }
    else if (pasos->get_visible_child() == pag_conexion)
    {
        pasos->set_visible_child(*pag_usuarios);
        info_bar_bien->set_reveal_child(false);
    }
    else if (pasos->get_visible_child() == pag_usuarios)
    {
        pasos->set_visible_child(*pag_comp);
        info_bar_bien->set_reveal_child(false);
    }
    else if (pasos->get_visible_child() == pag_comp)
    {
        pasos->set_visible_child(*pag_sumario);
        pag_sig->set_sensitive(false);
        info_bar_bien->set_reveal_child(false);
    }
}

void wizard::atras()
{
    if (pasos->get_visible_child() == pag_sumario)
    {
        pasos->set_visible_child(*pag_comp);
        pag_sig->set_sensitive(true);
        info_bar_bien->set_reveal_child(false);
    }
    else if (pasos->get_visible_child() == pag_comp)
    {
        pasos->set_visible_child(*pag_usuarios);
        info_bar_bien->set_reveal_child(false);
    }
    else if (pasos->get_visible_child() == pag_usuarios)
    {
        pasos->set_visible_child(*pag_conexion);
        info_bar_bien->set_reveal_child(false);
    }
    else if (pasos->get_visible_child() == pag_conexion)
    {
        pasos->set_visible_child(*pag_bienvenido);
        pag_sig->set_sensitive(true);
        pag_atras->set_sensitive(false);
    }
}

void wizard::conecta_senales()
{
    pag_sig->signal_clicked().connect(sigc::mem_fun(*this, &wizard::siguiente));
    pag_atras->signal_clicked().connect(sigc::mem_fun(*this, &wizard::atras));
    btn_comprobar->signal_clicked().connect(sigc::mem_fun(*this, &wizard::comprobar));
    btn_instalar->signal_clicked().connect(sigc::mem_fun(*this, &wizard::instalar_bd));
    bar_bien->signal_response().connect(sigc::mem_fun(*this, &wizard::cerrar_info_bar));
    m_connection_timeout = Glib::signal_timeout().connect(sigc::mem_fun(*this, &wizard::on_timeout), 50);
}

void wizard::instalar_bd()
{
    Gtk::MessageDialog mensaje(*bienvenido, "Si existe la base de datos. Esta sera reescrita", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL, true);
    mensaje.set_secondary_text("¿Desea Continuar?");
    progrees_bd_container->set_reveal_child(false);
    if (mensaje.run() == Gtk::RESPONSE_OK)
    {
        instalar_bd_ok();
    }
}

void wizard::comprobar()
{
    if (ety_user_comp->get_text() != "" || ety_contrasena_comp->get_text() != "" || ety_server_comp->get_text() != "")
    {
        try
        {
            info_bar_bien->set_reveal_child(false);
            bienvenida->comprueba_configuracion_bienvenida(ety_user_comp->get_text(), ety_contrasena_comp->get_text(), ety_server_comp->get_text());
            lbl_info_bien->set_text("Conexion Exitosa. Si aun no esta instalado, presione el boton \"Instalar Tablas\"");
            bar_bien->set_message_type(Gtk::MESSAGE_INFO);
            info_bar_bien->set_reveal_child(true);
            btn_instalar->set_sensitive(true);
        }
        catch (sql::SQLException &e)
        {
            info_bar_bien->set_reveal_child(false);
            std::cout << "Error: " << e.what() << std::endl;
            std::cout << "SQLState: " << e.getSQLState() << std::endl;
            std::cout << "Error code: " << e.getErrorCode() << std::endl;
            lbl_info_bien->set_text(e.what());
            bar_bien->set_message_type(Gtk::MESSAGE_ERROR);
            info_bar_bien->set_reveal_child(true);
            btn_instalar->set_sensitive(false);
        }
    }
    else
    {
        lbl_info_bien->set_text("Todos los campos son obligatorios");
        bar_bien->set_message_type(Gtk::MESSAGE_WARNING);
        info_bar_bien->set_reveal_child(true);
    }
}

void wizard::cerrar_info_bar(int)
{
    info_bar_bien->set_reveal_child(false);
}

void wizard::instalar_bd_ok()
{
    progrees_bd_container->set_reveal_child(true);
    try
    {
        m_bActivityMode = false;
        bienvenida->instala_bd(ety_user_bien->get_text(), ety_contrasena_comp->get_text(), ety_server_comp->get_text());
        bienvenida->instala_bd_part2(ety_user_bien->get_text(), ety_contrasena_comp->get_text(), ety_server_comp->get_text());
        lbl_info_bien->set_text("Base de datos instalada correctamente");
        bar_bien->set_message_type(Gtk::MESSAGE_INFO);
        info_bar_bien->set_reveal_child(true);
        btn_instalar->set_sensitive(false);
        progrees_bd->set_fraction(1.0);
    }
    catch (sql::SQLException &e)
    {
        m_bActivityMode = true;
        info_bar_bien->set_reveal_child(false);
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "SQLState: " << e.getSQLState() << std::endl;
        std::cout << "Error code: " << e.getErrorCode() << std::endl;
        lbl_info_bien->set_text(e.what());
        bar_bien->set_message_type(Gtk::MESSAGE_ERROR);
        info_bar_bien->set_reveal_child(true);
        btn_instalar->set_sensitive(false);
        progrees_bd->set_fraction(0.85);
    }
}

bool wizard::on_timeout()
{
    double new_val;
    if (m_bActivityMode)
        progrees_bd->pulse();
    else
    {
        new_val = progrees_bd->get_fraction() + 0.1;

        if (new_val > 1.0)
            new_val = 0.0;

        // Set the new value:
        progrees_bd->set_fraction(new_val);
    }
    return new_val > 0.99 ? false : true;
}