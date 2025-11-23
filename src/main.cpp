#include <iostream>
#include <iomanip>
#include <vector>
#include "funcao.h"
#include "refinamento.h"
#include "isolamento.h"

int main() {
    int opcao;
    bool continuar = true;
    std::vector<intervalo> intervalos;

    // padrão estabelecido
    double d0 = 0.5, e1 = 0.0001, e2 = 0.0001, maxIter = 30;
    double d1 = 1;

    std::cout << std::fixed << std::setprecision(6);

    while(continuar != false){
        std::cout << " ======= MENU ======= " << std::endl <<
        "0 - Isolamento" << std::endl <<
        "1 - Refinamento" << std::endl << 
        "2 - Sair" << std::endl <<
        "opcao: ";
        std::cin >> opcao;
        std::cout << std::endl;

        switch (opcao)
        {
        // ============== ISOLAMENTO ============== 
        case 0:
            std::cout << "======= Escolher padrao =======" << std::endl <<
            "0 - Funcao padrao (f(d) = e^d - 4*d^2)" << std::endl <<
            "1 - Funcao com 'a' variado (f(d) = a*e^d - 4*d^2)" << std::endl <<
            "2 - Voltar" << std::endl <<
            "Opcao: ";
            std::cin >> opcao;
            std::cout << std::endl;
            
            switch (opcao)
            {
            // ============== FUNCAO PADRAO ============== 
            case 0:
                double a1, b1;
                std::cout << "f(d) = e^d - 4*d^2" << std::endl << std::endl <<
                " ===== Escolha o intervalo inicial: =====" << std::endl <<
                "Extremidade esquerda: ";
                std::cin >> a1;
                std::cout << "Extremidade direita: ";
                std::cin >> b1;
                std::cout << std::endl;

                intervalos = isolamento(a1, b1, 1);
                if(intervalos.size() == 0){
                    std::cout << "Nenhuma raiz foi encontrada. " << std::endl;
                }
                else{
                    std::cout << std::setprecision(2) << "Intervalos com raizes encontrados entre " << a1 << " e " << b1 << ":" << std::endl;
                for(int i = 0; i<intervalos.size(); ++i){
                    std::cout << "[" << std::setprecision(2) << intervalos[i].a << "," << intervalos[i].b <<
                    "]" << " ";
                }
                std::cout << std::endl;
                }
                break;
            // ============== FUNCAO COM A VARIADO ============== 
            case 1:
                double a2, b2;
                double A;

                std::cout << 
                "f(d) = a*e^d - 4*d^2" << std::endl << std::endl <<
                " ======== Escolha o valor de 'a' ========" << std::endl <<
                "Valor: ";
                std::cin >> A;
                std::cout << std::endl;

                std::cout << "f(d) = " << std::setprecision(2) << A << "e^d - 4*d^2" << std::endl << std::endl <<
                " ===== Escolha o intervalo inicial: =====" << std::endl <<
                "Extremidade esquerda: ";
                std::cin >> a2;
                std::cout << "Extremidade direita: ";
                std::cin >> b2;
                std::cout << std::endl;

                intervalos = isolamento(a2, b2, A);
                if(intervalos.size() == 0){
                    std::cout << "Nenhuma raiz foi encontrada. " << std::endl;
                }
                else{
                    std::cout << std::setprecision(2) << "Intervalos com raizes encontrados entre " << a2 << " e " << b2 << ":" << std::endl;
                for(int i = 0; i<intervalos.size(); ++i){
                    std::cout << "[" << std::setprecision(2) << intervalos[i].a << "," << intervalos[i].b <<
                    "]" << " ";
                }
                std::cout << std::endl;
                }
                break;
            // ============== VOLTAR ============== 
            case 2:
                break;
            default:
                std::cout << "Erro! Entre uma opcao valida." << std::endl;
                break;
            }
            break;
        // ============== REFINAMENTO ============== 
        case 1:
            std::cout << "======= ESCOLHA O PADRAO =======" << std::endl <<
            "0 - Funcao padrao (f(d) = e^d - 4*d^2)" << std::endl <<
            "1 - Funcao com 'a' variado (f(d) = a*e^d - 4*d^2)" << std::endl <<
            "2 - Voltar" << std::endl <<
            "opcao: ";
            std::cin >> opcao;
            std::cout << std::endl;

            switch (opcao)
            {
            case 0:
                // ========== FUNCAO PADRAO ========== 
                std::cout << 
                "f(d) = e^d - 4*d^2" << std::endl << std::endl <<    
                " ======= METODOS DE REFINAMENTO =======" << std::endl << 
                "0 - Metodo de Newton-Raphson" << std::endl <<
                "1 - Metodo de Newton modificado" << std::endl <<
                "2 - Metodo da Secante tradicional" << std::endl <<
                "3 - Voltar" << std::endl <<
                "opcao: ";
                std::cin >> opcao;
                std::cout << std::endl;

                switch (opcao)
                {
                    // ============== NEWTON TRADICIONAL ==============
                case 0:
                    std::cout << "\n======== METODO DE NEWTON-RAPHSON ========" << std::endl;
                    std::cout << "Aproximacao: " << newton(d0, e1, e2, maxIter, 1) << std::endl;
                    break;
                    // ============== NEWTON MODIFICADO ==============
                case 1:
                    std::cout << "\n======== METODO DE NEWTON MODIFICADO ========" << std::endl;
                    std::cout << "Aproximacao: " << newton_modificado(d0, e1, e2, maxIter, 1) << std::endl;
                    break;
                    // ============== SECANTE TRADICIONAL ==============
                case 2:
                    std::cout << "\n======== METODO DA SECANTE ========" << std::endl;
                    std::cout << "Aproximacao: " << secante(d0, d1, e1, e2, maxIter, 1) << std::endl;
                    // ============== VOLTAR ==============
                case 3:
                    break;
                default:
                    std::cout << "Erro! Escolha um metodo valido." << std::endl;
                    break;
                }
                break;
            case 1:
                // ========== FUNCAO COM "A" VARIADO ==========
                double a, novo_d0, novo_d1, e, a3, b3;
                int index_intervalo;
                // definindo valor de a
                std::cout << 
                "f(d) = a*e^d - 4*d^2" << std::endl << std::endl <<
                " ======== Escolha o valor de 'a' ========" << std::endl <<
                "Valor: ";
                std::cin >> a;
                std::cout << std::endl;

                // isolamento
                std::cout << "f(d) = " << std::setprecision(2) << a << "e^d - 4*d^2" << std::endl << std::endl <<
                " ======== Isolamento ========" << std::endl <<
                "Extremidade esquerda: ";
                std::cin >> a3;
                std::cout << "Extremidade direita: ";
                std::cin >> b3;
                std::cout << std::endl;

                intervalos = isolamento(a3, b3, a);
                if(intervalos.size() == 0){
                    std::cout << "Nenhuma raiz foi encontrada. " << std::endl;
                    break;
                }
                else{
                    std::cout << std::setprecision(2) << "Intervalos com raizes encontrados entre " << a3 << " e " << b3 << ":" << std::endl;
                for(int i = 0; i<intervalos.size(); ++i){
                    std::cout << "[" << std::setprecision(2) << intervalos[i].a << "," << intervalos[i].b <<
                    "]" << " ";
                }
                std::cout << std::endl;
                }
                // escolha o intervalo a ser refinado
                std::cout << "======= Escolha o intervalo =======" << std::endl;
                for(int i = 0; i<intervalos.size(); ++i){
                    std::cout << i <<" - [" << std::setprecision(2) << intervalos[i].a << "," << intervalos[i].b <<
                    "]" << " ";
                }
                std::cout << std::endl << 
                "Opcao: ";
                std::cin >> index_intervalo;
                std::cout << std::endl;
                if(index_intervalo >= 0 && index_intervalo <= intervalos.size()-1){
                    intervalo intervalo_refinado = intervalos[index_intervalo];
                    // definindo valor de d0 e d1
                    novo_d0 = intervalo_refinado.a;
                    novo_d1 = intervalo_refinado.b;
                }    
                else{
                    std::cout << "Faca uma escolha valida." << std::endl;
                    break;
                }
                // escolher valor do erro absoluto  
                std::cout << 
                "f(d) = " << std::setprecision(2) << a << "*e^d - 4*d^2" << std::endl << std::endl <<
                " ======== Escolha o valor do erro absoluto ========" << std::endl <<
                "Erro: ";
                std::cin >> e;
                std::cout << std::endl;
                if(e <= 0 || e >= 1){
                    std::cout << "Entre um erro valido entre 0 e 1." << std::endl;
                    break;
                }

                // escolher método de refinamento
                std::cout << 
                "f(d) = " << std::setprecision(2) << a << "*e^d - 4*d^2" << std::endl << std::endl <<    
                " ======= METODOS DE REFINAMENTO =======" << std::endl << 
                "0 - Metodo de Newton-Raphson" << std::endl <<
                "1 - Metodo de Newton modificado" << std::endl <<
                "2 - Metodo da Secante tradicional" << std::endl <<
                "3 - Voltar" << std::endl <<
                "opcao: ";
                std::cin >> opcao;
                std::cout << std::endl;

                switch (opcao)
                {
                    // ============== NEWTON TRADICIONAL ==============
                case 0:
                    std::cout << "\n======== METODO DE NEWTON-RAPHSON ========" << std::endl;
                    std::cout << "Aproximacao: " << newton(novo_d0, e, e, maxIter, a) << std::endl;
                    break;
                    // ============== NEWTON MODIFICADO ==============
                case 1:
                    std::cout << "\n======== METODO DE NEWTON MODIFICADO ========" << std::endl;
                    std::cout << "Aproximacao: " << newton_modificado(novo_d0, e, e, maxIter, a) << std::endl;
                    break;
                    // ============== SECANTE TRADICIONAL ==============
                case 2:
                    std::cout << "\n======== METODO DA SECANTE ========" << std::endl;
                    std::cout << "Aproximacao: " << secante(novo_d0, novo_d1, e, e, maxIter, a) << std::endl;
                    // ============== VOLTAR ==============
                case 3:
                    break;
                default:
                    std::cout << "Erro! Escolha um metodo valido." << std::endl;
                    break;
                }
                
                break;
            case 2:
                break;
            default:
                std::cout << "Erro! Entre uma opcao valida" << std::endl;
                break;
            }
            
            break;
        // ============== SAIR ==============
        case 2:
            continuar = false;
            break;
        default:
            std::cout << "Erro! Entre uma opcao valida." << std::endl;
            break;
        }     
    }
    
    return 0;
}