#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include "headers.h"

std::vector<double> idft(Fourier fourier) {
    const std::vector<std::complex<double>> X = fourier.X;
    std::vector<double> samples(X.size());
    
    for (int n = 0; n < X.size(); n++) {
        std::complex<double> sum(0.0, 0.0);
        for (int k = 0; k < X.size(); k++) {
            sum += X[k] * std::exp(std::complex<double>(0, 2.0 * PI * k * n / X.size()));
        }
        samples[n] = std::real(sum);
    }
    for (int i = 0; i < samples.size(); i++) {
        samples[i] /=*std::max_element(samples.begin(),samples.end());  // Normalize the result
    }
    
    return samples;
}