#include <iostream>
#include <matplot/matplot.h>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
#include "headers.h"
#include<pybind11/complex.h>
//sprawdzić czy potrzebne
// int add() {
//     int a = 5;
//     int b = 7;
//     Signal s (3.0, 0.0, 1.0, "sin");
//     for(int i = 0; i < 100; i+=10) {
//         std::cout << s.samples[i] << " ";
//     }std::cout << std::endl;
//     return a + b;
// }
    //nadpisywanie maina

PYBIND11_MODULE(example, m) { //test
    m.doc() = "Example module using pybind11";

    

    // definicje do pybind 
    pybind11::class_<Signal>(m, "Signal")
        .def(pybind11::init<double, double, double, std::string>())
        .def(pybind11::init< double, double, std::string, Fourier>())
        .def_readwrite("frequency", &Signal::f)
        .def_readwrite("t_start", &Signal::t_start)
        .def_readwrite("t_end", &Signal::t_end)
        .def_readwrite("name", &Signal::name)
        .def_readwrite("samples", &Signal::samples);

    pybind11::class_<Fourier>(m, "Fourier")
        .def(pybind11::init<Signal>())
        .def_readwrite("X", &Fourier::X)
        .def_readwrite("t_start", &Fourier::t_start)
        .def_readwrite("t_end", &Fourier::t_end);

    m.attr("N")= N;  // przekaz ilości próbek i WIELU cyfr liczby pi
    m.attr("PI") = PI;  
    //definicje funkcji
    m.def("plot_signal", &plot_signal, "Plot signal using matplot++",
        pybind11::arg("signal"));
    
    m.def("plot_fourier", &plot_fourier, "Plot Fourier transform using matplot++",
        pybind11::arg("fourier"));
          
    m.def("dft", &dft, "Discrete Fourier Transform",
        pybind11::arg("signal"));

    m.def("idft", &idft, "Inverse Discrete Fourier Transform",
        pybind11::arg("fourier"));
    

}
