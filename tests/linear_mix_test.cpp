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
