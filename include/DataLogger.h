#pragma once

#include "../PCANModule/DataPoint.h"
#include <iostream>
#include <fstream>
#include <string>

// Logger class for logging data
class DataLogger {
public:
    DataLogger();
    void logData(const std::string& filename, const DataPoint& data);
    
};