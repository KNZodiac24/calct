#include <iostream>
#include <string>
#include "calc-tiempo.hpp"

int main (int argc, char *argv[]) {

    /*std::string primerTiempo {};*/
    /*std::cout << "Ingresa el primer tiempo: ";*/
    /*std::getline( std::cin >> std::ws, primerTiempo);*/

    std::string t1 {"1:23"};
    std::string t2 {"2:43"};

    std::cout << ejecutarCalculo(t1, t2, SUMA) << "\n";

    return 0;
}
