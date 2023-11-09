#include "DataPoint.h"
#include "../include/definitions.h"

DataPoint::DataPoint(uint32_t m_internID, byte* data, uint8_t dataLength, double timestamp)
{
	// byte* temp_data = new byte[dataLength];
	// for (int i = 0; i < dataLength; i++)
	// {
	// 	temp_data[i] = data[i];
	// }
	// data = std::unique_ptr<byte[]>(temp_data);
	// m_internID = m_internID;
	// dataLength = dataLength;
	// timestamp = timestamp;
}

DataPoint::DataPoint(uint32_t canID, char* data, uint8_t dataLength)
{
	m_internID = canID;
	parseValuesFromDataString(data, dataLength);
}

void DataPoint::parseValuesFromDataString(char* data, uint8_t dataLength)
{
	m_value = ReadBytesFromBufferc(data, 0, valuebuffersize);
	m_beacon = ReadBytesFromBufferc(data, valuebuffersize, beaconbuffersize);
	m_timestamp = ReadBytesFromBufferc(data, valuebuffersize+beaconbuffersize, timestampbuffersize);
	m_counter = ReadBytesFromBufferc(data, valuebuffersize+beaconbuffersize+timestampbuffersize, counterbuffersize);
}