#include "include/Display.h"
#include "include/ScreenBuffer.h"
#include <iostream>

int main(int argc, const char *argv[]) {
    using namespace color_chart;

    uint16_t firstColor = std::stoi(std::string(argv[2]), nullptr, 16);
    uint16_t secondColor = std::stoi(std::string(argv[3]), nullptr, 16);
  
    screen::CornersColors cornersColors {firstColor, secondColor};
    if (argc == 5) {
        cornersColors.downLeftCorner = std::stoi(std::string(argv[4]), nullptr, 16);
    }
 
    screen::ScreenBuffer screenBuffer(16, 9);
    screenBuffer.setCornerColors(cornersColors);
    auto buffer = screenBuffer.getScreen();

    Display display("dupa");

    int16_t y{0};
    for(auto& stripe : buffer) {
        int16_t x{0};
        for(auto& pixel : stripe) {
            display.draw({x, y}, &pixel, 1);
            x++;
        }
        y++;
    }
    display.present();

    return 0;
}
