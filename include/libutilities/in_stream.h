#pragma once

#include <istream>
#include <memory>
#include <optional>
#include <vector>

#include "libutilities/non_null.h"

namespace LibUtilities
{

class Utf8InStream;

class InStream
{
public:
    InStream(NonNullSharedPtr<std::istream> stream) :
        m_stream{stream}
    {
        if (!*m_stream)
        {
            throw std::invalid_argument{
                "LibUtilities::InStream Error. Cannot construct InStream from invalid basic_istream"};
        }
    }

    virtual ~InStream() = default;

    std::vector<char> readAll()
    {
        m_stream->seekg(0, m_stream->end);
        int64_t const end{m_stream->tellg()};
        m_stream->seekg(0, m_stream->beg);
        
        if (end < 0)
        {
            std::vector<char> data;
            char element;
            while (m_stream->read(&element, 1))
            {
                data.push_back(element);
            }
            return data;
        }
        else
        {
            std::vector<char> data{static_cast<size_t>(end), 0, std::allocator<char>{}};
            m_stream->read(&*data.begin(), data.size());
            return data;
        }
    }

    virtual char32_t get() = 0;

    static std::optional<NonNullSharedPtr<InStream>> guess(NonNullSharedPtr<std::istream> stream)
    {
        if (!*stream)
        {
            return {};
        }

        stream->seekg(std::ios::beg);
        if (stream->get() != 0) // UTF8 or UTFXX LE
        {
            if (stream->eof() || stream->get() != 0)
            {
                stream->seekg(std::ios::beg);
                return makeNonNullShared<Utf8InStream>(stream);
            }
        }
        else // UTFXX BE
        {

        }
        return {};
    } 

protected:
    NonNullSharedPtr<std::istream> m_stream;
};

}

using LibUtilities::InStream;