#include "utils.hpp"

void pad101(std::string &data, unsigned int r){
    const unsigned int remaining = r - (data.length() % r);
    data.append(1, '\x01');
    data.append(remaining-2, '\x00');
    data.append(1, '\x80');
}

// https://stackoverflow.com/a/3382894
std::string format_hex(const uint8_t *input, size_t n)
{
    static const char hex_digits[] = "0123456789ABCDEF";

    std::string output;
    output.reserve(n * 2);
    for (int i=0; i<n; i++)
    {
        uint8_t c = input[i];
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }
    return output;
}

std::string format_hex(const std::string& input){
    return format_hex((uint8_t*) input.c_str(), input.length());
}
