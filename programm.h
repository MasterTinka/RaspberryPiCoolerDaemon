#ifndef PROGRAMM_H
#define PROGRAMM_H
#include "sensors_class.h"
#include "pin_class.h"
#include <string>
#include <unistd.h>
#include <fstream>
#include <iostream>


class programm
{
public:
    void start();
private:
    [[noreturn]] void loop();
    int max_temp;
    unsigned int interval;
    unsigned int working_time;
    sensors_class sensors;
    pin_class *cooler;
};


#endif // PROGRAMM_H
