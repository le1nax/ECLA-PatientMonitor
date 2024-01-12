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
		if(configModeDebug){ 
			std::cout <<  "connection successful" << std::endl;
			std::cout <<  device << std::endl;
		}
		return true;
	}

	// If the connection failed, return false
	else
		if(configModeDebug){
		std::cout <<  "connection failed" << std::endl;
		return false;
		}
}

uint64_t CanAdapter::calculateTotalMilliseconds(const TPCANTimestamp& timestamp) {
    // Use uint64_t to prevent overflow during calculations
    uint64_t totalMilliseconds = static_cast<uint64_t>(timestamp.millis) +
                                 (static_cast<uint64_t>(timestamp.millis_overflow) << 32);
    
    return totalMilliseconds;
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
			if(configModeDebug){
				 std::cout <<  "received" << std::endl;
			}
			DataPoint parsed = DataPoint(pcanMessage.ID, reinterpret_cast<char*>(pcanMessage.DATA), calculateTotalMilliseconds(pcanTimestamp), 4);
			return parsed;
		}
	}
}

void CanAdapter::skipDataPoints(size_t amount)
{

	for(size_t i=0; i<amount; ++i)
	{
		while (true)
	{
		TPCANMsg pcanMessage;
		TPCANStatus m_pcanResult;
		// Try to read a PCAN message
		m_pcanResult = CAN_Read(PCAN_USBBUS1, &pcanMessage, nullptr);
		// If a message was received, print its details to the console
		if (m_pcanResult == PCAN_ERROR_OK)
		{
			break;
		}
	}
	}
}