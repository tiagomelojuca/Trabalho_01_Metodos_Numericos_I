#include <iostream>
#include "tratamento.h"

bool validando_inteiro(const std::string& entrada, int& numero_inteiro) {
    try {
        numero_inteiro = std::stoi(entrada);
        return true;
    }
    catch (std::invalid_argument&) {
        std::cout << "\nErro: entre um numero inteiro." << std::endl << std::endl;
    }
    catch (std::out_of_range&) {
        std::cout << "\nErro: entre um numero valido." << std::endl << std::endl;
    }
    return false;
}

bool validando_double(const std::string& entrada, double& numero_double){
    try {
        numero_double = std::stod(entrada);
        return true;
    } catch (std::invalid_argument&) {
        std::cout << "\nErro: entre um numero valido." << std::endl << std::endl;
    } 
    catch (std::out_of_range&) {
        std::cout << "\nErro: entre um numero valido." << std::endl << std::endl;
    }
    return false;
}
