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
    wizar->constructor->get_widget("btn_user", btn_user);
    wizar->constructor->get_widget("lbl_emp_bien", lbl_emp_bien);
    wizar->constructor->get_widget("lbl_num_bien", lbl_num_bien);
    wizar->constructor->get_widget("lbl_dir_bien", lbl_dir_bien);
    wizar->constructor->get_widget("lbl_rfc_bien", lbl_rfc_bien);
    wizar->constructor->get_widget("btn_aplica", btn_aplica);
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
    ety_user_bien->signal_changed().connect(sigc::mem_fun(*this, &wizard::on_ety_user_bien_changed));
    ety_contrasena1->signal_changed().connect(sigc::mem_fun(*this, &wizard::on_ety_contrasena1_changed));
    ety_contrasena2->signal_changed().connect(sigc::mem_fun(*this, &wizard::on_ety_contrasena2_changed));
    btn_user->signal_clicked().connect(sigc::mem_fun(*this, &wizard::btn_user_clicked));
    ety_emp_bien->signal_changed().connect(sigc::mem_fun(*this, &wizard::on_ety_emp_bien_changed));
    ety_num_bien->signal_changed().connect(sigc::mem_fun(*this, &wizard::on_ety_num_bien_changed));
    ety_dir_bien->signal_changed().connect(sigc::mem_fun(*this, &wizard::on_ety_dir_bien_changed));
    ety_rfc_bien->signal_changed().connect(sigc::mem_fun(*this, &wizard::on_ety_rfc_bien_changed));
    btn_cancelar_stp->signal_clicked().connect(sigc::mem_fun(*this, &wizard::cierra_wizard));
    btn_aplica->signal_clicked().connect(sigc::mem_fun(*this, &wizard::on_btn_aplica_clicked));
}

void wizard::cierra_wizard()
{
    bienvenido->hide();
}
void wizard::on_ety_user_bien_changed()
{
    if (ety_user_bien->get_text().size() > 0)
    {
        ety_contrasena1->set_sensitive(true);
        ety_contrasena2->set_sensitive(true);
    }
    else
    {
        ety_contrasena1->set_sensitive(false);
        ety_contrasena2->set_sensitive(false);
    }
}

void wizard::on_ety_contrasena1_changed()
{
    if (ety_contrasena1->get_text() == ety_contrasena2->get_text() && !ety_contrasena1->get_text().empty() && !ety_contrasena2->get_text().empty() && ety_contrasena1->get_text().size() > 8)
    {
        info_bar_bien->set_reveal_child(false);
        btn_user->set_sensitive(true);
    }
    else
    {
        lbl_info_bien->set_text("Las contraseñas no coinciden y/o debe tener una longitud mayor a 8 caracteres.");
        bar_bien->set_message_type(Gtk::MESSAGE_WARNING);
        info_bar_bien->set_reveal_child(true);
        btn_user->set_sensitive(false);
    }
}

void wizard::on_ety_contrasena2_changed()
{
    on_ety_contrasena1_changed();
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
            bienvenida->configuracion->escribe_configuracion(ety_user_comp->get_text(), ety_server_comp->get_text(), ety_contrasena_comp->get_text());
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
        bienvenida->instala_bd();
        bienvenida->instala_bd_part2();
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

void wizard::btn_user_clicked()
{
    try
    {
        if (bienvenida->comprueba_gerente())
        {
            Gtk::MessageDialog mensaje(*bienvenido, "Ya existe un gerente en la base de datos.", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);
            mensaje.set_secondary_text("¿Desea Añadir Otro?");
            if (mensaje.run() == Gtk::RESPONSE_YES)
            {
                mensaje.close();
                Gtk::MessageDialog mensajea(*bienvenido, "¿Los datos son correctos?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);
                if (mensajea.run() == Gtk::RESPONSE_YES)
                {
                    bienvenida->anade_usuario("Gerente", ety_user_bien->get_text(), ety_contrasena1->get_text());
                    lbl_info_bien->set_text("Usuario Añadido Correctamente");
                    bar_bien->set_message_type(Gtk::MESSAGE_INFO);
                    info_bar_bien->set_reveal_child(true);
                }
            }
        }
        else
        {
            Gtk::MessageDialog mensajeb(*bienvenido, "¿Los datos son correctos?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);
            if (mensajeb.run() == Gtk::RESPONSE_YES)
            {
                bienvenida->anade_usuario("Gerente", ety_user_bien->get_text(), ety_contrasena1->get_text());
                lbl_info_bien->set_text("Usuario Añadido Correctamente");
                bar_bien->set_message_type(Gtk::MESSAGE_INFO);
                info_bar_bien->set_reveal_child(true);
            }
        }
    }
    catch (sql::SQLException &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "SQLState: " << e.getSQLState() << std::endl;
        std::cout << "Error code: " << e.getErrorCode() << std::endl;
        lbl_info_bien->set_text(e.what());
        bar_bien->set_message_type(Gtk::MESSAGE_ERROR);
        info_bar_bien->set_reveal_child(true);
    }
}

void wizard::on_ety_emp_bien_changed()
{
    if (ety_emp_bien->get_text() != "")
    {
        lbl_emp_bien->set_text(ety_emp_bien->get_text());
    }
    else
    {
        lbl_info_bien->set_text("Este campo es obligatorio");
        bar_bien->set_message_type(Gtk::MESSAGE_WARNING);
        info_bar_bien->set_reveal_child(true);
    }
}
void wizard::on_ety_dir_bien_changed()
{
    if (ety_dir_bien->get_text() != "")
    {
        lbl_dir_bien->set_text(ety_dir_bien->get_text());
    }
    else
    {
        lbl_info_bien->set_text("Este campo es obligatorio");
        bar_bien->set_message_type(Gtk::MESSAGE_WARNING);
        info_bar_bien->set_reveal_child(true);
    }
}
void wizard::on_ety_num_bien_changed()
{
    if (ety_num_bien->get_text() != "")
    {
        lbl_num_bien->set_text(ety_num_bien->get_text());
    }
    else
    {
        lbl_info_bien->set_text("Este campo es obligatorio");
        bar_bien->set_message_type(Gtk::MESSAGE_WARNING);
        info_bar_bien->set_reveal_child(true);
    }
}

void wizard::on_ety_rfc_bien_changed()
{
    if (ety_rfc_bien->get_text() != "")
    {
        lbl_rfc_bien->set_text(ety_rfc_bien->get_text());
    }
}

void wizard::on_btn_aplica_clicked()
{
    if (lbl_emp_bien->get_text() != "" && lbl_dir_bien->get_text() != "" && lbl_num_bien->get_text() != "")
    {
        try
        {
            bienvenida->datos_tienda(lbl_emp_bien->get_text(), lbl_num_bien->get_text(), lbl_dir_bien->get_text(), lbl_rfc_bien->get_text());
            lbl_info_bien->set_text("Datos Aplicados Correctamente ya puede cerrar esta ventana.");
            bar_bien->set_message_type(Gtk::MESSAGE_INFO);
            info_bar_bien->set_reveal_child(true);
        }
        catch (sql::SQLException &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
            std::cout << "SQLState: " << e.getSQLState() << std::endl;
            std::cout << "Error code: " << e.getErrorCode() << std::endl;
            lbl_info_bien->set_text(e.what());
            bar_bien->set_message_type(Gtk::MESSAGE_ERROR);
            info_bar_bien->set_reveal_child(true);
        }
    }
    else
    {
        lbl_info_bien->set_text("No se han completado todos los campos");
        bar_bien->set_message_type(Gtk::MESSAGE_WARNING);
        info_bar_bien->set_reveal_child(true);
    }
}