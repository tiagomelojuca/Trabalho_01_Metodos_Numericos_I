#include <iostream>
#include <iomanip>
#include <vector>
#include "funcao.h"
#include "refinamento.h"
#include "isolamento.h"
#include "tratamento.h"

int main() {
    // variáveis
    int opcao;
    std::string entrada;
    bool continuar = true, condicao;

    // padrão estabelecido
    double d0 = 0.5, e1 = 0.0001, e2 = 0.0001, maxIter = 30;
    double d1 = 1;

    std::cout << std::fixed << std::setprecision(6);

    // loop da interface no terminal
    while(continuar != false){
        // MENU
        std::cout << " ======= MENU ======= " << std::endl <<
        "0 - Refinamento" << std::endl << 
        "1 - Sair" << std::endl <<
        "opcao: ";
        std::cin >> entrada;
        if(!validando_inteiro(entrada, opcao))  
            continue;
        std::cout << std::endl;

        switch (opcao)
        {
        // ============== REFINAMENTO ============== 
        case 0:
            condicao = true;
            while(condicao){
                std::cout << "======= ESCOLHA O PADRAO =======" << std::endl <<
                "0 - Funcao padrao (f(d) = e^d - 4*d^2)" << std::endl <<
                "1 - Funcao com 'a' variado (f(d) = a*e^d - 4*d^2)" << std::endl <<
                "2 - Voltar para o MENU" << std::endl <<
                "opcao: ";
                std::cin >> entrada;
                if(!validando_inteiro(entrada, opcao))  
                    continue;
                std::cout << std::endl;

                switch (opcao)
                {
                case 0:
                    condicao = true;
                    while(condicao){
                        // ========== FUNCAO PADRAO ========== 
                        std::cout << 
                        "f(d) = e^d - 4*d^2, d0 = " << d0 << ", d1 = " << d1 << ", erro = " << e1 << std::endl << std::endl <<    
                        " ======= METODOS DE REFINAMENTO =======" << std::endl << 
                        "0 - Metodo de Newton-Raphson" << std::endl <<
                        "1 - Metodo de Newton modificado" << std::endl <<
                        "2 - Metodo da Secante tradicional" << std::endl <<
                        "3 - Voltar para o MENU" << std::endl <<
                        "opcao: ";
                        std::cin >> entrada;
                        if(!validando_inteiro(entrada, opcao))  
                            continue;
                        std::cout << std::endl;

                        switch (opcao)
                        {
                            // ============== NEWTON TRADICIONAL ==============
                        case 0:
                            std::cout << "\n======== METODO DE NEWTON-RAPHSON ========" << std::endl;
                            std::cout << "Aproximacao: " << newton(d0, e1, e2, maxIter, 1) << std::endl << std::endl;
                            break;
                            // ============== NEWTON MODIFICADO ==============
                        case 1:
                            std::cout << "\n======== METODO DE NEWTON MODIFICADO ========" << std::endl;
                            std::cout << "Aproximacao: " << newton_modificado(d0, e1, e2, maxIter, 1) << std::endl << std::endl;
                            break;
                            // ============== SECANTE TRADICIONAL ==============
                        case 2:
                            std::cout << "\n======== METODO DA SECANTE ========" << std::endl;
                            std::cout << "Aproximacao: " << secante(d0, d1, e1, e2, maxIter, 1) << std::endl << std::endl;
                            break;
                            // ============== VOLTAR ==============
                        case 3:
                            condicao = false;
                            break;
                        default:
                            std::cout << "\nOpcao inexistente! Tente novamente." << std::endl << std::endl;
                            break;
                        }
                    }
                    break;
                case 1:
                    // ========== FUNCAO COM "A" VARIADO ==========
                    double A, novo_d0, novo_d1, e;
                    intervalo intervalo;
                    // definindo valor de a
                    while(true){
                        std::cout << 
                        "f(d) = a*e^d - 4*d^2" << std::endl << std::endl <<
                        " ======== Escolha o valor de 'a' ========" << std::endl <<
                        "Valor: ";
                        std::cin >> entrada;
                        if(!validando_double(entrada, A))
                            continue;
                        std::cout << std::endl;

                        if(A < 0 || A > 2.165364){
                            std::cout << "O deslocamento d so existe se 'a' esta entre 0 e 2.165364 (truncado)." << std::endl << std::endl;
                            continue;
                        }
                        break;
                    }
                    // valor de A tem de estar entre 0 e 2.165364
                    if(A == 0){
                        std::cout << "Se a amplitude vale 0, o deslocamento tambem vale 0." << std::endl << std::endl;
                        break;
                    }
                
                    // isolamento
                    intervalo = isolamento_para_f_com_A_variado(A);
                    
                    std::cout << std::setprecision(2) << "Intervalos com raizes encontrados: [" << 
                    std::setprecision(2) << intervalo.a << ", " << intervalo.b << "]" << std::endl << std::endl;
                    
                    novo_d0 = intervalo.a;
                    novo_d1 = intervalo.b;
                
                    // escolher valor do erro absoluto  
                    while(true){
                        std::cout << 
                        "f(d) = " << std::setprecision(2) << A << "*e^d - 4*d^2" << std::endl << std::endl <<
                        " ======== Escolha o valor do erro absoluto ========" << std::endl <<
                        "Erro: ";
                        std::cin >> entrada;
                        if(!validando_double(entrada, e))
                            continue;
                        std::cout << std::endl;
                        
                        if(e <= 0 || e >= 1){
                            std::cout << "Entre um erro valido entre 0 e 1." << std::endl << std::endl;
                            continue;
                        }
                        break;
                    }

                    condicao = true;
                    while(condicao){
                        // escolher método de refinamento
                        std::cout << 
                        "f(d) = " << std::setprecision(2) << A << "*e^d - 4*d^2" << std::endl << std::endl <<    
                        " ======= METODOS DE REFINAMENTO =======" << std::endl << 
                        "0 - Metodo de Newton-Raphson" << std::endl <<
                        "1 - Metodo de Newton modificado" << std::endl <<
                        "2 - Metodo da Secante tradicional" << std::endl <<
                        "3 - Voltar para o MENU" << std::endl <<
                        "opcao: ";
                        std::cin >> entrada;
                        if(!validando_inteiro(entrada, opcao))  
                            continue;
                        std::cout << std::endl;

                        switch (opcao)
                        {
                            // ============== NEWTON TRADICIONAL ==============
                        case 0:
                            std::cout << "\n======== METODO DE NEWTON-RAPHSON ========" << std::endl;
                            std::cout << "Aproximacao: " << newton(novo_d0, e, e, maxIter, A) << std::endl << std::endl;
                            break;
                            // ============== NEWTON MODIFICADO ==============
                        case 1:
                            std::cout << "\n======== METODO DE NEWTON MODIFICADO ========" << std::endl;
                            std::cout << "Aproximacao: " << newton_modificado(novo_d0, e, e, maxIter, A) << std::endl << std::endl;
                            break;
                            // ============== SECANTE TRADICIONAL ==============
                        case 2:
                            std::cout << "\n======== METODO DA SECANTE ========" << std::endl;
                            std::cout << "Aproximacao: " << secante(novo_d0, novo_d1, e, e, maxIter, A) << std::endl << std::endl;
                            break;
                            // ============== VOLTAR ==============
                        case 3:
                            condicao = false;
                            break;
                        default:
                            std::cout << "\nOpcao inexistente! Tente novamente." << std::endl << std::endl;
                            break;
                        }
                    }
                    break;
                // ============== VOLTAR ==============
                case 2:
                    condicao = false;
                    break;
                default:
                    std::cout << "\nOpcao inexistente! Tente novamente." << std::endl << std::endl;
                    break;
                }
            }
            
            break;
        // ============== SAIR ==============
        case 1:
            continuar = false;
            break;
        default:
            std::cout << "\nOpcao inexistente! Tente novamente." << std::endl << std::endl;
            break;
        }     
    }
    
    return 0;
}