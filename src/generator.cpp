#include <iostream>
#include "headers.h"
#include <vector>
#include <string>
#include <cmath>


std::vector<double> generate(double f, double t_start, double t_end, std::string name) {
    int sf = N;  // częstotliwość próbkowania (liczba próbek na sekundę)
    int n = N * (t_end - t_start);  // łączna ilość próbek
    
    if (n <= 0) {
        std::cout << "Error: t_end must be greater than t_start." << std::endl;//kontrola
        return {};
    }

    std::vector<double> signal(n); //wektor sygnałowy
    if (f <= 0) {
        std::cout << "Error: Frequency must be greater than zero." << std::endl; //kontrola
        return {};
    }
    
    if (name == "sin") {
        for (int i = 0; i < n; i++) {
            signal[i] = sin(2 * PI * f * i / sf);
        }
    }
    else if (name == "cos") {
        for (int i = 0; i < n; i++) {
            signal[i] = cos(2 * PI * f * i / sf);
        }
    }
    else if (name == "kwadrat") {
        for (int i = 0; i < n; i++) {
            signal[i] = (sin(2 * PI * f * i / sf) >= 0) ? 1 : -1;
        }
    }
    else if (name == "pila") {
        for (int i = 0; i < n; i++) {
            double phase = PI * f * i / sf;
            signal[i] = (1/PI) * (phase - PI * floor(phase/PI));//floor zaokrągla wartość do całkowitej
        }
    }
    else {
        std::cout << "Error: Unknown signal type." << std::endl;
        return {};
    }
    
    return signal;
}