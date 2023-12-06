#include "include/DataTransfer.h"

int main()
{
	std::unique_ptr<DataTransfer> dataTransfer = std::make_unique<DataTransfer>();
	dataTransfer->establishConnection();
    return 0;
}
