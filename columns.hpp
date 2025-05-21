#ifndef INDEXING_HPP
#define INDEXING_HPP

#include <vector>
#include <fstream>
#include "structs.hpp"

using namespace std;

bool get_filtered_table(
    ifstream &table_a,
    ifstream &table_b,
    long long int A_a_condition,
    long long int B_a_condition,
    vector<TableAColumn> &filtered_table_a,
    vector<TableBColumn> &filtered_table_b,
    size_t &filtered_table_a_size,
    size_t &filtered_table_b_size);

#endif