#include "programm.h"

void programm::start()
{
    if(access("/etc/CoolerDaemon.conf", 0) == -1)
    {
        if(access("/etc/CoolerDaemon.conf", 2) == 0)
        {
            std::ofstream fout("/etc/CoolerDaemon.conf");
            fout << "# Lines must be written in one piece" << std::endl;
            fout << "pin=14" << std::endl;
            fout << "max_temp=50" << std::endl;
            fout << "interval=10" << std::endl;
            fout << "working_time=600" << std::endl;
        }
        else
        {
           std::ofstream fout("/tmp/cooler.log");
           fout << "*****THERE IS NO LOG FILE*****" << std::endl;
           fout << "*******PLEASE CREATE IT*******" << std::endl;
           fout << "****/etc/CoolerDaemon.conf****" << std::endl;
           fout << "******RUNNIG ON DEFAULTS******" << std::endl;
           this->cooler = new pin_class(14);
           this->interval = 10;
           this->max_temp = 50;
           this->working_time = 600;
           this->loop();
        }
    }
    std::ifstream fin("/etc/CoolerDaemon.conf");
    if(fin.is_open())
    {
        while(!fin.eof())
        {
            std::string temp;
            getline(fin, temp);
            if(temp.front() == '#')
                continue;
            else if (!temp.find("pin="))
            {
                temp.erase(0, temp.find_first_of("=") + 1);
                cooler = new pin_class(atoi(temp.c_str()));
            }
            else if (!temp.find("max_temp="))
            {
                temp.erase(0, temp.find_first_of("=") + 1);
                max_temp = atoi(temp.c_str());
            }
            else if (!temp.find("interval="))
            {
                temp.erase(0, temp.find_first_of("=") + 1);
                interval = atoi(temp.c_str());
            }
            else if (!temp.find("working_time="))
            {
                temp.erase(0, temp.find_first_of("=") + 1);
                working_time = atoi(temp.c_str());
            }
            temp.clear();
        }
    }
    this->loop();
}

[[noreturn]] void programm::loop()
{
    std::ofstream fout("/tmp/cooler.log");
    while(true)
    {
        fout << sensors.get_current_temperature() << " - beginning of cycle" << std::endl;
        while(sensors.get_current_temperature() < max_temp)
        {
            fout << sensors.get_current_temperature() << " - sleeping" << std::endl;
            cooler->turn_off();
            sleep(interval);
        }
        fout << sensors.get_current_temperature() << " - turning on" << std::endl;
        cooler->turn_on();
        sleep(working_time);
    }
}
