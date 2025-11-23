#include <iostream>
#include <cmath>
#include <vector>
#include <isolamento.h>
#include "funcao.h"

std::vector<intervalo> isolamento(double a, double b, double A){
    std::vector<intervalo> intervalos;
    for(int i = a; i<b; ++i){
        
        // teorema
        if(f_a(i, A) * f_a(i+1, A) < 0){
            intervalo I;
            I.a = i;
            I.b = i+1;
            intervalos.push_back(I);
        }
        // tentar implementar corolário
        // tentar apertar intervalo
        
    }

    return intervalos;
}