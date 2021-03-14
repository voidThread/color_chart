#include "LinearMix.h"
#include <bitset>
#include <array>
#include <any>

using namespace color_chart;

std::list<defines::RGB565> equations::LinearMix::mix(defines::RGB565 startColor, 
        defines::RGB565 endColor, std::size_t gradientLength) {
    std::size_t minimalGradientLength{3};
    if (gradientLength < minimalGradientLength) {
        return std::list{startColor, endColor};
    }

    std::list<defines::RGB565> gradient{startColor};

    auto startComponents = substractComponentColors(startColor);
    auto endComponents = substractComponentColors(endColor);
    
    for (std::size_t x{1}; x < gradientLength; x++) {

   //     auto redSubpixel = startRed + 
    //        (x / (gradientLength-1) * (endRed.to_ulong() - startRed.to_ulong()));
        //startColor[subpixel] + 
        //((x) / (gradientLength-1) * (endColor[subpixel] - startColor[subpixel]))
        gradient.emplace_back(defines::RGB565(x));
    }

    return gradient;
}

defines::Subpixels equations::LinearMix::substractComponentColors(defines::RGB565 color)
{ 
    uint16_t redMask{0xf800};
    uint16_t greenMask{0x07e0};
    uint16_t blueMask{0x001f};

    defines::RedSubpixel red((color & redMask) >> 11);
    defines::GreenSubpixel green((color & greenMask) >> 5);
    defines::BlueSubpixel blue(color & blueMask);

    return defines::Subpixels{red, green, blue};
}
