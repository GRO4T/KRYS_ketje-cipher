#include <gtest/gtest.h>

#include "utils.hpp"


TEST(TestKetje, TestPadding)
{
    // Arrange
    std::string data = "1234";
    const std::string expected_output = "31323334010000000000000000000000000000000000000080";
    // Act
    pad101(data, 25);
    // Assert
    EXPECT_EQ(format_hex(data), expected_output);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
