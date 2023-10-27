#pragma once
#include <Windows.h>
#include <cstdint>
#include <memory>
#include <fstream>
#include "DataPoint.h"

class Transmitter
{
public:
	Transmitter();
    bool sendData(const DataPoint &data);
	bool endSending();

private:
	std::ofstream file;
};
