#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <fstream>
using std::ifstream;
using std::string;

bool input_condition(long long int &a, long long int &b);
bool input_tables(string &table_a_file_name, string &table_b_file_name);
bool get_file_stream(
    string table_a_file_name,
    string table_b_file_name,
    ifstream &table_a,
    ifstream &table_b);

#endif