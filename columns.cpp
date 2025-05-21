#include "columns.hpp"
#include "structs.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

// 단일 테이블 파일을 처리하고 필터링된 데이터를 채우는 헬퍼 함수
template <typename TableColumnType, typename TableValuesType>
bool process_table_file(
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

        // 'a' 파싱
        if (!(ss >> val_a))
        {
            continue;
        }

        // 'a' 뒤의 구분자(콤마 또는 공백) 확인
        if (ss.peek() == ',' || ss.peek() == ' ')
        {
            ss.get(delimiter_char);
        }

        // 'b' 파싱
        if (!(ss >> val_b))
        {
            continue;
        }

        // 'b' 뒤의 구분자(콤마 또는 공백) 확인
        if (ss.peek() == ',' || ss.peek() == ' ')
        {
            ss.get(delimiter_char);
        }

        // 'c' 파싱
        if (!(ss >> val_c))
        {
            continue;
        }

        // 필터 적용: val_a를 a_condition_ll과 비교하기 위해 long long으로 캐스팅
        if (static_cast<long long int>(val_a) == a_condition_ll)
        {
            temp_data_map[val_a].b.push_back(val_b);
            temp_data_map[val_a].c.push_back(val_c);
        }
    }

    cout << "temp_data_map.size() : " << temp_data_map.size() << endl;

    if (table_stream.bad())
    {
        return false;
    }

    filtered_table.clear();
    for (const auto &pair : temp_data_map)
    {
        TableColumnType col;
        col.a = pair.first;       // 'a'는 맵의 키
        col.values = pair.second; // 'values'(b와 c 벡터를 포함)는 맵의 값
        filtered_table.push_back(col);
    }
    filtered_table_size = filtered_table.size();
    return true;
}

bool get_filtered_table(
    std::ifstream &table_a_stream,
    std::ifstream &table_b_stream,
    long long int A_a_condition,
    long long int B_a_condition,
    std::vector<TableAColumn> &filtered_table_a,
    std::vector<TableBColumn> &filtered_table_b,
    size_t &filtered_table_a_size,
    size_t &filtered_table_b_size)
{
    // 테이블 A 처리
    if (!process_table_file<TableAColumn, TableAValues>(
            table_a_stream, A_a_condition, filtered_table_a, filtered_table_a_size))
    {
        return false;
    }

    // 테이블 B 처리
    if (!process_table_file<TableBColumn, TableBValues>(
            table_b_stream, B_a_condition, filtered_table_b, filtered_table_b_size))
    {
        return false;
    }

    return true;
}