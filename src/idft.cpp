#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include "headers.h"

std::vector<double> idft(const std::vector<std::complex<double>>& X) {
    const int N = X.size();
    std::vector<double> samples(N);
    const double scale = 1.0 / N;
    
    for (int n = 0; n < N; n++) {
        std::complex<double> sum(0.0, 0.0);
        for (int k = 0; k < N; k++) {
            sum += X[k] * std::exp(std::complex<double>(0, 2.0 * PI * k * n / N));
        }
        samples[n] = scale * std::real(sum);
    }
    
    return samples;
}