#include <gtkmm.h>

class Login
{
private:
    Gtk::Window *window_glade;
    Gtk::ComboBox *cb_usuarios;
    Gtk::Entry *ety_usuario;
    Gtk::Entry *ety_contrasena;
    Gtk::Button *btn_sesion;
public:
    Login();
    ~Login();
    void show();
protected:
    bool cierra_Login(GdkEventAny* event);
    void conecta_senales();
    void establece_widgets();
    void ver_resultado();
}*v1;