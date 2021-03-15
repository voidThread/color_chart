#include "include/Display.h"
#include "include/ScreenBuffer.h"
#include <iostream>

int main(int argc, const char *argv[]) {
    using namespace color_chart;

    uint16_t firstColor = std::stoi(std::string(argv[2]), nullptr, 16);
    uint16_t secondColor = std::stoi(std::string(argv[3]), nullptr, 16);
    
    screen::CornersColors cornersColors {firstColor, secondColor};

    screen::ScreenBuffer screenBuffer(16, 9);
    screenBuffer.setCornerColors(cornersColors);
    auto buffer = screenBuffer.getScreen();

    Display display("dupa");

/*    auto horizontal = buffer.begin();
    for (int16_t x{0}; x < buffer.size(); x++) {
        auto vertical = horizontal->begin();
        for (int16_t y{0}; y <buffer.front().size(); y++) {
            display.draw({x, y}, &(*vertical), 1);
            std::next(vertical);
        }
        std::next(horizontal);
    }*/
int16_t y{0};
    for(auto& stripe : buffer) {
//        std::cout << '\n';
        int16_t x{0};
        for(auto& pixel : stripe) {
//            std::cout << std::hex << "|" << pixel << "|";
            display.draw({x, y}, &pixel, 1);
            x++;
        }
        y++;
    }
    display.present();

    return 0;
}
