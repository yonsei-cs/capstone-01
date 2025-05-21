#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
bool input_condition(long long int &a, long long int &b)
{
    cout << "SELECT * FROM A, B" << endl;
    cout << "\tWHERE A.a=";
    cin >> a;
    cout << "\tAND B.a=";
    cin >> b;
    cout << "\tAND A.b=B.b" << endl;
    return true;
}

bool input_tables(string &table_a_file_name, string &table_b_file_name)
{
    cout << "A 테이블이 저장되어 있는 파일의 경로를 입력하세요: ";
    cin >> table_a_file_name;
    cout << "B 테이블이 저장되어 있는 파일의 경로를 입력하세요: ";
    cin >> table_b_file_name;
    return true;
}

bool get_file_stream(string table_a_file_name, string table_b_file_name, ifstream &table_a, ifstream &table_b)
{
    table_a.open(table_a_file_name);
    if (!table_a.is_open())
    {
        cout << table_a_file_name << " 파일을 열지 못했습니다." << endl;
        return false;
    }
    table_b.open(table_b_file_name);
    if (!table_b.is_open())
    {
        cout << table_b_file_name << " 파일을 열지 못했습니다." << endl;
        return false;
    }
    return true;
}