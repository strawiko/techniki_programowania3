#include <iostream>
#include <matplot/matplot.h>
#include<pybind11/pybind11.h>
int add() {
    int a = 5;
    int b = 4;
    return a + b;
}//zdwad
PYBIND11_MODULE(example, m) {
    m.doc() = "Example module using pybind11"; // optional module docstring

    // Expose functions to Python
    m.def("add", &add, "A function that adds two numbers");
}