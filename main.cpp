#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class sensors_class
{
public:
    void read_to_string();
    void read_to_int();
    float get_current_temperature();
    const string& get_sensors_output();
private:
    float cur_temperature;
    string sensors_output;
    const string& sensor_output_const = sensors_output;
};

void sensors_class::read_to_string()
{
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
    string temp_string;
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
    cout << temp_string << endl;
    this->cur_temperature = stof(temp_string);
}

float sensors_class::get_current_temperature()
{
    return this->cur_temperature;
}

const string& sensors_class::get_sensors_output()
{
    return this->sensor_output_const;
}

class programm
{
public:
    void start();
private:
    sensors_class sensors;
};

void programm::start()
{
    sensors.read_to_int();
    cout << sensors.get_sensors_output() << endl;
    cout << sensors.get_current_temperature() << endl;
}

int main()
{
    programm programm_object;
    programm_object.start();
    return 0;
}
