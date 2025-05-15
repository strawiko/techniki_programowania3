#include <vector>
#include <cmath>
#include <algorithm>

// 1D Filtering
std::vector<double> filter1D(const std::vector<double>& signal, const std::vector<double>& kernel) {
    std::vector<double> result(signal.size());
    int kernelCenter = kernel.size() / 2;
    
    for (size_t i = 0; i < signal.size(); i++) {
        double sum = 0.0;
        for (size_t k = 0; k < kernel.size(); k++) {
            int signalIdx = i + k - kernelCenter;
            // Handle boundaries by mirroring
            if (signalIdx < 0) signalIdx = -signalIdx;
            if (signalIdx >= static_cast<int>(signal.size())) 
                signalIdx = 2 * signal.size() - signalIdx - 2;
            
            sum += signal[signalIdx] * kernel[k];
        }
        result[i] = sum;
    }
    return result;
}

// 2D Filtering
std::vector<std::vector<double>> filter2D(const std::vector<std::vector<double>>& image, 
                                        const std::vector<std::vector<double>>& kernel) {
    int rows = image.size();
    int cols = image[0].size();
    int kernelRows = kernel.size();
    int kernelCols = kernel[0].size();
    int kernelCenterY = kernelRows / 2;
    int kernelCenterX = kernelCols / 2;
    
    std::vector<std::vector<double>> result(rows, std::vector<double>(cols));
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double sum = 0.0;
            for (int ky = 0; ky < kernelRows; ky++) {
                for (int kx = 0; kx < kernelCols; kx++) {
                    int imageY = i + ky - kernelCenterY;
                    int imageX = j + kx - kernelCenterX;
                    
                    // Handle boundaries by mirroring
                    if (imageY < 0) imageY = -imageY;
                    if (imageX < 0) imageX = -imageX;
                    if (imageY >= rows) imageY = 2 * rows - imageY - 2;
                    if (imageX >= cols) imageX = 2 * cols - imageX - 2;
                    
                    sum += image[imageY][imageX] * kernel[ky][kx];
                }
            }
            result[i][j] = sum;
        }
    }
    return result;
}

// Common filter kernels
namespace Filters {
    // 1D Filters
    std::vector<double> gaussianKernel1D(int size, double sigma) {
        std::vector<double> kernel(size);
        int center = size / 2;
        double sum = 0.0;
        
        for (int i = 0; i < size; i++) {
            double x = i - center;
            kernel[i] = exp(-(x * x) / (2 * sigma * sigma));
            sum += kernel[i];
        }
        
        // Normalize
        for (double& value : kernel) {
            value /= sum;
        }
        return kernel;
    }
    
    // 2D Filters
    std::vector<std::vector<double>> gaussianKernel2D(int size, double sigma) {
        std::vector<std::vector<double>> kernel(size, std::vector<double>(size));
        int center = size / 2;
        double sum = 0.0;
        
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                double dx = x - center;
                double dy = y - center;
                kernel[y][x] = exp(-(dx * dx + dy * dy) / (2 * sigma * sigma));
                sum += kernel[y][x];
            }
        }
        
        // Normalize
        for (auto& row : kernel) {
            for (double& value : row) {
                value /= sum;
            }
        }
        return kernel;
    }
    
    std::vector<std::vector<double>> sobelX() {
        return {{-1, 0, 1},
                {-2, 0, 2},
                {-1, 0, 1}};
    }
    
    std::vector<std::vector<double>> sobelY() {
        return {{-1, -2, -1},
                { 0,  0,  0},
                { 1,  2,  1}};
    }
}