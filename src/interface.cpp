#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Box.H>
#include <iostream>

#include "interface.hpp"
#include "client.hpp"

void Interface::serv_clik(Fl_Widget *widget, void *data){
    cout << "HELLO" << endl;
    Client cl;
    cl.settings();
}

void Interface::con_clik(Fl_Widget *widget, void *data){
    cout << "WORLD" << endl;
}

void Interface::tr_clik(Fl_Widget *widget, void *data){
    cout << "!" << endl;
}

int Interface::run(){
    Fl_Window *window = new Fl_Window(640, 480, "SDT");

    // Инпут поля
    Fl_Input *input_ip = new Fl_Input(100, 100, 200, 30, "IP:");
    input_ip->value("127.0.0.1");

    Fl_Input *input_path = new Fl_Input(350, 100, 200, 30, "Path:");

    // Кнопочки
    Fl_Button *button_serv = new Fl_Button(100, 140, 100, 30, "Server");
    button_serv->callback(serv_clik);

    Fl_Button *button_con = new Fl_Button(275, 140, 100, 30, "Connection");
    button_con->callback(con_clik);

    Fl_Button *button_tr = new Fl_Button(450, 140, 100, 30, "Transmission");
    button_tr->callback(tr_clik);

    // Закрытие
    window->end();
    window->show();

    return Fl::run();
}
