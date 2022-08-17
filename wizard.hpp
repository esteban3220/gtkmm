#include <gtkmm.h>
#include "coneccion.hpp"

class wizard
{
private:
    Gtk::Window *bienvenido;
    Gtk::Entry *ety_user_comp;
    Gtk::Entry *ety_contrasena_comp;
    Gtk::Entry *ety_server_comp;
    Gtk::Entry *ety_user_bien;
    Gtk::Entry *ety_contrasena1;
    Gtk::Entry *ety_contrasena2;
    Gtk::Entry *ety_emp_bien;
    Gtk::Entry *ety_num_bien;
    Gtk::Entry *ety_dir_bien;
    Gtk::Entry *ety_rfc_bien;
    Gtk::Button *btn_comprobar;
    Gtk::Button *btn_instalar,*btn_aplica;
    Gtk::Button *pag_sig;
    Gtk::Button *pag_atras,*btn_user;
    Gtk::Button *btn_cancelar_stp;
    Gtk::StackSidebar *pila_stp;
    Gtk::Stack *pasos;
    Gtk::Box *pag_bienvenido;
    Gtk::Box *pag_conexion;
    Gtk::Box *pag_usuarios;
    Gtk::Box *pag_comp;
    Gtk::Box *pag_sumario;
    Gtk::Revealer *info_bar_bien, *progrees_bd_container;
    Gtk::InfoBar *bar_bien;
    Gtk::Label *lbl_info_bien,*lbl_emp_bien,*lbl_num_bien,*lbl_dir_bien,*lbl_rfc_bien;
    Gtk::ProgressBar *progrees_bd;
    bool m_bActivityMode;
    sigc::connection m_connection_timeout;
    coneccion *bienvenida = new coneccion();
public:
    wizard();
    ~wizard();
    void run();
protected:
    void establece_widgets();
    void conecta_senales();
    void siguiente();
    void atras();
    void cancelar();
    void comprobar();
    void comprobar_conexion();
    void instalar_bd();
    void instalar_bd_ok();
    void cerrar_info_bar(int response);
    bool on_timeout();
    void on_ety_user_bien_changed();
    void on_ety_contrasena1_changed();
    void on_ety_contrasena2_changed();
    void btn_user_clicked();
    void on_ety_emp_bien_changed();
    void on_ety_num_bien_changed();
    void on_ety_dir_bien_changed();
    void on_ety_rfc_bien_changed();
    void on_btn_aplica_clicked();
    void cierra_wizard();
}*w1;