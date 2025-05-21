#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <vector>
#include <cstdint>

struct TableAValues
{
    std::vector<int32_t> b, c;
};

struct TableBValues
{
    std::vector<int32_t> b, c;
};

struct TableAColumn
{
    int32_t a;
    int32_t b;
    int32_t c;
};

struct TableBColumn
{
    int32_t a;
    int32_t b;
    int32_t c;
};

#endif