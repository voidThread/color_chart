#include <gtest/gtest.h>
#include "LinearMix.h"

class LinearMixTest : public ::testing::Test
{
    protected:
        color_chart::equations::LinearMix  linearMix;
};

TEST_F(LinearMixTest, GetComponentsFromRedColor)
{
    //Arrange
    using namespace color_chart;
    defines::RGB565 color{0xf800};

    //Act
    auto components = linearMix.substractComponentColors(color);

    //Assert
    ASSERT_EQ(std::any_cast<defines::RedSubpixel>(components[defines::Component::Red]), 0x1f);
    ASSERT_EQ(std::any_cast<defines::GreenSubpixel>(components[defines::Component::Green]), 0x00);
    ASSERT_EQ(std::any_cast<defines::BlueSubpixel>(components[defines::Component::Blue]), 0x00);
}

TEST_F(LinearMixTest, GetComponentsFromGreenColor)
{
    //Arrange
    using namespace color_chart;
    defines::RGB565 color{0x07e0};

    //Act
    auto components = linearMix.substractComponentColors(color);

    //Assert
    ASSERT_EQ(std::any_cast<defines::RedSubpixel>(components[defines::Component::Red]), 0x00);
    ASSERT_EQ(std::any_cast<defines::GreenSubpixel>(components[defines::Component::Green]), 0x3f);
    ASSERT_EQ(std::any_cast<defines::BlueSubpixel>(components[defines::Component::Blue]), 0x00);
}

TEST_F(LinearMixTest, GetComponentsFromBlueColor)
{
    //Arrange
    using namespace color_chart;
    defines::RGB565 color{0x001f};

    //Act
    auto components = linearMix.substractComponentColors(color);

    //Assert
    ASSERT_EQ(std::any_cast<defines::RedSubpixel>(components[defines::Component::Red]), 0x00);
    ASSERT_EQ(std::any_cast<defines::GreenSubpixel>(components[defines::Component::Green]), 0x00);
    ASSERT_EQ(std::any_cast<defines::BlueSubpixel>(components[defines::Component::Blue]), 0x1f);
}

TEST_F(LinearMixTest, GetComponentsFromBlackColor)
{
    //Arrange
    using namespace color_chart;
    defines::RGB565 color{0xffff};

    //Act
    auto components = linearMix.substractComponentColors(color);

    //Assert
    ASSERT_EQ(std::any_cast<defines::RedSubpixel>(components[defines::Component::Red]), 0x1f);
    ASSERT_EQ(std::any_cast<defines::GreenSubpixel>(components[defines::Component::Green]), 0x3f);
    ASSERT_EQ(std::any_cast<defines::BlueSubpixel>(components[defines::Component::Blue]), 0x1f);
}

TEST_F(LinearMixTest, GetComponentsFromWhiteColor)
{
    //Arrange
    using namespace color_chart;
    defines::RGB565 color{0x0000};

    //Act
    auto components = linearMix.substractComponentColors(color);

    //Assert
    ASSERT_EQ(std::any_cast<defines::RedSubpixel>(components[defines::Component::Red]), 0x00);
    ASSERT_EQ(std::any_cast<defines::GreenSubpixel>(components[defines::Component::Green]), 0x00);
    ASSERT_EQ(std::any_cast<defines::BlueSubpixel>(components[defines::Component::Blue]), 0x00);
}

TEST_F(LinearMixTest, LengthGradientLessThenThreeReturnListWithColorsProvidedInParameters) {
    //Arrange
    using namespace color_chart;
    defines::RGB565 blackColor{0x0000};
    defines::RGB565 whiteColor{0xFFFF};
    std::size_t gradientLength{2};

    //Act
    auto gradient = linearMix.mix(blackColor, whiteColor, gradientLength);

    //Assert
    ASSERT_EQ(gradient.size(), gradientLength);
    ASSERT_EQ(gradient.front(), blackColor);
    ASSERT_EQ(gradient.back(), whiteColor);
}

TEST_F(LinearMixTest, LengthGradientGraterThenThreeReturnListWithSizeEqualLenght) {
    using namespace color_chart;
    //Arrange
    defines::RGB565 blackColor{0x0000};
    defines::RGB565 whiteColor{0xFFFF};
    std::size_t gradientLength{4};

    //Act
    auto gradient = linearMix.mix(blackColor, whiteColor, gradientLength);

    //Assert
    ASSERT_EQ(gradient.size(), gradientLength);
}

TEST_F(LinearMixTest, CalculateMidleBetweenTwoColorsReturnOneAdditional) {
    //Arrange
    using namespace color_chart;
    defines::RGB565 blackColor{0x0000};
    defines::RGB565 whiteColor{0xffff};
    std::size_t gradientLength{3};
    
    //Act
    auto gradient = linearMix.mix(blackColor, whiteColor, gradientLength);

    //Assert
    ASSERT_EQ(gradient.front(), blackColor);
    ASSERT_EQ(*std::next(gradient.begin()), 0x7BEF);
    ASSERT_EQ(gradient.back(), whiteColor);
}

TEST_F(LinearMixTest, CalculateMidleBetweenTwoColorsInvertedReturnOneAdditional) {
    //Arrange
    using namespace color_chart;
    defines::RGB565 blackColor{0x0000};
    defines::RGB565 whiteColor{0xffff};
    std::size_t gradientLength{3};
    
    //Act
    auto gradient = linearMix.mix(whiteColor, blackColor, gradientLength);

    //Assert
//    ASSERT_EQ(gradient.front(), whiteColor);
    ASSERT_EQ(*std::next(gradient.begin()), 0x7BEF);
//    ASSERT_EQ(gradient.back(), blackColor);
}

TEST_F(LinearMixTest, ConvertSubpixelsToRGB565) {
    //Arrange
    using namespace color_chart;
    defines::Subpixels whiteColor{defines::RedSubpixel{0x1f}, defines::GreenSubpixel{0x3f},
    defines::BlueSubpixel{0x1f}};

    //Act
    auto rgbColor = linearMix.makeRGB565(whiteColor);

    //Assert
    ASSERT_EQ(rgbColor, 0xffff);
}
