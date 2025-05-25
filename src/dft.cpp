#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include "headers.h"

std::vector<double> dft(Signal signal) {


    std::vector<double> Y;
    std::vector<std::complex<double>> X(signal.samples.size());
    const double scale = 1.0 / std::sqrt(signal.samples.size());
    
    for (int k = 0; k < signal.samples.size(); k++) {
        X[k] = std::complex<double>(0.0, 0.0);
        for (int n = 0; n < signal.samples.size(); n++) {
            double angle = 2.0 * PI * k * n / signal.samples.size();
            double real = std::cos(angle);
            double imag = -std::sin(angle);
            X[k] += signal.samples [n] * std::complex<double>(real, imag);
        }
        X[k] *= scale;  // Normalization
    }
    Y.reserve(X.size());
    for (int i = 0; i < X.size(); i++) {
        Y.push_back(X[i].real());
    }
    return Y;
}