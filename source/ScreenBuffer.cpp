#include "ScreenBuffer.h"
#include <algorithm>
#include <iostream>

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

   } else if (cornersColors.downLeftCorner.has_value() && cornersColors.downRightCorner.has_value() == false) {
        //calculate first position in horizontal line
        uint16_t startTemp{cornersColors.topLeftCorner}, endTemp{cornersColors.downLeftCorner.value()};
        auto needToReverse{false};
        if (cornersColors.topLeftCorner > cornersColors.downLeftCorner) {
            startTemp = cornersColors.downLeftCorner.value();
            endTemp = cornersColors.topLeftCorner;
            needToReverse = true;
        }
        auto firstPixelsInLines = linearMix.mix(startTemp, endTemp, screenHeight);
        if (needToReverse) {
            std::reverse(firstPixelsInLines.begin(), firstPixelsInLines.end());
        }
           
        needToReverse = false;
        screen::BufferScreen buffer;
        for (auto& firstPixel : firstPixelsInLines) {
            startTemp = firstPixel;
            endTemp = cornersColors.topRightCorner;
            if (firstPixel > cornersColors.topRightCorner) {
                startTemp = cornersColors.topRightCorner;
                endTemp = firstPixel;
                needToReverse = true;
            }
            auto oneline = linearMix.mix(startTemp, endTemp, screenWidth);
            if (needToReverse) {
                std::reverse(oneline.begin(), oneline.end());
            }
            buffer.emplace_back(oneline);
        }
        return buffer;

   } else if (cornersColors.downRightCorner.has_value()) {
       screen::BufferScreen buffer;
       auto needToReverse{false};
       if (cornersColors.topLeftCorner > cornersColors.downLeftCorner.value()) {
           std::swap(cornersColors.topLeftCorner, cornersColors.downLeftCorner.value());
           needToReverse = true;
       }
       auto firstPixelsInLine = linearMix.mix(cornersColors.topLeftCorner, 
               cornersColors.downLeftCorner.value(), screenHeight);
       if (needToReverse) {
           std::reverse(firstPixelsInLine.begin(), firstPixelsInLine.end());
       }

       needToReverse = false;
       if (cornersColors.topRightCorner > cornersColors.downRightCorner.value()) {
          std::swap(cornersColors.topRightCorner, cornersColors.downRightCorner.value());
          needToReverse = true;
       }
       auto lastPixelsInLine = linearMix.mix(cornersColors.topRightCorner, 
               cornersColors.downRightCorner.value(), screenHeight);
       if (needToReverse) {
           std::reverse(lastPixelsInLine.begin(), lastPixelsInLine.end());
       }
 
       auto lastPixel = lastPixelsInLine.begin();
       for (auto& firstPixel : firstPixelsInLine) {
           needToReverse = false;
           if (firstPixel > *lastPixel) {
               std::swap(firstPixel, *lastPixel);
               needToReverse = true;
           }
           auto horizontalLine = linearMix.mix(firstPixel, *lastPixel, screenWidth);
           if (needToReverse) {
               std::reverse(horizontalLine.begin(), horizontalLine.end());
           }
           buffer.emplace_back(horizontalLine);
           lastPixel = std::next(lastPixel);
       }
       return buffer;
   }
   return screen::BufferScreen(0, defines::OneLineGradient(0));
}

screen::ScreenBuffer::ScreenBuffer(int width, int height) 
    :screenWidth(width), screenHeight(height) {
}
