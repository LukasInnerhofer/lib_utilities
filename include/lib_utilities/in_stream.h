#pragma once

#include <istream>
#include <memory>
#include <vector>

namespace LibUtilities
{
    template <typename T>
    class InStream
    {
    public:
        InStream(std::shared_ptr<std::basic_istream<T>> stream) :
            m_stream{stream}
        {
            if (!*m_stream)
            {
                throw std::invalid_argument{
                    "LibUtilities::InStream Error. Cannot construct InStream from invalid basic_istream"};
            }
        }

        std::vector<T> readAll()
        {
            m_stream->seekg(0, m_stream->end);
            int64_t const end{m_stream->tellg()};
            m_stream->seekg(0, m_stream->beg);
            
            if (end < 0)
            {
                std::vector<T> data;
                T element;
                while (m_stream->read(&element, 1))
                {
                    data.push_back(element);
                }
                return data;
            }
            else
            {
                std::vector<T> data{static_cast<size_t>(end), 0, std::allocator<T>{}};
                m_stream->read(&*data.begin(), data.size());
                return data;
            }
        }

    private:
        std::shared_ptr<std::basic_istream<T>> m_stream;
    };

}
