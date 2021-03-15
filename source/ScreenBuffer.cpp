#include "ScreenBuffer.h"

using namespace color_chart;

void screen::ScreenBuffer::setCornerColors(screen::CornersColors colors) {
    cornersColors = colors;
}

screen::BufferScreen screen::ScreenBuffer::getScreen() {
   if (cornersColors.downLeftCorner.has_value() == false && 
           cornersColors.downRightCorner.has_value() == false) {
        auto oneline = linearMix.mix(cornersColors.topLeftCorner, cornersColors.topRightCorner, screenWidth);
        return screen::BufferScreen(screenHeight, oneline);
   }
   return screen::BufferScreen(0, defines::OneLineGradient(0));
}

screen::ScreenBuffer::ScreenBuffer(int width, int height) 
    :screenWidth(width), screenHeight(height) {
}
