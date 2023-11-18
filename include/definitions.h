#pragma once

#include <cmath>
#include <memory>
#include <list>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <memory>
#include <cstring>
#include <codecvt>
#include <locale>
#include <iomanip>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "imgui.h"

static constexpr size_t maxbuffersize = 2001;
static constexpr size_t valuebuffersize = sizeof(int32_t);
static constexpr size_t beaconbuffersize = sizeof(uint8_t);
static constexpr size_t timestampbuffersize = sizeof(uint16_t);
static constexpr size_t counterbuffersize = beaconbuffersize;

enum class DataPointType 
{
    BP = 0, 
    ECG = 1, 
    CONFIG = 2,
    DEBUG = 3
};

template<typename... Ts>
std::vector<std::byte> make_bytes(Ts&&... args) noexcept {
return{std::byte(std::forward<Ts>(args))...};
}

static void readBytesFromArray(const char* array, size_t numBytes) {
    for (size_t i = 0; i < numBytes; ++i) {
        std::cout << std::hex << static_cast<int>(static_cast<uint8_t>(array[i])) << " ";
    }
    std::cout << std::endl;
}

static std::string ReplaceNullCharacters(const std::string& inputString) {
    std::string outputString = inputString;
    size_t pos = outputString.find('\0');
    while (pos != std::string::npos) {
        outputString.replace(pos, 1, "");
        pos = outputString.find('\0', pos);
    }
    return outputString;
}

static uint16_t Get16bitLSBfromUInt(uint32_t sourcevalue)
        {
            uint32_t lsb = (sourcevalue & 0xFFFF);
            return (uint16_t)lsb;
        }

static std::string TrimString(const std::string& inputString) {
    std::string trimmedString = inputString;
    size_t firstNonWhitespace = trimmedString.find_first_not_of(" \t\r\n");
    size_t lastNonWhitespace = trimmedString.find_last_not_of(" \t\r\n");
    if (firstNonWhitespace != std::string::npos && lastNonWhitespace != std::string::npos) {
        trimmedString = trimmedString.substr(firstNonWhitespace, lastNonWhitespace - firstNonWhitespace + 1);
    }
    else {
        trimmedString.clear();
    }
    return trimmedString;
}

static std::string Utf8ToString(const std::string& utf8String)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wideString = converter.from_bytes(utf8String);
    std::string outputString(wideString.begin(), wideString.end());
    return outputString;
}

static inline constexpr size_t uInt16Size = sizeof(unsigned short);


/// @brief Konvertiert einen big-endian buffer in einen integer in little endian 
/// @param buffer 
/// @param startIndex 
/// @param length 
/// @return 
static unsigned long ReadByteValuesFromBufferLittleEndian(const char* buffer, unsigned long  startIndex, unsigned long  numBytesToRead)
{
    unsigned long  value;
    std::memcpy(&value, buffer + startIndex, numBytesToRead);
    return value;
}

static unsigned long Read16ByteValuesFromBufferLittleEndian(const char* buffer, unsigned long  startIndex)
{
    unsigned long  value;
    std::memcpy(&value, buffer + startIndex, uInt16Size);
    return value;
}

static std::string formatTm(const struct tm& timeInfo) {
    std::ostringstream oss;

    oss << std::setfill('0');  // Set fill character to '0'

    // Format date components: dd-MM-yyyy
    oss << std::setw(2) << timeInfo.tm_mday << "-"
        << std::setw(2) << (timeInfo.tm_mon + 1) << "-"
        << std::setw(4) << (timeInfo.tm_year + 1900) << " ";

    // Format time components: HH:mm:ss.fff
    oss << std::setw(2) << timeInfo.tm_hour << ":"
        << std::setw(2) << timeInfo.tm_min << ":"
        << std::setw(2) << timeInfo.tm_sec << "."
        << std::setw(3) << 0 << std::setfill('0');  // Fill milliseconds with '0'

    return oss.str();
}

// Function to plot a std::vector<int>
static void PlotVector(const char* label, const std::vector<float>& values) {

    ImGui::PlotLines(label, values.data(), static_cast<int>(values.size()), 0, nullptr, FLT_MIN, FLT_MAX, ImVec2(0, 80));
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}


static int BinaryCodedDecimalToInteger(int value)
        {
            if (value != 0xFF)
            {
                int lowerNibble = value & 0x0F;
                int upperNibble = value >> 4;

                int multipleOfOne = lowerNibble;
                int multipleOfTen = upperNibble * 10;

                return (multipleOfOne + multipleOfTen);
            }
            else return 0;
        }

static std::unique_ptr<char[]> ReadBytesFromBuffer(const char* array, size_t startIndex, size_t numBytes) {
    std::unique_ptr<char[]> output(new char[numBytes]);

    for (size_t i = 0; i < numBytes; ++i) {
        output[i] = array[startIndex + i];
    }

    return output;
}

static uint16_t Read16ByteValuesFromBuffer(const char* buffer, size_t startIndex) {
    char* buf = ReadBytesFromBuffer(buffer, startIndex, uInt16Size).release();
    unsigned long  value = 0;
    std::memcpy(&value, buf, uInt16Size);
    delete[] buf;
    return value;
}


/// @todo exeption handling 
static int32_t ReadByteSignedValuesFromBuffer(const char* buffer, unsigned long  startIndex, unsigned long  numBytesToRead)
{
    auto buf = ReadBytesFromBuffer(buffer, startIndex, numBytesToRead).release();
    // unsigned long  value = 0;
    // std::memcpy(&value, buf, numBytesToRead);

    int32_t interpretedValue = *(int*)buf;
    delete[] buf;
    return interpretedValue;
}   