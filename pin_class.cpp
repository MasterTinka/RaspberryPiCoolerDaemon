#include "pin_class.h"


pin_class::pin_class(int pin_num)
{
    pin = std::to_string(pin_num);
    system(("echo \"" + pin + "\" > /sys/class/gpio/export").c_str());
    system(("echo \"out\" > /sys/class/gpio/gpio" + pin + "/direction").c_str());
}


pin_class::~pin_class()
{
    system(("echo \"" + pin + "\" > /sys/class/gpio/unexport").c_str());
}

void pin_class::turn_on()
{

    system(("echo \"1\" > /sys/class/gpio/gpio" + pin + "/value").c_str());
}

void pin_class::turn_off()
{
    system(("echo \"0\" > /sys/class/gpio/gpio" + pin + "/value").c_str());
}
