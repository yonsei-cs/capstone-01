#ifndef COLUMNS_HPP // 이전 INDEXING_HPP에서 변경
#define COLUMNS_HPP

#include <vector>
#include <fstream>
#include "structs.hpp"

// 헤더 파일에서는 'using namespace std;' 사용을 지양하는 것이 좋습니다.
// 필요하다면 cpp 파일 내에서 사용하거나 std:: 접두사를 명시합니다.

bool get_filtered_table_map_based(
    std::ifstream &table_a_stream,
    std::ifstream &table_b_stream,
    long long int A_a_condition,
    long long int B_a_condition,
    std::vector<TableAColumn> &filtered_table_a,
    std::vector<TableBColumn> &filtered_table_b,
    size_t &filtered_table_a_size,
    size_t &filtered_table_b_size);

bool get_filtered_table_direct_filter(
    std::ifstream &table_a_stream,
    std::ifstream &table_b_stream,
    long long int A_a_condition,
    long long int B_a_condition,
    std::vector<TableAColumn> &filtered_table_a,
    std::vector<TableBColumn> &filtered_table_b,
    size_t &filtered_table_a_size,
    size_t &filtered_table_b_size);

#endif // COLUMNS_HPP