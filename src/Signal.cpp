#include "headers.h"
#include <iostream>
#include <vector>
#include <string>

    Signal::Signal(double frequency, double faze, std::string signal_name) 
        : f(frequency), name(signal_name) {
        samples = generate(f, faze, name);
    }
    Signal::Signal( std::string signal_name,const Fourier& transformata)
        : name(signal_name)
         {
         samples=idft(transformata);
        if (samples.empty()) {
            std::cout << "Warning: Samples vector is empty. Signal will not be generated." << std::endl;
        }
    
    }
    Signal::Signal(Signal signal1, Signal signal2)
        : name(signal1.name + " + " + signal2.name) {
        
        samples = addsignals(signal1, signal2);
    }
    Signal::~Signal(){
        std::cout << "Signal destructor called for " << name << std::endl;
    }
