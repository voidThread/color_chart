#pragma once

#include "Defines.h"
#include "LinearMix.h"

#include <optional>

namespace color_chart {
namespace screen {

    using BufferScreen = std::list<defines::OneLineGradient>;
    struct CornersColors {
            defines::RGB565 topLeftCorner{0};
            defines::RGB565 topRightCorner{0};
            std::optional<defines::RGB565> downLeftCorner;
            std::optional<defines::RGB565> downRightCorner;
    };

    class IScreenBuffer {
        public:
            virtual void setCornerColors(screen::CornersColors colors) =0;
            virtual BufferScreen getScreen() =0;

            virtual ~IScreenBuffer() = default;
    };

    class ScreenBuffer : public IScreenBuffer {
        public:
            void setCornerColors(screen::CornersColors colors) override;
            BufferScreen getScreen() override;

            virtual ~ScreenBuffer() = default;
            ScreenBuffer(int width, int height);

        private:
            screen::CornersColors cornersColors;
            equations::LinearMix linearMix;
            int screenWidth, screenHeight;
    };

}
}
