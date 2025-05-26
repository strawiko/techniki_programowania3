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
    ylim({y_min, y_max});
    plot(t, signal.samples);
    xlabel("Time [s]");
    ylabel("Amplitude");
    title("Signal: " + signal.name);
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << signal.f; // ustawi 2 miejsca po przecinku
    // Save plot to raport directory
    std::string filename = (("../raport/"+signal.name+" "+(signal.name=="rdft"?(ss.str()+"hz"):"" )+ "_signal.png"));
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

    // Create frequency vector
    std::vector<double> f(fourier.X.size());
    double df = 1.0 / (fourier.t_end - fourier.t_start)/N;
    for(size_t i = 0; i < f.size(); i++) {
        f[i] = i * df;
    }

    // Create magnitude vector
    std::vector<double> magnitude(fourier.X.size());
    for(size_t i = 0; i < fourier.X.size(); i++) {
        magnitude[i] = std::abs(fourier.X[i]);
    }
std::cout<< "to tuuuuuuuuuuuuuFourier transform size: " << fourier.X.size() << std::endl;
    // Create plot
    xlim({0, *std::max_element(f.begin(), f.end()) * 1.2});
    ylim({*std::min_element(magnitude.begin(), magnitude.end()) * 1.2, *std::max_element(magnitude.begin(), magnitude.end()) * 1.2});
    plot(f, magnitude);
    xlabel("Frequency [Hz]");
    ylabel("Magnitude");
    title("Fourier Transform");
    //nadpisanie maina
    // Save plot to raport directory
    std::string filename = (("../raport/Fourier_transform.png"));
    std::cout << "Saving plot to: " << filename << std::endl;
    save(filename);
    show();
}