#include "monkeyduplex.hpp"

int main(void) {
    MonkeyDuplex md = MonkeyDuplex(10, 10, 1, 10);
    md.start(BitString("1234"));
}
