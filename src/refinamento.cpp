#include <iostream>
#include <cmath>
#include <iomanip> // biblioteca para construção da tabela
#include "funcao.h"
#include "refinamento.h"

#define D_0 0.5
// ================= MÉTODO DE NEWTON-RAPHSON =================

double newton(double d0, double e1, double e2, int maxIter, double a){
    double d1;
    int k;
    // verificando se d0 já é uma aproximação válida
    if(std::abs(f_a(d0, a)) < e1) return d0;
    
    // rótulos da tabela
    std::cout << std::fixed << std::setprecision(6);
    std::cout << std::left;
    std::cout << std::setw(10) << "iteracao"
        << std::setw(12) << "d0"
        << std::setw(12) << "d1"
        << std::setw(13) << "d1-d0"
        << std::setw(13) << "f(d1)" << std::endl;
    
    // refinamento    
    k = 1;
    while(k <= maxIter){
        // calculando nova aproximação d1
        d1 = d0 - f_a(d0, a)/dxf_a(d0, a);

        // tabela
        std::cout << std::setw(10) << k
        << std::setw(12) << d0
        << std::setw(12) << d1
        << std::setw(13) << d1-d0
        << std::setw(13) << f_a(d1, a) << std::endl;
        std::cout << std::string(65, '-') << std::endl;
        
        // verificando critérios de parada
        if(std::abs(f_a(d1, a)) < e1 || std::abs(d1-d0) < e2 || k >= maxIter) return d1;
        // continuar...
        d0 = d1;
        ++k;
    }
    return d1;
}

// ================= MÉTODO DE NEWTON MODIFICADO =================

double newton_modificado(double d0, double e1, double e2, int maxIter, double a){
    double d1;
    int k;
    // verificando se d0 já é uma aproximação válida
    if(std::abs(f_a(d0, a)) < e1) return d0;
    
    // rótulos da tabela
    std::cout << std::fixed << std::setprecision(6);
    std::cout << std::left;
    std::cout << std::setw(10) << "iteracao"
        << std::setw(12) << "d0"
        << std::setw(12) << "d1"
        << std::setw(13) << "d1-d0"
        << std::setw(13) << "f(d1)" << std::endl;
    
    // refinamento    
    k = 1;
    while(k <= maxIter){
        // calculando nova aproximação d1
        d1 = d0 - f_a(d0, a)/dxf_a(D_0, a);

        // tabela
        
        std::cout << std::setw(10) << k
        << std::setw(12) << d0
        << std::setw(12) << d1
        << std::setw(13) << d1-d0
        << std::setw(13) << f_a(d1, a) << std::endl;
        std::cout << std::string(65, '-') << std::endl;
        
        // verificando critérios de parada
        if(std::abs(f_a(d1, a)) < e1 || std::abs(d1-d0) < e2 || k >= maxIter) return d1;
        // continuar...
        d0 = d1;
        ++k;
    }
    return d1;
}

// ================= MÉTODO DA SECANTE TRADICIONAL =================

double secante(double x0, double x1, double e1, double e2, int maxIter, double a){
    double x2;
    int k;

    // verificando se x0 ou x1 sao aproximações válidas
    if(std::abs(f_a(x0, a)) < e1) return x0;
    if(std::abs(f_a(x1, a)) < e1 || std::abs(x1-x0) < e2) return x1;

    // rótulos da tabela
    std::cout << std::fixed << std::setprecision(6);
    std::cout << std::left;
    std::cout << std::setw(12) << "iteracao"
        << std::setw(12) << "x"
        << std::setw(12) << "f(x)" << std::endl;

    // refinamento
    k = 1;
    while(k <= maxIter){
        // calculando nova aproximação x2
        x2 = x1 - f_a(x1, a)/(f_a(x1, a) - f_a(x0, a)) * (x1-x0);
        
        // tabela
        std::cout << std::setw(10) << k
                  << std::setw(12) << x2
                  << std::setw(12) << f_a(x2, a) << std::endl;        
        std::cout << std::string(40, '-') << std::endl;

        // verificando critérios de parada
        if(std::abs(f_a(x2, a)) < e1 || std::abs(x2-x1) < e2 || k >= maxIter) return x2;
        // continuar...
        x0 = x1;
        x1 = x2;
        ++k;
    }
    return x2;
}


