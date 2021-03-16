#include "ProgramSetup.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

using namespace color_chart;

ParseCommandLine::ParseCommandLine(int argc, const char* argv[])
  : argc(argc), argv(argv) {

  //check how many there is parameters
  if (argc < 4 || argc > 6) {
    //throw exception if there are to many arguments
    throw std::invalid_argument("Bad number of arguments\n");
  } else {
    std::vector<uint16_t> cornersColors = getColorsFromNumbers();

    try {
      dataFromCommandLine.corners.topLeftCorner = cornersColors.at(0);
      dataFromCommandLine.corners.topRightCorner = cornersColors.at(1);
      if (argc > 4) {
          dataFromCommandLine.corners.downLeftCorner = cornersColors.at(2);
      }
      if (argc > 5) {
          dataFromCommandLine.corners.downRightCorner = cornersColors.at(3);
      }
    }catch (const std::out_of_range &outOfRange) {
      std::cerr << "ParseCommandLine():"
                << "Invalid number of arguments!\n" << outOfRange.what();
    }
    dataFromCommandLine.displayName = argv[1];
  }
}

std::vector<uint16_t> ParseCommandLine::getColorsFromNumbers() {
  std::vector<uint16_t> cornersColors;
  for (int x = 2; x < argc; x++) {
    cornersColors.emplace_back(convertCStringToInt(argv[x]));
  }

  return cornersColors;
}

uint16_t ParseCommandLine::convertCStringToInt(const char *numberToConvert) {
    uint16_t returnConvertedNumber{0};

  try {
    if (stringIsHex(numberToConvert)) {
      returnConvertedNumber = std::stoi(std::string {numberToConvert}, nullptr, 16);
    } else {
      returnConvertedNumber = std::stoi(std::string {numberToConvert});
    }
  }catch (const std::invalid_argument &invalidArgument) {
    std::cerr << "ParseCommandLine::convertCStringToInt():"
              << "Invalid argument\n" << invalidArgument.what();
  }catch (const std::out_of_range &outOfRange) {
    std::cerr << "ParseCommandLine::convertCStringToInt():"
              << "Out of range\n" << outOfRange.what();
  }

  return returnConvertedNumber;
}

bool ParseCommandLine::stringIsHex(const std::string &stringArgument) {
  std::string hexPrefix("0x");

  return stringArgument.end() != std::search(stringArgument.begin(), stringArgument.end(),
      hexPrefix.begin(), hexPrefix.end(),
      [](char first, char second) {
        return std::toupper(first) == std::toupper(second);
      });
}

DataFromUser ParseCommandLine::getInputData() {
  return dataFromCommandLine;
}
