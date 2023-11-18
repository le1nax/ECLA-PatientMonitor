#include "PCANBasic.h"
#include <iostream>

#include "include/definitions.h"

//PCANModule includes
#include "PCANModule/DataManager.h"
#include "PCANModule/DataPoint.h"
#include "PCANModule/CanAdapter.h"

#include "include/DisplayManager.h"

#include <thread>

#include <vector>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

int main()
{
	TPCANHandle device = PCAN_USBBUS1;
	CanAdapter can_adapter(device);
	DataManager dataManagerInstance;
	dataManagerInstance.dispManager->initWindow();
	while (!can_adapter.connect())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	
	// for (size_t i = 0; i < 100; i++)
	while(1)
	{
		DataPoint data = can_adapter.listen();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		can_adapter.skipDataPoints(3000);
		dataManagerInstance.sendData(data);
		// float readData = static_cast<float>(ReadByteSignedValuesFromBuffer(data.m_value, 0 ,data.m_data_lenght));
    	// std::cout << "handeled datapoint: " << readData << "at time: " <<  std::endl;
	}

	dataManagerInstance.endSending();

    return 0;
}
