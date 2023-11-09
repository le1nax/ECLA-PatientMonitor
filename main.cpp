#include "PCANBasic.h"
#include <iostream>

//PCANModule includes
#include "PCANModule/Transmitter.h"
#include "PCANModule/DataPoint.h"
#include "PCANModule/CanAdapter.h"

#include <thread>

int main()
{
    std::cout << "Test" << std::endl;
	TPCANHandle device = PCAN_USBBUS1;
	CanAdapter can_adapter(device);
	Transmitter tr;
	while (!can_adapter.connect())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	
	for (size_t i = 0; i < 15; i++)
	{
		DataPoint data = can_adapter.listen();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		tr.sendData(data);
	}
	tr.endSending();

	
	return 0;
}
