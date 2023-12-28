#pragma once

#include <string>


/*
 * Pads the given string in-place, so that it is aligned to the desired size `r` and ends with a one, sequence of zeros, and a one.
 * Note that the alignment is given in bytes, not bits.
 */
void pad101(std::string &data, unsigned int r);

std::string string_to_hex(const std::string& input);