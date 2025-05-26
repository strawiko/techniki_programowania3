#include "headers.h"
#include <iostream>
#include <vector>
#include <string>

    
    Fourier::Fourier(const Signal& signal) {
        X = dft(signal);
        t_start = signal.t_start;
        t_end = signal.t_end;
    }

    Fourier::~Fourier() {
        std::cout << "Fourier destructor called for Fourier transform" << std::endl;
    }
