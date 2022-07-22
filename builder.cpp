#pragma once
#include <iostream>
#include <gtkmm.h>

class builder
{
public:
    Glib::RefPtr<Gtk::Builder> constructor;
    builder();
    ~builder();
}*login,*wizar;

builder::builder(){
    constructor = Gtk::Builder::create_from_file("window_main.glade");
}