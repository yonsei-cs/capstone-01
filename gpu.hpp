#ifndef GPU_HPP
#define GPU_HPP

#include <vector>
#include "structs.hpp"

// 예시 함수 선언: (실제 연산에 맞게 파라미터 수정)
bool run_gpu_query(
    const std::vector<TableAColumn> &table_a,
    const std::vector<TableBColumn> &table_b);

#endif