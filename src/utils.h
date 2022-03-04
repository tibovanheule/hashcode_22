#pragma once
#include <string>
#include <iostream>
using namespace std;

void print(std::string string);
void println(std::string string);
void write_file(std::string algorithm, std::string dataset, int expected,
                     int actual, double time);