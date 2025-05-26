#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include "headers.h"

std::vector<double> idft(const std::vector<std::complex<double>>& X) {
    std::vector<double> samples(X.size());
    const double scale = 1.0 / X.size();
    
    for (int n = 0; n < X.size(); n++) {
        std::complex<double> sum(0.0, 0.0);
        for (int k = 0; k < X.size(); k++) {
            sum += X[k] * std::exp(std::complex<double>(0, 2.0 * PI * k * n / X.size()));
        }
        samples[n] = scale * std::real(sum);
    }
    
    return samples;
}    //nadpisywanie maina
