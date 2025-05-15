#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <complex>
#include "generator.cpp"

// DFT implementation
std::vector<std::complex<double>> DFT(const std::vector<double>& signal) {
    const double PI = 3.14159265358979323846;
    size_t N = signal.size();
    std::vector<std::complex<double>> result(N);
    
    for (size_t k = 0; k < N; k++) {
        std::complex<double> sum(0, 0);
        for (size_t n = 0; n < N; n++) {
            double angle = 2 * PI * k * n / N;
            sum += signal[n] * std::complex<double>(cos(angle), -sin(angle));
        }
        result[k] = sum;
    }
    
    return result;
}

// IDFT implementation
std::vector<double> IDFT(const std::vector<std::complex<double>>& spectrum) {
    const double PI = 3.14159265358979323846;
    size_t N = spectrum.size();
    std::vector<double> result(N);
    
    for (size_t n = 0; n < N; n++) {
        std::complex<double> sum(0, 0);
        for (size_t k = 0; k < N; k++) {
            double angle = 2 * PI * k * n / N;
            sum += spectrum[k] * std::complex<double>(cos(angle), sin(angle));
        }
        result[n] = sum.real() / N;
    }
    
    return result;
}

// Helper function to get magnitude spectrum
std::vector<double> getMagnitudeSpectrum(const std::vector<std::complex<double>>& spectrum) {
    std::vector<double> magnitude(spectrum.size());
    for (size_t i = 0; i < spectrum.size(); i++) {
        magnitude[i] = std::abs(spectrum[i]);
    }
    return magnitude;
}

// Example usage function
void analyzeSignal(SignalType type) {
    // Generate signal
    double amplitude = 1.0;
    double frequency = 2.0;
    double duration = 1.0;
    double samplingRate = 1000;
    
    auto samples = generateSignalSamples(amplitude, frequency, duration, samplingRate, type);
    
    // Perform DFT
    auto spectrum = DFT(samples);
    
    // Get magnitude spectrum
    auto magnitudes = getMagnitudeSpectrum(spectrum);
    
    // Perform IDFT
    auto recoveredSignal = IDFT(spectrum);
    
    // Print first 10 values of original signal, spectrum, and recovered signal
    std::cout << "Original signal (first 10 samples):\n";
    for (size_t i = 0; i < 10 && i < samples.size(); ++i) {
        std::cout << samples[i] << " ";
    }
    
    std::cout << "\n\nMagnitude spectrum (first 10 values):\n";
    for (size_t i = 0; i < 10 && i < magnitudes.size(); ++i) {
        std::cout << magnitudes[i] << " ";
    }
    
    std::cout << "\n\nRecovered signal (first 10 samples):\n";
    for (size_t i = 0; i < 10 && i < recoveredSignal.size(); ++i) {
        std::cout << recoveredSignal[i] << " ";
    }
    std::cout << "\n";
}
