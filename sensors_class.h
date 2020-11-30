#ifndef SENSORS_CLASS_H
#define SENSORS_CLASS_H
#include <string>

class sensors_class
{
public:
    float get_current_temperature();
    const std::string& get_sensors_output();
private:
    void read_to_string();
    void read_to_int();

    float cur_temperature;
    std::string sensors_output;
    const std::string& sensor_output_const = sensors_output;
};

#endif // SENSORS_CLASS_H
