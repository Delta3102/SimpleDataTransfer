#include "interface.hpp"
#include "client.hpp"
#include "relay_server.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>

#include <iostream>

// Инициализация объектов
static Client cl;
static RelayServer srv;

Fl_Input *input_ip = nullptr;
Fl_Input *input_path = nullptr;
Fl_Text_Display *disp = nullptr;
Fl_Text_Buffer log_buff;

void Interface::serv_clik(Fl_Widget *widget, void *data){
    srv.run(log_buff, disp);
}

void Interface::con_clik(Fl_Widget *widget, void *data){
    cl.ip_serv = input_ip->value();

    cl.receiving(log_buff, disp);
}

void Interface::tr_clik(Fl_Widget *widget, void *data){
    cl.ip_serv = input_ip->value();
    cl.data_name = input_path->value();

    cl.transmissons(log_buff, disp);
}

int Interface::run(){
    Fl_Window *window = new Fl_Window(640, 480, "SDT");

    // Инпут Отпут поля
    input_ip = new Fl_Input(80, 80, 200, 30, "IP:");
    input_ip->value("127.0.0.1");

    input_path = new Fl_Input(370, 80, 200, 30, "File name:");

    log_buff.Fl_Text_Buffer();
    log_buff.text("Start program");
    

    disp = new Fl_Text_Display(50, 200, 540, 200, "log");
    disp->buffer(log_buff);

    // Кнопки
    Fl_Button *button_serv = new Fl_Button(100, 140, 100, 30, "Server");
    button_serv->callback(serv_clik);

    Fl_Button *button_con = new Fl_Button(275, 140, 100, 30, "Receiving");
    button_con->callback(con_clik);

    Fl_Button *button_tr = new Fl_Button(450, 140, 100, 30, "Transmission");
    button_tr->callback(tr_clik);

    // Закрытие
    window->end();
    window->show();

    return Fl::run();
}
