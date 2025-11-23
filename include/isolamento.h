#include <iostream>
#include <vector>

// extremidades do intervalo
struct intervalo{
    double a, b;
};

// função de isolamento
std::vector<intervalo> isolamento(double a, double b, double A);