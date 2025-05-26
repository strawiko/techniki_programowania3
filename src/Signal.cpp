#include "headers.h"
#include <iostream>
#include <vector>
#include <string>

    Signal::Signal(double frequency, double start, double end, std::string signal_name) 
        : f(frequency), t_start(start), t_end(end), name(signal_name) {
        samples = generate(f, t_start, t_end, name);
    }
    Signal::Signal( double start, double end, std::string signal_name,const Fourier& transformata)
        :  t_start(start), t_end(end), name(signal_name)
         {
         samples=idft(transformata);
        if (samples.empty()) {
            std::cout << "Warning: Samples vector is empty. Signal will not be generated." << std::endl;
        }
    }
    Signal::~Signal(){
        std::cout << "Signal destructor called for " << name << std::endl;
    }
