#include "../include/DataLogger.h"

DataLogger::DataLogger(){

}

void DataLogger::logData(const std::string& filename, const DataPoint& data) {
        std::ofstream file(filename, std::ios_base::app); // Open file in append mode
        if (file.is_open()) {
            file << data.encodedData.value << std::endl; // Write data to file
            file.close();
            std::cout << "Data logged to " << filename << std::endl;
        } else {
            std::cerr << "Error: Unable to open file " << filename << " for writing" << std::endl;
        }
    }