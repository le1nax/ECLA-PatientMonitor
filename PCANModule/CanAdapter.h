#pragma once

#include "PCANBasic.h"
#include "DataPoint.h"

class DataManager;

class CanAdapter
{
public:
	// Method to establish a connection to a CAN adapter via USB
	CanAdapter(TPCANHandle device);
    
	bool connect();
	DataPoint listen();
	void skipDataPoints(size_t amount);
	
	
private:
	// Define the PCAN device to be used
	TPCANHandle device;
	uint64_t calculateTotalMilliseconds(const TPCANTimestamp& timestamp);
};