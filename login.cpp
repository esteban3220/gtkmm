#include "login.hpp"
#include "builder.cpp"
#include "wizard.cpp"
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
        if (conn->conecta(ety_usuario->get_text(), ety_contrasena->get_text()))
        {
            Gtk::MessageDialog mensajea(*window_glade, "Simon Si es", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
            mensajea.run();
        }
        else
        {
            Gtk::MessageDialog mensajea(*window_glade, "No krnal: ", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK, true);
            mensajea.run();
        }
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

void Login::comprueba_configuracion(){
    if (!conn->comprueba_configuracion())
    {
        Gtk::MessageDialog mensaje(*window_glade, "No hay archivo de configuracion.", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK, true);
        mensaje.set_secondary_text("Se iniciara el ayudante de configuracion.");
        mensaje.run();
        w1 = new wizard();
        w1->run(); 
    }
}