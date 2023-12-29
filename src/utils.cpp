#include "utils.hpp"

void pad101(std::string &data, unsigned int r){
    const unsigned int remaining = r - (data.length() % r);
    data.append(1, '\x01');
    data.append(remaining-2, '\x00');
    data.append(1, '\x80');
}

// https://stackoverflow.com/a/3382894
std::string string_to_hex(const std::string& input)
{
    static const char hex_digits[] = "0123456789ABCDEF";

    std::string output;
    output.reserve(input.length() * 2);
    for (unsigned char c : input)
    {
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }
    return output;
}
