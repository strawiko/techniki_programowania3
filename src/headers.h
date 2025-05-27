#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <complex>
//deklaracje wszsytkiego
class Signal;  
class Fourier;
std::vector<double> generate(double f, double t_start, double t_end, std::string name);

std::vector<std::complex<double>> dft(Signal signal);

std::vector<double> idft(Fourier fourier);
constexpr double PI = 3.14159265358979323846; //absurdalnie dużo cyfr liczby pi
constexpr int N = 100;  // ilość próbek na sekundę

class Signal { //używane do generowania sygnałów
public:
    double f; //częstotliwość
    double t_start;
    double t_end;
    std::string name;
    std::vector<double> samples;
    //nadpisywanie maina

    Signal(double frequency, double start, double end, std::string signal_name) ;
        
    Signal( double start, double end, std::string signal_name,const Fourier& transformata);

    ~Signal();
};
class Fourier { //używane do transformacji w obie strony
public:
    std::vector<std::complex<double>> X;
    double t_start;
    double t_end;
    Fourier(const Signal& signal);

    ~Fourier() ;
};

void plot_signal(Signal signal);  //rysowanie
void plot_fourier(Fourier fourier);  