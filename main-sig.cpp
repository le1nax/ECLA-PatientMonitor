#include <iostream>

// Forward declaration of Class B
class ClassB;

// Class A definition
class ClassA {
public:
    // Function to read data from USB connection and send it to Class B
    void readDataFromUSB(ClassB& classBInstance) {
        // Simulating reading data from USB
        // In a real scenario, you would read data from the USB connection here
        std::string data = "Data from USB";

        // Call the function of Class B to handle the data
        classBInstance.processData(data);
    }
};

// Class B definition
class ClassB {
public:
    // Function to handle the data received from Class A
    void processData(const std::string& data) {
        // Processing logic for the received data
        std::cout << "Class B is processing data: " << data << std::endl;
    }
};

int main() {
    // Create instances of Class A and Class B
    ClassA classA;
    ClassB classB;

    // Read data from USB using Class A and pass Class B instance as a parameter
    classA.readDataFromUSB(classB);

    return 0;
}