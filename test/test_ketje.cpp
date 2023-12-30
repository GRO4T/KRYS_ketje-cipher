#include <gtest/gtest.h>


#include "monkeyduplex.hpp"
#include "utils.hpp"


TEST(TestKetje, TestPadding)
{
    // Arrange
    std::string data = "1234";
    const std::string expected_output = "31 32 33 34 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 80";
    // Act
    pad101(data, 25);
    // Assert
    EXPECT_EQ(format_hex(data), expected_output);
}

TEST(TestKetje, TestMonkeyDuplex){
    MonkeyDuplex md = MonkeyDuplex(20, 10, 1, 10);
    md.start(BitString("1234"));
    BitString x = md.step(BitString("xy"), 16);
    BitString expected = BitString("\x06\xc7");
    EXPECT_EQ(x, expected);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
