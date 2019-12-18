#pragma once

constexpr unsigned int strhash(char const* input)
{
    return *input ?
        static_cast<unsigned int>(*input) + 33 * strhash(input + 1) :
        5381;
}