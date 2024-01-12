#pragma once

#include "PCANBasic.h"
#include "DataPoint.h"

class DataManager;

class CanAdapter
{
public:
	/// @brief Constructor of CanAdapter 
	/// @param device Handles PCANUsb Adapter
	CanAdapter(TPCANHandle device);
    
	/// @brief Connects PCAN USB Adapter
	/// @return Returns Success of connection
	bool connect();
	/// @brief Read function of PCAN USB Adapter.
	/// @return Returns read Data Point
	DataPoint listen();
	/// @brief Skips a certain amount of data points. Used, when configModeDebug is set to true.
	void skipDataPoints(size_t amount);
	
	
private:
	///@brief Defines the PCAN device to be used
	TPCANHandle device;
	/// @brief caculate the total millisecond timestamp
	uint64_t calculateTotalMilliseconds(const TPCANTimestamp& timestamp);
};