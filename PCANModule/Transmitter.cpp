#include "Transmitter.h"
#include <ctime>

Transmitter::Transmitter()
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	this->file = std::ofstream("Data.txt");
	file << "ID " << "0x0001" << ",Count of Sensors " << "1" << ",Datum " << "07.03.2023 15:52" << std::endl;
	file << std::endl;
	file << std::endl;
	file << std::endl;
	file << "Start of Measurement:" << std::endl;
	file << std::endl;
	
}

bool Transmitter::sendData(const DataPoint& data)
{
	file << data.internID << ",";
	for (int i = 0; i < data.dataLength; i++)
	{
		file << data.data[i];
	}
	file << "," << data.timestamp << std::endl;
	return true;
}

bool Transmitter::endSending()
{
	file.close();
	return true;
}