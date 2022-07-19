#include "login.cpp"

int main(int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);
  v1 = new Login();
  v1->show();
  Gtk::Main::run();
  return EXIT_SUCCESS;
}