#include "DataPoint.h"


DataPoint::DataPoint(uint32_t internID, byte* data, uint8_t dataLength, double timestamp)
{
	byte* temp_data = new byte[dataLength];
	for (int i = 0; i < dataLength; i++)
	{
		temp_data[i] = data[i];
	}
	this->data = std::unique_ptr<byte[]>(temp_data);
	this->internID = internID;
	this->dataLength = dataLength;
	this->timestamp = timestamp;
}