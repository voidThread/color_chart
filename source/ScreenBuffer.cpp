#include "ScreenBuffer.h"
#include <algorithm>

using namespace color_chart;

void screen::ScreenBuffer::setCornerColors(screen::CornersColors colors) {
    cornersColors = colors;
}

screen::BufferScreen screen::ScreenBuffer::getScreen() {
   if (cornersColors.downLeftCorner.has_value() == false && 
           cornersColors.downRightCorner.has_value() == false) {

       auto needToReverse{false};
       if (cornersColors.topLeftCorner > cornersColors.topRightCorner) {
            std::swap(cornersColors.topLeftCorner, cornersColors.topRightCorner);
            needToReverse = true;
       }

       auto oneline = linearMix.mix(cornersColors.topLeftCorner, cornersColors.topRightCorner, screenWidth);

       if (needToReverse) {
           std::reverse(oneline.begin(), oneline.end());
       }
       return screen::BufferScreen(screenHeight, oneline);
   } else if (cornersColors.downLeftCorner.has_value()) {
        //calculate first position in horizontal line
        uint16_t startTemp{cornersColors.topLeftCorner}, endTemp{cornersColors.downLeftCorner.value()};
        if (cornersColors.topLeftCorner > cornersColors.downLeftCorner) {
            startTemp = cornersColors.downLeftCorner.value();
            endTemp = cornersColors.topLeftCorner;
        }
        auto firstPixelsInLines = linearMix.mix(startTemp, endTemp, screenHeight);
           
        screen::BufferScreen buffer;
        for (auto& firstPixel : firstPixelsInLines) {
            auto oneline = linearMix.mix(firstPixel, cornersColors.topRightCorner, screenWidth);
            buffer.emplace_back(oneline);
        }
        return buffer;
   }
   return screen::BufferScreen(0, defines::OneLineGradient(0));
}

screen::ScreenBuffer::ScreenBuffer(int width, int height) 
    :screenWidth(width), screenHeight(height) {
}
