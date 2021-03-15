#include <gtest/gtest.h>
#include "ScreenBuffer.h"

class ScreenBufferTest : public ::testing::Test
{
    protected:
        color_chart::screen::ScreenBuffer screenBuffer{16,9};
};

TEST_F(ScreenBufferTest, ScreenBufferFiledWithOneLineGradient) {
    //Arrange
    using namespace color_chart;
    screen::CornersColors twoCorners{0x0000, 0xffff};
    screenBuffer.setCornerColors(twoCorners);

    //Act
    auto buffer = screenBuffer.getScreen();

    //Assert
    ASSERT_EQ(buffer.size(), 9);
    ASSERT_EQ(buffer.front().size(), 16);
    ASSERT_EQ(buffer.front().back(), buffer.back().back());
    ASSERT_EQ(buffer.front().front(), buffer.back().front());
}

TEST_F(ScreenBufferTest, ScreenBufferFiledWithOneLineGradientInvertedColors) {
    //Arrange
    using namespace color_chart;
    screen::CornersColors twoCorners{0xffff, 0x0000};
    screenBuffer.setCornerColors(twoCorners);

    //Act
    auto buffer = screenBuffer.getScreen();

    //Assert
    ASSERT_EQ(buffer.size(), 9);
    ASSERT_EQ(buffer.front().size(), 16);
    ASSERT_EQ(buffer.front().back(), buffer.back().back());
    ASSERT_EQ(buffer.front().front(), buffer.back().front());
}
