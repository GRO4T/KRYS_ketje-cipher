#pragma once

#include <string>
#include <cstdint>


/*
 * Pads the given string in-place, so that it is aligned to the desired size `r` and ends with a one, sequence of zeros, and a one.
 * Note that the alignment is given in bytes, not bits.
 */
void pad101(std::string &data, unsigned int r);

std::string format_hex(const uint8_t *input, size_t n);
std::string format_hex(const std::string& input);
