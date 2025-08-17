#ifndef _LOGS_
#define _LOGS_

#include <string>
#include <fstream>

#define LOGFILE "../logs.txt"

void clear_log();
void save_log(std::string msg);

#endif