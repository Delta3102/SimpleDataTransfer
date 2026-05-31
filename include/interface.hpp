#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>

using namespace std;

class Core;

class Interface
{
private:
    Core *contr; 
    Fl_Window *window = new Fl_Window(640, 480, "SDT");
    //Поля
    Fl_Input *input_ip = new Fl_Input(80, 80, 200, 30, "IP:");
    Fl_Input *input_path = new Fl_Input(370, 80, 200, 30, "File name:");
    //Кнопки
    Fl_Button *button_serv = new Fl_Button(100, 140, 100, 30, "Server");
    Fl_Button *button_con = new Fl_Button(275, 140, 100, 30, "Receiving");
    Fl_Button *button_tr = new Fl_Button(450, 140, 100, 30, "Transmission");
    //Логи
    Fl_Text_Display *disp = new Fl_Text_Display(50, 200, 540, 200, "log");
    Fl_Text_Buffer *log_buff = new Fl_Text_Buffer();

public:
    Interface(Core *c){
        contr = c;
    }
    static void serv_clik(Fl_Widget *widget, void *data);
    static void con_clik(Fl_Widget *widget, void *data);
    static void tr_clik(Fl_Widget *widget, void *data);
    string get_ip();
    string get_name();
    void logging(string text);
    void delstr();
    int run();
};

#endif
