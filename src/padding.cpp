#include "padding.h"

void pad101(std::string &data, unsigned int r){
    const unsigned int remaining = r - (data.length() % r);
    data.append(1, '\x01');
    data.append(remaining-2, '\x00');
    data.append(1, '\x80');
}
