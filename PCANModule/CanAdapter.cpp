#include <iostream>
#include "CanAdapter.h"

CanAdapter::CanAdapter(TPCANHandle device)
{
	this->device = device;
}
bool CanAdapter::connect()
{
	
	// Try to connect to the device
	TPCANStatus status = CAN_Initialize(device, PCAN_BAUD_1M);

	// If the connection was successful, return true
	if (status == PCAN_ERROR_OK)
	{
		std::cout << "connection successful" << std::endl;
		std::cout << device << std::endl;
		return true;
	}

	// If the connection failed, return false
	else
		std::cout << "connection failed" << std::endl;
		return false;
}

DataPoint CanAdapter::listen()
{
	TPCANStatus m_pcanResult;
	TPCANMsg pcanMessage;
	TPCANTimestamp pcanTimestamp;
	while (true)
	{
		// Try to read a PCAN message
		m_pcanResult = CAN_Read(PCAN_USBBUS1, &pcanMessage, &pcanTimestamp);
		// If a message was received, print its details to the console
		if (m_pcanResult == PCAN_ERROR_OK)
		{
			std::cout << "received" << std::endl;
			DataPoint parsed = DataPoint(pcanMessage.ID, reinterpret_cast<char*>(pcanMessage.DATA), 20); 
			return parsed;
			//return parseDatapoint(pcanMessage);
		}
	}
}

DataPoint CanAdapter::parseDatapoint(TPCANMsg msg)
{
	std::cout << "received" << std::endl;

	return DataPoint(msg.ID, reinterpret_cast<char*>(msg.DATA), 20);
	
}