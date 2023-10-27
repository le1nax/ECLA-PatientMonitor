#pragma once
#include <Windows.h>
#include <cstdint>
#include <memory>
#include <fstream>

class DataPoint
{
public:
	DataPoint(uint32_t internID, byte* data, uint8_t dataLength, double timestamp);
	DataPoint(const DataPoint& other);
	
	uint32_t internID;                                  
	std::unique_ptr<byte[]> data;
	uint8_t dataLength;
	double timestamp;
    
private:

};