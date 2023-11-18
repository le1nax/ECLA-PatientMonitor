#pragma once
#include <Windows.h>
#include "../include/definitions.h"
#include <cstdint>
#include <memory>
#include <fstream>
#include <vector>

class DataPoint
{
public:
	DataPoint(uint32_t canID, byte* data, uint8_t dataLength, double timestamp);
	DataPoint(uint32_t canID, char* data, uint8_t dataLength);
	DataPoint(const DataPoint& other) = default;
	uint32_t m_internID;
	char* m_value;
	char* m_beacon;
	char* m_timestamp;
	char* m_counter;
	uint8_t m_data_lenght;
	DataPointType m_datatype = DataPointType::DEBUG;
	

private:
	// uint32_t m_internID;                                  
	// char* m_data;

	// uint8_t dataLength;
	// double timestamp;
	void parseValuesFromDataString(char* data, uint8_t dataLength);

    

};