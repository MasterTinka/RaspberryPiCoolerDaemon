#include "sensors_class.h"

void sensors_class::read_to_string()
{
    sensors_output.clear();
    FILE* sensors = popen("sensors -A \"cpu_thermal-virtual-0\"", "r");
    char * buffer = new char[1024];
    while(!feof(sensors))
    {
        fgets(buffer, 1024, sensors);
        sensors_output += buffer;
    }
    delete[] buffer;
}

void sensors_class::read_to_int()
{
    this->read_to_string();
    std::string temp_string;
    for(unsigned int i = sensors_output.find("temp1"); i < sensors_output.size(); i++)
    {
        if(sensors_output.at(i) == '+')
        {
            for (unsigned int j = i + 1; j <= i + 4; j++)
            {
                temp_string += sensors_output.at(j);
            }
            break;
        }
    }
    this->cur_temperature = stof(temp_string);
}

float sensors_class::get_current_temperature()
{
    this->read_to_int();
    return this->cur_temperature;
}

const std::string& sensors_class::get_sensors_output()
{
    this->read_to_string();
    return this->sensor_output_const;
}
