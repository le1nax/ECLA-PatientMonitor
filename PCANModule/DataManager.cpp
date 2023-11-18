#include "DataManager.h"
#include <ctime>

DataManager::DataManager()
{
	dispManager = std::make_shared<DisplayManager>();
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	this->file = std::ofstream("Data.txt");
	file << "ID " << "0x0001" << ",Count of Sensors " << "1" << ",Datum " << "07.03.2023 15:52" << std::endl;
	file << std::endl;
	file << std::endl;
	file << std::endl;
	file << "Start of Measurement:" << std::endl;
	file << std::endl;
	setCallback(std::bind(&DisplayManager::onPressureChanged, dispManager, std::placeholders::_1));
}

bool DataManager::sendData(const DataPoint& data)
{
	dispManager->onPressureChanged(data);
	// receiveData(data);
	// if(data.m_datatype == DataPointType::DEBUG)
	// {
	// 	dataSignal(data);
	// }
	return true;
}

bool DataManager::endSending()
{
	file.close();
	return true;
}