#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void print(std::string string) {
#ifdef VERBOSE
    std::cout << string;
#endif
}

void println(std::string string) {
#ifdef VERBOSE
    std::cout << string << std::endl;
#endif
}


void write_file(std::string algorithm, std::string dataset, int expected,
                     int actual, double time) {
    std::ofstream outfile;
    std::string filename = "output";
    outfile.open(filename, std::ofstream::out | std::ofstream::app);
    outfile << dataset << ", " << expected << ", " << actual << ", " << time
            << std::endl;
    outfile.close();
}