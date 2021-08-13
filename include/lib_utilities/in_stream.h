#pragma once

#include <istream>
#include <vector>

namespace LibUtilities
{
    template <typename T>
    class InStream : public std::basic_istream<T>
    {
    public:
        std::vector<T> readAll()
        {
            seekg(std::ios::end);
            pos_type const end{tellg()};
            
            std::vector<T> data{end, 0, std::allocator<T>{}};

            return data;
        }
    };

}
