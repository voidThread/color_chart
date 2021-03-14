#pragma once

#include <cstdint>
#include <list>
#include <array>
#include <any>
#include <bitset>

namespace color_chart::defines {
    using RGB565 = uint16_t;
    using Subpixels = std::array<std::any, 3>;
    using RedSubpixel = std::bitset<5>;
    using GreenSubpixel = std::bitset<6>;
    using BlueSubpixel = std::bitset<5>;
}
namespace color_chart::equations {
    class LinearMix {
        public:
            std::list<defines::RGB565> mix(defines::RGB565 startColor, defines::RGB565 endColor, std::size_t gradientLength);
            std::array<std::any, 3> substractComponentColors(defines::RGB565 color);
    };
}
