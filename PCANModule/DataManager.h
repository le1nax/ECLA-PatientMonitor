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

    using CallbackType = std::function<void(const DataPoint&)>;

    void setCallback(const CallbackType& callback) {
        callback_ = callback;
    }

    void receiveData(const DataPoint& dataPoint) {
        if (callback_) {
            callback_(dataPoint);
        }
    }
private:
    // Callback function to be triggered when data is received
    CallbackType callback_;
	std::ofstream file;
};
