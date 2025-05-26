#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <complex>

// #define PI 3.14159265358979323846
// #define N 1000
class Signal;  // Forward declaration of Signal class
class Fourier;
// Forward declaration of generate function
std::vector<double> generate(double f, double t_start, double t_end, std::string name);

// Forward declaration of dft function
std::vector<std::complex<double>> dft(Signal signal);

// Forward declaration of idft function
std::vector<double> idft(Fourier fourier);
constexpr double PI = 3.14159265358979323846;
constexpr int N = 1000;  // Sample size for signal generation

class Signal {
public:
    double f;
    double t_start;
    double t_end;
    std::string name;
    std::vector<double> samples;
    //nadpisywanie maina

    Signal(double frequency, double start, double end, std::string signal_name) ;
        
    Signal( double start, double end, std::string signal_name,const Fourier& transformata);

    ~Signal();
};
class Fourier {
public:
    std::vector<std::complex<double>> X;
    double t_start;
    double t_end;
    Fourier(const Signal& signal);

    ~Fourier() ;
};

void plot_signal(Signal signal);  // Add this declaration
void plot_fourier(Fourier fourier);  // Add this declaration