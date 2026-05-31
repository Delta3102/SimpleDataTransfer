#ifndef CORE_HPP
#define CORE_HPP
#include "network.hpp"
#include "interface.hpp"
#include <string>

class Core
{
private:
    NetWork *Model = new NetWork(this);
    Interface *View = new Interface(this);

public:
    void loge(string text);
    void dele();
    void start_server();
    void reciv();
    void transmic();    
    void run();
};

#endif