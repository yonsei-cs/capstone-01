#include "columns.hpp"
#include "structs.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std; // cpp 파일에서는 사용 편의를 위해 유지 (전역보다는 함수 스코프가 더 좋음)

// 헬퍼 함수: 맵 기반 필터링 (기존 방식)
template <typename TableColumnType, typename TableValuesType>
bool process_table_file_map_internal( // 이름 변경하여 내부 사용 명시
    std::ifstream &table_stream,
    long long int a_condition_ll,
    std::vector<TableColumnType> &filtered_table,
    size_t &filtered_table_size)
{
    std::map<int32_t, TableValuesType> temp_data_map;
    std::string line;
    int32_t val_a, val_b, val_c;

    table_stream.clear();
    table_stream.seekg(0, std::ios::beg);

    while (std::getline(table_stream, line))
    {
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        std::stringstream ss(line);
        char delimiter_char = 0;

        if (!(ss >> val_a))
            continue;
        if (ss.peek() == ',' || ss.peek() == ' ')
            ss.get(delimiter_char);
        if (!(ss >> val_b))
            continue;
        if (ss.peek() == ',' || ss.peek() == ' ')
            ss.get(delimiter_char);
        if (!(ss >> val_c))
            continue;

        temp_data_map[val_a].b.push_back(val_b);
        temp_data_map[val_a].c.push_back(val_c);
    }

    // cout << "Map-based: temp_data_map.size() for condition " << a_condition_ll << ": " << temp_data_map.size() << endl;

    if (table_stream.bad())
    {
        std::cerr << "Error reading from table stream." << std::endl;
        return false;
    }

    filtered_table.clear();
    auto it_find = temp_data_map.find(static_cast<int32_t>(a_condition_ll)); // 조건 타입을 int32_t로 캐스팅
    if (it_find != temp_data_map.end())
    {
        for (size_t i = 0; i < it_find->second.b.size(); ++i)
        {
            TableColumnType col;
            col.a = static_cast<int32_t>(a_condition_ll);
            col.b = it_find->second.b[i];
            col.c = it_find->second.c[i];
            filtered_table.push_back(col);
            // cout << "Map-based Filtered: (" << col.a << ", " << col.b << ", " << col.c << ")" << endl;
        }
    }
    filtered_table_size = filtered_table.size();
    return true;
}

// 헬퍼 함수: 직접 필터링 (새로운 방식)
template <typename TableColumnType>
bool process_table_file_direct_internal( // 이름 변경하여 내부 사용 명시
    std::ifstream &table_stream,
    long long int a_condition_ll,
    std::vector<TableColumnType> &filtered_table,
    size_t &filtered_table_size)
{
    std::string line;
    int32_t val_a, val_b, val_c;

    table_stream.clear();
    table_stream.seekg(0, std::ios::beg);

    filtered_table.clear();

    while (std::getline(table_stream, line))
    {
        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        std::stringstream ss(line);
        char delimiter_char = 0;

        if (!(ss >> val_a))
            continue;
        if (ss.peek() == ',' || ss.peek() == ' ')
            ss.get(delimiter_char);
        if (!(ss >> val_b))
            continue;
        if (ss.peek() == ',' || ss.peek() == ' ')
            ss.get(delimiter_char);
        if (!(ss >> val_c))
            continue;

        if (val_a == a_condition_ll) // 직접 조건 비교
        {
            TableColumnType col;
            col.a = val_a; // 또는 static_cast<int32_t>(a_condition_ll)
            col.b = val_b;
            col.c = val_c;
            filtered_table.push_back(col);
            // cout << "Direct Filtered: (" << col.a << ", " << col.b << ", " << col.c << ")" << endl;
        }
    }
    if (table_stream.bad())
    {
        std::cerr << "Error reading from table stream." << std::endl;
        return false;
    }
    filtered_table_size = filtered_table.size();
    return true;
}

bool get_filtered_table_map_based(
    std::ifstream &table_a_stream,
    std::ifstream &table_b_stream,
    long long int A_a_condition,
    long long int B_a_condition,
    std::vector<TableAColumn> &filtered_table_a,
    std::vector<TableBColumn> &filtered_table_b,
    size_t &filtered_table_a_size,
    size_t &filtered_table_b_size)
{
    // 테이블 A 처리 (맵 기반)
    if (!process_table_file_map_internal<TableAColumn, TableAValues>(
            table_a_stream, A_a_condition, filtered_table_a, filtered_table_a_size))
    {
        cerr << "Error processing table A (map-based)." << endl;
        return false;
    }

    // 테이블 B 처리 (맵 기반)
    if (!process_table_file_map_internal<TableBColumn, TableBValues>(
            table_b_stream, B_a_condition, filtered_table_b, filtered_table_b_size))
    {
        cerr << "Error processing table B (map-based)." << endl;
        return false;
    }

    return true;
}

bool get_filtered_table_direct_filter(
    std::ifstream &table_a_stream,
    std::ifstream &table_b_stream,
    long long int A_a_condition,
    long long int B_a_condition,
    std::vector<TableAColumn> &filtered_table_a,
    std::vector<TableBColumn> &filtered_table_b,
    size_t &filtered_table_a_size,
    size_t &filtered_table_b_size)
{
    // 테이블 A 처리 (직접 필터링)
    if (!process_table_file_direct_internal<TableAColumn>(
            table_a_stream, A_a_condition, filtered_table_a, filtered_table_a_size))
    {
        cerr << "Error processing table A (direct filter)." << endl;
        return false;
    }

    // 테이블 B 처리 (직접 필터링)
    if (!process_table_file_direct_internal<TableBColumn>(
            table_b_stream, B_a_condition, filtered_table_b, filtered_table_b_size))
    {
        cerr << "Error processing table B (direct filter)." << endl;
        return false;
    }

    return true;
}