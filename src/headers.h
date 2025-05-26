#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <complex>

#define PI 3.14159265358979323846
#define N 1000
class Signal;  // Forward declaration of Signal class

// Forward declaration of generate function
std::vector<double> generate(double f, double t_start, double t_end, std::string name);

// Forward declaration of dft function
std::vector<std::complex<double>> dft(Signal signal);

// Forward declaration of idft function
std::vector<double> idft(const std::vector<std::complex<double>>& X);

class Signal {
public:
    double f;
    double t_start;
    double t_end;
    std::string name;
    std::vector<double> samples;

    Signal(double frequency, double start, double end, std::string signal_name) 
        : f(frequency), t_start(start), t_end(end), name(signal_name) {
        samples = generate(f, t_start, t_end, name);
    }
    ~Signal(){
        std::cout << "Signal destructor called for " << name << std::endl;
    };
};
class Fourier {
public:
    std::vector<std::complex<double>> X;
    double t_start;
    double t_end;
    Fourier(Signal signal) {
        X = dft(signal);
        t_start = signal.t_start;
        t_end = signal.t_end;
    }

    ~Fourier() {
        std::cout << "Fourier destructor called for Fourier transform" << std::endl;
    }
};

void plot_signal(Signal signal);  // Add this declaration
void plot_fourier(Fourier fourier);  // Add this declaration