#include <iostream>
#include <matplot/matplot.h>
#include <filesystem>
#include "headers.h"

void plot_signal(Signal signal) {
    using namespace matplot;

    // Create report directory if it doesn't exist
    std::filesystem::path report_path = std::filesystem::current_path().parent_path() / "raport";
    if (!std::filesystem::exists(report_path)) {
        std::filesystem::create_directory(report_path);
    }

    // Create time vector
    std::vector<double> t(signal.samples.size());
    double dt = (signal.t_end - signal.t_start) / signal.samples.size();
    for(size_t i = 0; i < t.size(); i++) {
        t[i] = i * dt;
    }
    
     double margin = (*std::max_element(signal.samples.begin(), signal.samples.end()) - *std::min_element(signal.samples.begin(), signal.samples.end())) * 0.2;
    //std::cout << "Margin: " << *std::min_element(signal.samples.begin(), signal.samples.end()) << std::endl;
    double y_min = *std::min_element(signal.samples.begin(), signal.samples.end()) - margin;
    double y_max = *std::max_element(signal.samples.begin(), signal.samples.end()) + margin;
    // double y_min = 1.2;
    // double y_max = -1.2;
    // Create plot
    xlim({signal.t_start, signal.t_end});
    ylim({y_min, y_max});
    plot(t, signal.samples);
    xlabel("Time [s]");
    ylabel("Amplitude");
    title("Signal: " + signal.name);
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << signal.f; // ustawi 2 miejsca po przecinku
    // Save plot to raport directory
    std::string filename = (("../raport/"+signal.name+" "+(signal.name=="rdft"?"":(ss.str()+"hz") )+ "_signal.png"));
    std::cout << "Saving plot to: " << filename<< std::endl;
    save(filename);
    show();
}
void plot_fourier(Fourier fourier) {
    using namespace matplot;

    // Create report directory if it doesn't exist
    std::filesystem::path report_path = std::filesystem::current_path().parent_path() / "raport";
    if (!std::filesystem::exists(report_path)) {
        std::filesystem::create_directory(report_path);
    }

    // Create frequency vector based on actual signal sampling
    size_t M  = fourier.X.size();  // liczba próbek
double fs = N;         // częstotliwość próbkowania [Hz]
double df = fs / M;            // odstęp między kolejnymi binami częstotliwości [Hz]

// Wyświetlamy tylko "pozytywną" połowę widma (do Nyquista)
size_t H = M/2 + 1;            // liczba binów w rfft
std::vector<double> f(H), magnitude(H);

for (size_t k = 0; k < H; ++k) {
    // oś częstotliwości w [Hz]
    f[k] = k * df;

    // amplituda – standardowo skalujemy przez 2/M, żeby mieć
    // rzeczywiste wartości z dziedziny czasu
    magnitude[k] = 2.0 * std::abs(fourier.X[k]) / M;

    // jeżeli wolisz widmo mocy:
    // magnitude[k] = std::norm(fourier.X[k]) / M;
}

// potem:

xlim({0, *std::max_element(f.begin(),f.end())* 1.2});
ylim({0, *std::max_element(magnitude.begin(), magnitude.end()) * 1.2});
plot(f, magnitude);
xlabel("Frequency [Hz]");
ylabel("Magnitude");
title("Fourier Transform");
    
//*std::max_element(magnitude.begin(), magnitude.end()) * 1.2}
    // Create plot
    
    //nadpisanie maina
    // Save plot to raport directory
    std::string filename = (("../raport/Fourier_transform.png"));
    std::cout << "Saving plot to: " << filename << std::endl;
    save(filename);
    show();
}