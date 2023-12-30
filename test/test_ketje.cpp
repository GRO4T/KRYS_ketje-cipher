#include <gtest/gtest.h>

#include "monkeyduplex.hpp"
#include "utils.hpp"

#include <monkey.h>
#include <Keccak-f.h>

TEST(TestKetje, TestMonkeyDuplex){
    Krys::MonkeyDuplex md = Krys::MonkeyDuplex(20, 10, 1, 10);
    md.start(BitString("1234"));
    BitString x_step = md.step(BitString("xy"), 16);
    BitString x_stride = md.stride(BitString("xy"), 16);

    IterableTransformation<KeccakPStar> f(200);
    MonkeyDuplex md_ref = MonkeyDuplex(f, 20, 10, 1, 10);
    md_ref.start(BitString("1234"));
    BitString x_step_ref = md_ref.step(BitString("xy"), 16);
    BitString x_stride_ref = md_ref.stride(BitString("xy"), 16);
    EXPECT_EQ(x_step, x_step_ref);
    EXPECT_EQ(x_stride, x_stride_ref);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
