#include <iostream>
#include <string>
#include "calc-tiempo.hpp"

int main(){

    std::cout << "-------------------- CALCULADORA DE TIEMPO --------------------\n---------------------------------------------------------------\n\n";
    std::cout << "Se deben ingresar los tiempos con el siguiente formato: hh:mm:ss\nEl nivel de detalle máximo aceptado es en horas, y el mínimo en segundos.\n---------------------------------------------------------------\n";
    std::cout << "Ejemplos de uso (formato -> equivalencia en lenguaje natural):\n10:31:27 -> 10 horas, 31 minutos y 27 segundos\n01:03:07 -> 1 hora, 3 minutos y 7 segundos\n2:1:0 -> 2 horas, 1 minuto y 0 segundos\n10:3 -> 10 minutos y 3 segundos\n5:07 -> 5 minutos y 7 segundos\n34 -> 34 segundos\n03 -> 3 segundos\n9 -> 9 segundos\n\n";

    std::string primerTiempo {};
    std::cout << "Ingresa el primer tiempo: ";
    std::getline( std::cin >> std::ws, primerTiempo);

    if(!validarFormato(primerTiempo)){
        return 1;
    }

    return 0;
}
