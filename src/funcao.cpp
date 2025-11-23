#include "funcao.h"
#include <iostream>
#include <cmath>

// função no formato padrão (a = 1)
double f(double d){
    return exp(d) - 4*pow(d,2);
}
// derivada
double dxf(double d){
    return exp(d) - 8*d;
}

// ======================================

// função f com variação em a
double f_a(double d, double a){
    return a*exp(d) - 4*pow(d,2);
}
// derivada
double dxf_a(double d, double a){
    return a*exp(d) - 8*d;
}
