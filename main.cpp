#include "Display.h"
#include "ScreenBuffer.h"

int main(int argc, const char *argv[]) {
    using namespace color_chart;

    uint16_t firstColor = std::stoi(argv[2], nullptr, 16);
    uint16_t secondColor = std::stoi(argv[3], nullptr, 16);
    
    screen::CornersColors cornersColors {firstColor, secondColor};

    screen::ScreenBuffer screenBuffer(16, 9);
    screenBuffer.setCornerColors(cornersColors);
    auto buffer = screenBuffer.getScreen();

    Display display("dupa");

    auto horizontal = buffer.begin();
    for (int16_t x{0}; x < buffer.size(); x++) {
        auto vertical = horizontal->begin();
        for (int16_t y{0}; y <buffer.front().size(); x++) {
            display.draw({x, y}, &(*vertical), 1);
            std::next(vertical);
        }
        std::next(horizontal);
    }

    return 0;
}
