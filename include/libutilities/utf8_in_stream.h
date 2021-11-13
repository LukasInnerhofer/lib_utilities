#pragma once

#include "libutilities/in_stream.h"
#include <climits>
#include <cuchar>
#include <iostream>
#include <cstring>
#include <iomanip>

namespace LibUtilities
{

class Utf8InStream : public InStream
{
public:
    Utf8InStream(NonNullSharedPtr<std::istream> stream) :
        InStream{stream}
    {
    }

    char32_t get() override
    {
        static char src[MB_LEN_MAX];
        std::memset(src, 0, sizeof(src));
        m_stream->get(src, sizeof(src));
        std::mbstate_t state{0};
        auto const size{std::mbrtoc32(nullptr, src, sizeof(src), &state)};
        if (static_cast<int>(size) < 1)
        {
            // TODO handle conversion error
            return 0;
        }
        char32_t result;
        std::mbrtoc32(&result, src, size, &state);
        return result;
    }
};

}