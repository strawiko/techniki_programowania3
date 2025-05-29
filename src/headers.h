#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <complex>

//deklaracje wszsytkiego
class Signal;  
class Fourier;
std::vector<double> generate(double f, double t_start,std::string name);
std::vector<double> addsignals(Signal signal1, Signal signal2); //dodawanie sygnałów
std::vector<std::complex<double>> dft(Signal signal);
std::vector<double> idft(Fourier fourier);
Signal filter(Signal signal, double cutoff_hz); //filtracja sygnału
constexpr double PI = 3.14159265358979323846; //absurdalnie dużo cyfr liczby pi
constexpr int N = 100;  // ilość próbek na sekundę
constexpr double T=5.0;
class Signal { //używane do generowania sygnałów
public:
    double f; //częstotliwość
    std::string name;
    std::vector<double> samples;
    //nadpisywanie maina

    Signal(double frequency, double faza, std::string signal_name) ;
        
    Signal( std::string signal_name,const Fourier& transformata);
    Signal(Signal signal1, Signal signal2);

    ~Signal();
};
class Fourier { //używane do transformacji w obie strony
public:
    std::vector<std::complex<double>> X;
    Fourier(const Signal& signal);

    ~Fourier() ;
};

void plot_signal(Signal signal);  //rysowanie
void plot_fourier(Fourier fourier);  