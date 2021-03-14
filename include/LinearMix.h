#pragma once

#include <cstdint>
#include <list>
#include <array>
#include <any>
#include <bitset>

namespace color_chart::defines {
    using RGB565 = uint16_t;
    constexpr auto NumberOfSubpixels = std::size_t{3};
    using Subpixels = std::array<std::any, NumberOfSubpixels>;
    using RedSubpixel = std::bitset<5>;
    using GreenSubpixel = std::bitset<6>;
    using BlueSubpixel = std::bitset<5>;
    
    enum Component {Red, Green, Blue};
}
namespace color_chart::equations {
    class LinearMix {
        public:
            std::list<defines::RGB565> mix(defines::RGB565 startColor, defines::RGB565 endColor, std::size_t gradientLength);
            defines::Subpixels substractComponentColors(defines::RGB565 color);
            defines::Subpixels calculateNewColor(int pixelNumber, std::size_t gradientLength);
            defines::RGB565 makeRGB565(defines::Subpixels color);

        private:
            defines::Subpixels startComponents{0};
            defines::Subpixels endComponents{0};
    };
}
