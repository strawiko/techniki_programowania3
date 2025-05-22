#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include "headers.h"

std::vector<std::complex<double>> dft(const std::vector<double>& samples) {

    std::vector<std::complex<double>> X(samples.size());
    const double scale = 1.0 / std::sqrt(samples.size());
    
    for (int k = 0; k < samples.size(); k++) {
        X[k] = std::complex<double>(0.0, 0.0);
        for (int n = 0; n < samples.size(); n++) {
            double angle = 2.0 * PI * k * n / samples.size();
            double real = std::cos(angle);
            double imag = -std::sin(angle);
            X[k] += samples[n] * std::complex<double>(real, imag);
        }
        X[k] *= scale;  // Normalization
    }
    
    return X;
}