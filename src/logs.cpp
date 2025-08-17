#include "logs.hpp"

void clear_log()
{
    std::ofstream fout;
    fout.open(LOGFILE, std::ios::trunc);
    fout.close();
}

void save_log(std::string msg)
{
    std::ofstream fout;
    fout.open(LOGFILE, std::ios::app);
    fout << msg << std::endl;
    fout.close();
}