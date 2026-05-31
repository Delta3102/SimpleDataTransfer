#include "core.hpp"
#include "network.hpp"
#include "interface.hpp"
#include <string>

void Core::loge(string text){
    View->logging(text);
}

void Core::dele(){
    View->delstr();
}

void Core::start_server(){
    Model->server_run();
}

void Core::reciv(){
    Model->set_ip(View->get_ip());
    Model->set_data_name(View->get_name());
    Model->receiving();
}

void Core::transmic(){
    Model->set_ip(View->get_ip());
    Model->set_data_name(View->get_name());
    Model->transmissons();
}

void Core::run(){
    View->run(); 
}