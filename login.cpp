#include "login.hpp"
#include "builder.cpp"
#include "wizard.cpp"
#include "window_bd.cpp"
Login::Login()
{
    establece_widgets();
    conecta_senales();
    comprueba_configuracion();
}

void Login::show()
{
    window_glade->show_all();
}

void Login::establece_widgets()
{
    login = new builder();
    login->constructor->get_widget("Login_main", window_glade);
    login->constructor->get_widget("ety_contrasena", ety_contrasena);
    login->constructor->get_widget("ety_usuario", ety_usuario);
    login->constructor->get_widget("btn_sesion", btn_sesion);
    login->constructor->get_widget("cb_usuarios", cb_usuarios);
}

void Login::conecta_senales()
{
    window_glade->signal_delete_event().connect(sigc::mem_fun(*this, &Login::cierra_Login));
    btn_sesion->signal_clicked().connect(sigc::mem_fun(*this, &Login::ver_resultado));
}

void Login::ver_resultado()
{
    try
    {
        w_main = new window_bd(conn->conecta(ety_usuario->get_text(), ety_contrasena->get_text())[0], conn->conecta(ety_usuario->get_text(), ety_contrasena->get_text())[1],ety_contrasena->get_text());
        window_glade->hide();
        w_main->show();
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "Error Connecting to MariaDB Platform: " << e.what() << std::endl;
        Gtk::MessageDialog mensaje(*window_glade, "Error Mariadb", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
        mensaje.set_secondary_text(e.what());
        mensaje.set_title("Error");
        mensaje.run();
    }
}

bool Login::cierra_Login(GdkEventAny *event)
{
    Gtk::Main::quit();
    return true;
}

void Login::comprueba_configuracion()
{
    if (!conn->comprueba_configuracion())
    {
        Gtk::MessageDialog mensaje(*window_glade, "Faltal uno o mas componentes del Archivo de Configuracion.", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK, true);
        mensaje.set_secondary_text("Se iniciara el ayudante de configuracion.");
        mensaje.run();
        w1 = new wizard();
        w1->run();
    }else{
        for(auto i : conn->lee_usuarios()){
            cb_usuarios->append(i);
        }
    }
}