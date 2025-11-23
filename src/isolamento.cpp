#include <iostream>
#include <cmath>
#include <vector>
#include <isolamento.h>
#include "funcao.h"

// função de isolamento
std::vector<intervalo> isolamento(double a, double b, double A){
    // vetor que guarda os intervalos que contém raízes
    std::vector<intervalo> intervalos;
    for(int i = a; i<b; ++i){
        
        // teorema: f(a)*f(b) < 0 -> tem raiz entre a e b!
        if(f_a(i, A) * f_a(i+1, A) < 0){
            intervalo I;
            I.a = i;
            I.b = i+1;
            intervalos.push_back(I);
        }
        // tentar implementar corolário
            // f'(d) < 0 ou f'(d) > 0, para todo d em [a,b] -> raiz única entre a e b!
        // tentar apertar intervalo
        
    }

    return intervalos;
}