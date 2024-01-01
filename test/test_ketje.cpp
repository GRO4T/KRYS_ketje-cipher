#include <stdexcept>
#include <gtest/gtest.h>

#include "monkeyduplex.hpp"
#include "monkeywrap.hpp"
#include "utils.hpp"

#include "monkey.h"
#include "Keccak-f.h"
#include "Ketjev2.h"

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

TEST(TestKetje, TestMonkeyWrap) {
    std::string K = "1234";
    std::string N = "5678";
    std::string A = "abc";
    std::string B = "def";
    uint ell = 8;

    Krys::MonkeyWrap mw(16, 12, 1, 6);
    mw.initialize(BitString(K), BitString(N));
    auto [C, T] = mw.wrap(BitString(A), BitString(B), ell);

    // KetjeJr ketje;
    // ketje.initialize(K, N);
    // std::string T_ref;
    // auto C_ref = ketje.wrap(A, B, ell, T_ref);

    // EXPECT_EQ(C, BitString(C_ref));
    // EXPECT_EQ(T, BitString(T_ref));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
