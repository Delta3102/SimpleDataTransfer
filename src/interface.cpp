#include "core.hpp"
#include "interface.hpp"
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>

using namespace std;

string Interface::get_ip(){
    return input_ip->value();
}

string Interface::get_name(){
    return input_path->value();
}

void Interface::serv_clik(Fl_Widget *widget, void *data){
    auto* obj = static_cast<Core*>(data);
    obj->start_server();
}

void Interface::con_clik(Fl_Widget *widget, void *data){
    auto* obj = static_cast<Core*>(data);
    obj->reciv();
}

void Interface::tr_clik(Fl_Widget *widget, void *data){
    auto* obj = static_cast<Core*>(data);
    obj->transmic();
}

void Interface::logging(string text){
    log_buff->append(text.c_str());
    log_buff->append("\n");
    disp->redraw();
    Fl::check();
}

void Interface::delstr(){
    int end = log_buff->length();
    int start = log_buff->line_start(end-1);
    log_buff->remove(start, end);
}

int Interface::run(){
    //Настройка виджетов
    input_ip->value("127.0.0.1");
    disp->buffer(log_buff);
    //Настройка кнопок
    button_serv->callback(serv_clik, contr);
    button_con->callback(con_clik, contr);
    button_tr->callback(tr_clik, contr);
    // Закрытие
    window->end();
    window->show();
    return Fl::run();
}
