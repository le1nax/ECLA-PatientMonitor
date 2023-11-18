#include <functional>
#include <iostream>

// Assume Foo is defined somewhere
struct Foo {
    int data;
};

// Handler class with a member function to handle the received data
class Handler {
public:
    void handlerFunc(const Foo& fooReceived) {
        std::cout << "Handler received Foo with data: " << fooReceived.data << std::endl;
        // Add your handling logic here
    }
};

// Receiver class with a callback mechanism
class Receiver {
public:
    // Define a callback type using std::function
    using CallbackType = std::function<void(const Foo&)>;

    // Set the callback function
    void setCallback(const CallbackType& callback) {
        callback_ = callback;
    }

    // Simulate receiving data and trigger the callback
    void receiveData(const Foo& foo) {
        if (callback_) {
            callback_(foo);
        }
    }

private:
    // Callback function to be triggered when data is received
    CallbackType callback_;
};

int main() {
    // Create instances of Handler and Receiver
    Handler handler;
    Receiver receiver;

    // Set the callback function in the Receiver
    receiver.setCallback(std::bind(&Handler::handlerFunc, &handler, std::placeholders::_1));

    // Simulate receiving data in the Receiver
    Foo receivedFoo{42};
    receiver.receiveData(receivedFoo);

    return 0;
}