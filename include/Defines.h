#pragma once

#include <cstdint>
#include <array>
#include <any>
#include <bitset>
#include <list>

namespace color_chart::defines {
    using RGB565 = uint16_t;
    constexpr auto NumberOfSubpixels = std::size_t{3};
    using Subpixels = std::array<std::any, NumberOfSubpixels>;
    using RedSubpixel = std::bitset<5>;
    using GreenSubpixel = std::bitset<6>;
    using BlueSubpixel = std::bitset<5>;
    using OneLineGradient = std::list<RGB565>;
    
    enum Component {Red, Green, Blue};
}
