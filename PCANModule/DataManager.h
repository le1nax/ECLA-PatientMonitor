#pragma once
#include <Windows.h>
#include <cstdint>
#include <memory>
#include <fstream>
#include "DataPoint.h"
#include "../include/DisplayManager.h"
#include <functional>
// #include <sigc++/signal.h>
// #include <sigc++/connection.h>

class DataManager
{
public:
	DataManager();
    bool sendData(const DataPoint &data);
	bool endSending();
    std::shared_ptr<DisplayManager> dispManager;

	// sigc::signal<void(DataPoint &data)> dataSignal;

    // Define a callback type using std::function
    using CallbackType = std::function<void(const DataPoint&)>;

    // Set the callback function
    void setCallback(const CallbackType& callback) {
        callback_ = callback;
    }

    // Simulate receiving data and trigger the callback
    void receiveData(const DataPoint& dataPoint) {
        if (callback_) {
            callback_(dataPoint);
        }
    }

    bool sendDataUdp(const DataPoint& dataPoint);
private:
    // Callback function to be triggered when data is received
    CallbackType callback_;
	std::ofstream file;
};
