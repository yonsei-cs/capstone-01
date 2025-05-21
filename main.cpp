#include "utils.hpp"
#include <iostream>
#include <sqlite3.h>
#include <vector>

#include "columns.hpp"

using namespace std;
int main()
{
    long long int a, b;
    string table_a_file_name, table_b_file_name;
    ifstream table_a, table_b;
    vector<TableAColumn> filtered_table_a;
    vector<TableBColumn> filtered_table_b;
    size_t filtered_table_a_size, filtered_table_b_size;
    input_condition(a, b);
    input_tables(table_a_file_name, table_b_file_name);
    bool file_open_result = get_file_stream(table_a_file_name, table_b_file_name, table_a, table_b);

    if (file_open_result == false)
        return 1;

    cout << "a : " << a << endl;
    cout << "b : " << b << endl;
    cout << "table_a_file_name : " << table_a_file_name << endl;
    cout << "table_b_file_name : " << table_b_file_name << endl;

    if (get_filtered_table(table_a, table_b, a, b, filtered_table_a, filtered_table_b, filtered_table_a_size, filtered_table_b_size) == false)
    {
        cout << "Error in get_filtered_table" << endl;
        return 1;
    }

    cout << "filtered_table_a_size : " << filtered_table_a_size << endl;
    cout << "filtered_table_b_size : " << filtered_table_b_size << endl;
    return 0;
}