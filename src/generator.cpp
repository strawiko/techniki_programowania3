#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

enum class SignalType {
    SINE,
    COSINE,
    SQUARE,
    SAWTOOTH
};

// Function to get random signal type
SignalType getRandomSignalType() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 3);
    return static_cast<SignalType>(dis(gen));
}

// Modified function with optional random type
double generateSignal(double time, double amplitude, double frequency, SignalType type = getRandomSignalType()) {
    const double PI = 3.14159265358979323846;
    double period = 2 * PI * frequency * time;
    
    switch(type) {
        case SignalType::SINE:
            return amplitude * std::sin(period);
            
        case SignalType::COSINE:
            return amplitude * std::cos(period);
            
        case SignalType::SQUARE:
            return amplitude * (std::sin(period) > 0 ? 1.0 : -1.0);
            
        case SignalType::SAWTOOTH:
            return amplitude * (2.0 * (period/(2*PI) - std::floor(0.5 + period/(2*PI))));
            
        default:
            return 0.0;
    }
}

// Modified sample generator with optional random type
std::vector<double> generateSignalSamples(double amplitude, double frequency, 
                                        double duration, double samplingRate,
                                        SignalType type = getRandomSignalType()) {
    std::vector<double> samples;
    double dt = 1.0 / samplingRate;
    
    for(double t = 0; t < duration; t += dt) {
        samples.push_back(generateSignal(t, amplitude, frequency, type));
    }
    
    return samples;
}

int main() {
    // Signal parameters
    double amplitude = 1.0;     // Amplitude (V)
    double frequency = 2.0;     // Frequency (Hz)
    double duration = 1.0;      // Duration (s)
    double samplingRate = 1000; // Samples per second (Hz)

    // Generate all signal types
    std::vector<std::pair<SignalType, std::vector<double>>> signals = {
        {SignalType::SINE, generateSignalSamples(amplitude, frequency, duration, samplingRate, SignalType::SINE)},
        {SignalType::COSINE, generateSignalSamples(amplitude, frequency, duration, samplingRate, SignalType::COSINE)},
        {SignalType::SQUARE, generateSignalSamples(amplitude, frequency, duration, samplingRate, SignalType::SQUARE)},
        {SignalType::SAWTOOTH, generateSignalSamples(amplitude, frequency, duration, samplingRate, SignalType::SAWTOOTH)}
    };

    // Print information and first few samples for each signal
    for (const auto& [type, samples] : signals) {
        std::cout << "\nSignal type: ";
        switch(type) {
            case SignalType::SINE: std::cout << "SINE"; break;
            case SignalType::COSINE: std::cout << "COSINE"; break;
            case SignalType::SQUARE: std::cout << "SQUARE"; break;
            case SignalType::SAWTOOTH: std::cout << "SAWTOOTH"; break;
        }
        std::cout << "\nParameters:"
                  << "\n- Amplitude: " << amplitude << " V"
                  << "\n- Frequency: " << frequency << " Hz"
                  << "\n- Duration: " << duration << " s"
                  << "\n- Sampling rate: " << samplingRate << " Hz"
                  << "\nFirst 10 samples:\n";

        // Print first 10 samples
        for(size_t i = 0; i < std::min<size_t>(10, samples.size()); ++i) {
            std::cout << samples[i] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
