#include "LinearMix.h"
#include <bitset>
#include <array>
#include <any>

using namespace color_chart;

std::list<defines::RGB565> equations::LinearMix::mix(defines::RGB565 startColor, 
        defines::RGB565 endColor, std::size_t gradientLenght) {
    std::size_t minimalGradientLength{3};
    if (gradientLenght < minimalGradientLength) {
        return std::list{startColor, endColor};
    }

    std::list<defines::RGB565> gradient{startColor};

    startComponents = substractComponentColors(startColor);
    endComponents = substractComponentColors(endColor);
    
    for (std::size_t x{1}; x < gradientLenght; x++) {
        gradient.emplace_back(makeRGB565(calculateNewColor(x, gradientLenght)));
    }

    return gradient;
}

defines::Subpixels equations::LinearMix::substractComponentColors(defines::RGB565 color)
{ 
    const uint16_t redMask{0xf800};
    const uint16_t greenMask{0x07e0};
    const uint16_t blueMask{0x001f};

    defines::RedSubpixel red((color & redMask) >> 11);
    defines::GreenSubpixel green((color & greenMask) >> 5);
    defines::BlueSubpixel blue(color & blueMask);

    return defines::Subpixels{red, green, blue};
}

defines::Subpixels equations::LinearMix::calculateNewColor(int pixelNumber, std::size_t gradientLength)
{
/*    for (std::size_t subpixel{defines::Component::Red}; subpixel <= defines::Component::Blue; subpixel++) {
        auto newSubpixel = startComponents[subpixel] + (pixelNumber / (gradientLength-1) * 
         (std::any_cast<endComponents[subpixel].to_ulong() - startComponents[subpixel].to_ulong());
    }*/
    auto redNewSubpixel = std::any_cast<defines::RedSubpixel>(startComponents[defines::Component::Red]).to_ulong() + 
        (pixelNumber / (gradientLength-1) * 
     (std::any_cast<defines::RedSubpixel>(endComponents[defines::Component::Red]).to_ulong() - 
      std::any_cast<defines::RedSubpixel>(startComponents[defines::Component::Red]).to_ulong()));

    auto greenNewSubpixel = std::any_cast<defines::GreenSubpixel>(startComponents[defines::Component::Green]).to_ulong() + 
        (pixelNumber / (gradientLength-1) * 
     (std::any_cast<defines::GreenSubpixel>(endComponents[defines::Component::Green]).to_ulong() - 
      std::any_cast<defines::GreenSubpixel>(startComponents[defines::Component::Green]).to_ulong()));

    auto blueNewSubpixel = std::any_cast<defines::BlueSubpixel>(startComponents[defines::Component::Blue]).to_ulong() + 
        (pixelNumber / (gradientLength-1) * 
     (std::any_cast<defines::BlueSubpixel>(endComponents[defines::Component::Blue]).to_ulong() - 
      std::any_cast<defines::BlueSubpixel>(startComponents[defines::Component::Blue]).to_ulong()));

     return defines::Subpixels{redNewSubpixel, greenNewSubpixel, blueNewSubpixel};
}

defines::RGB565 equations::LinearMix::makeRGB565(defines::Subpixels color) {
    return defines::RGB565{0};
}
