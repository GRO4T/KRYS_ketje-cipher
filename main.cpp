#include "monkeyduplex.hpp"

int main(void) {
    Krys::MonkeyDuplex md = Krys::MonkeyDuplex(20, 10, 1, 10);
    md.start(BitString("1234"));
    BitString x = md.step(BitString("xy"), 16);
    std::cout << x << endl;
}
