#pragma once

#include "Defines.h"

namespace color_chart {
namespace equations {
    class IGradientMix {
        public:
            virtual defines::OneLineGradient mix(defines::RGB565 startColor, defines::RGB565 endColor, std::size_t gradientLength) =0;
            virtual defines::Subpixels substractComponentColors(defines::RGB565 color) =0;
            virtual defines::Subpixels calculateNewColor(int pixelNumber, std::size_t gradientLength) =0;
            virtual defines::RGB565 makeRGB565(defines::Subpixels color) =0;

            virtual ~IGradientMix() = default;
    };

    class LinearMix : public IGradientMix {
        public:
            defines::OneLineGradient mix(defines::RGB565 startColor, defines::RGB565 endColor, std::size_t gradientLength) override;
            defines::Subpixels substractComponentColors(defines::RGB565 color) override;
            defines::Subpixels calculateNewColor(int pixelNumber, std::size_t gradientLength) override;
            defines::RGB565 makeRGB565(defines::Subpixels color) override;

            virtual ~LinearMix() = default;

        private:
            defines::Subpixels startComponents{0};
            defines::Subpixels endComponents{0};
    };
}
}
