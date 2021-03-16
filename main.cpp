#include "include/Display.h"
#include "include/ScreenBuffer.h"
#include "include/ProgramSetup.h"

#include <iostream>

int main(int argc, const char *argv[]) {
    using namespace color_chart;
    DataFromUser colorsAndDisplayName;

    try {
      colorsAndDisplayName = ParseCommandLine(argc, argv).getInputData();

    }catch (const std::exception &exception) {
      std::cerr << "Problem with parsing line\n" << exception.what();
      return -1;
    }
    
    Display display(colorsAndDisplayName.displayName);
    screen::ScreenBuffer screenBuffer(display.size().width, display.size().height);
    screenBuffer.setCornerColors(colorsAndDisplayName.corners);
    auto buffer = screenBuffer.getScreen();

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
