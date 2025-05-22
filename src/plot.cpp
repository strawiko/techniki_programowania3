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

    // Create plot
    plot(t, signal.samples);
    xlabel("Time [s]");
    ylabel("Amplitude");
    title("Signal: " + signal.name);
    
    // Save plot to raport directory
    std::string filename = (("../raport/"+signal.name + "_signal.png"));
    std::cout << "Saving plot to: " << filename << std::endl;
    save(filename);
    show();
}