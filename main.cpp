#include "utils.hpp"
#include "columns.hpp" // columns.hpp 먼저 include (structs.hpp 의존성)

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono> // 시간 측정을 위해 chrono 헤더 추가

// using namespace std; // main 함수 내에서 std:: 명시 또는 using 선언

int main()
{
    long long int a_condition, b_condition;
    std::string table_a_file_name, table_b_file_name;
    std::ifstream table_a_stream, table_b_stream;

    input_condition(a_condition, b_condition);
    input_tables(table_a_file_name, table_b_file_name);

    bool file_open_result = get_file_stream(table_a_file_name, table_b_file_name, table_a_stream, table_b_stream);
    if (!file_open_result)
    {
        std::cerr << "Failed to open table files." << std::endl;
        return 1;
    }

    std::cout << "\n--- Input Conditions ---" << std::endl;
    std::cout << "A.a condition: " << a_condition << std::endl;
    std::cout << "B.a condition: " << b_condition << std::endl;
    std::cout << "Table A file: " << table_a_file_name << std::endl;
    std::cout << "Table B file: " << table_b_file_name << std::endl;
    std::cout << "------------------------" << std::endl;

    // 결과 저장을 위한 변수들
    std::vector<TableAColumn> filtered_table_a_map, filtered_table_a_direct;
    std::vector<TableBColumn> filtered_table_b_map, filtered_table_b_direct;
    size_t filtered_table_a_size_map, filtered_table_b_size_map;
    size_t filtered_table_a_size_direct, filtered_table_b_size_direct;

    // --- 방법 1: 맵 기반 필터링 시간 측정 ---
    std::cout << "\n--- Testing Map-based Filtering ---" << std::endl;
    auto start_map = std::chrono::high_resolution_clock::now();

    // 파일 스트림은 각 process 함수 내부에서 rewind 됩니다.
    if (!get_filtered_table_map_based(table_a_stream, table_b_stream, a_condition, b_condition,
                                      filtered_table_a_map, filtered_table_b_map,
                                      filtered_table_a_size_map, filtered_table_b_size_map))
    {
        std::cerr << "Error in get_filtered_table_map_based" << std::endl;
        table_a_stream.close();
        table_b_stream.close();
        return 1;
    }
    auto end_map = std::chrono::high_resolution_clock::now();
    auto duration_map = std::chrono::duration_cast<std::chrono::microseconds>(end_map - start_map);

    std::cout << "Map-based: filtered_table_a_size: " << filtered_table_a_size_map << std::endl;
    std::cout << "Map-based: filtered_table_b_size: " << filtered_table_b_size_map << std::endl;
    std::cout << "Map-based: Time taken: " << duration_map.count() << " microseconds" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    // --- 방법 2: 직접 필터링 시간 측정 ---
    std::cout << "\n--- Testing Direct Filtering ---" << std::endl;
    auto start_direct = std::chrono::high_resolution_clock::now();

    // 파일 스트림은 각 process 함수 내부에서 rewind 됩니다.
    if (!get_filtered_table_direct_filter(table_a_stream, table_b_stream, a_condition, b_condition,
                                          filtered_table_a_direct, filtered_table_b_direct,
                                          filtered_table_a_size_direct, filtered_table_b_size_direct))
    {
        std::cerr << "Error in get_filtered_table_direct_filter" << std::endl;
        table_a_stream.close();
        table_b_stream.close();
        return 1;
    }
    auto end_direct = std::chrono::high_resolution_clock::now();
    auto duration_direct = std::chrono::duration_cast<std::chrono::microseconds>(end_direct - start_direct);

    std::cout << "Direct Filter: filtered_table_a_size: " << filtered_table_a_size_direct << std::endl;
    std::cout << "Direct Filter: filtered_table_b_size: " << filtered_table_b_size_direct << std::endl;
    std::cout << "Direct Filter: Time taken: " << duration_direct.count() << " microseconds" << std::endl;
    std::cout << "------------------------------" << std::endl;

    // 파일 스트림 닫기
    table_a_stream.close();
    table_b_stream.close();

    return 0;
}