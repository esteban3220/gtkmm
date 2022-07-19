#ifndef _BUILDER
#define _BUILDER

#include <iostream>
#include <gtkmm.h>

class builder
{
public:
    Glib::RefPtr<Gtk::Builder> constructor;
    builder();
    ~builder();
}*build;

builder::builder(){
    constructor = Gtk::Builder::create_from_file("window_main.glade");
}
#endif