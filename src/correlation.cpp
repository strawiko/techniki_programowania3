#include <vector>
#include <complex>
#include <cmath>
#include "headers.h"
std::vector<double>correlation(const Signal& signal1, const Signal& signal2) {
    size_t N = signal1.samples.size();
    std::vector<double> result(2 * N + 1, 0.0);
    
    for (size_t lag = 0; lag < 2 * N - 1; ++lag) {
        for (size_t n = 0; n < N; ++n) {
            if (n + lag < N) {
                result[lag] += signal1.samples[n] * signal2.samples[n + lag];
            } else if (n + lag >= N && n + lag < 2 * N - 1) {
                result[lag] += signal1.samples[n] * signal2.samples[n + lag - N];
            }
        }
    }
    
    return result;
}