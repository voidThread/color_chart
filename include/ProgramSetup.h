#pragma once

#include "ScreenBuffer.h"

#include <string>
#include <vector>

namespace color_chart {
// Structure for handling PODs from user input
struct DataFromUser {
    screen::CornersColors corners;
    std::string displayName;
};


// This class parsing user input to proper types
// name - string
// colors - 16bit unsigned int
class ParseCommandLine {
    public:
        ParseCommandLine(int argc, const char* argv[]);
        DataFromUser getInputData();

    private:
        std::vector<uint16_t> getColorsFromNumbers();
        static uint16_t convertCStringToInt(const char *numberToConvert);
        static bool stringIsHex(const std::string &stringArgument);

        int argc;
        const char** argv;
        DataFromUser dataFromCommandLine;
};
}
