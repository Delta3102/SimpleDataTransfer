#include "relay_server.cpp"
#include "client.cpp"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Box.H>

class Interface
{
public:
    int run(Client &cl, RelayServer &srv){
        Fl_Window *window = new Fl_Window(640, 480, "SDT");

        // Инпут поля
        Fl_Input *input_ip = new Fl_Input(100, 100, 200, 30, "IP:");
        input_ip->value("127.0.0.1");

        Fl_Input *input_path = new Fl_Input(350, 100, 200, 30, "Path:");

        // Кнопочки
        Fl_Button *button_serv = new Fl_Button(100, 140, 100, 30, "Server");

        Fl_Button *button_con = new Fl_Button(275, 140, 100, 30, "Connection");
        Fl_Button *button_tr = new Fl_Button(450, 140, 100, 30, "Transmission");

        // Закрытие
        window->end();
        window->show();

        return Fl::run();
    }
};

int main(){
    Client cl;
    RelayServer srv;
    Interface intr;

    intr.run(cl, srv);
}
