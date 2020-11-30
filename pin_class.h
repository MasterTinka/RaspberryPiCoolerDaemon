#ifndef PIN_CLASS_H
#define PIN_CLASS_H
#include <string>
#include <cstdlib>

class pin_class
{
public:
    pin_class(int pin_num);
    ~pin_class();
    void turn_on();
    void turn_off();
private:
    bool status;
    std::string pin;
};


#endif // PIN_CLASS_H
