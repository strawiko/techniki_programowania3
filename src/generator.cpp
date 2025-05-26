#include <iostream>
#include "headers.h"
#include <vector>
#include <string>
#include <cmath>
#define PI 3.14159265358979323846
#define N 1000

std::vector<double> generate(double f, double t_start, double t_end, std::string name) {
    int sf = N * f;
    int n = N * (t_end - t_start)*f;
    
    if (n <= 0) {
        std::cout << "Error: t_end must be greater than t_start." << std::endl;
        return {};
    }

    std::vector<double> signal(n);
    
    if (name == "sin") {
        for (int i = 0; i < n; i++) {
            signal[i] = sin(2 * PI * f * i / sf + t_start);
        }
    }
    else if (name == "cos") {
        for (int i = 0; i < n; i++) {
            signal[i] = cos(2 * PI * f * i / sf + t_start);
        }
    }
    else if (name == "kwadrat") {
        for (int i = 0; i < n; i++) {
            signal[i] = (sin(2 * PI * f * i / sf + t_start) >= 0) ? 1 : -1;
        }
    }
    else if (name == "pila") {
        for (int i = 0; i < n; i++) {
            double phase =  PI * f * i / sf + t_start;
            signal[i] = (1/PI) * (phase - PI * floor(phase/PI));
        }
    }
    else {
        std::cout << "Error: Unknown signal type." << std::endl;
        return {};
    }
    
    return signal;
}