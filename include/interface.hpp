#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>

class Interface
{
public:
    static void serv_clik(Fl_Widget *widget, void *data);
    static void con_clik(Fl_Widget *widget, void *data);
    static void tr_clik(Fl_Widget *widget, void *data);

    int run();
};

#endif
