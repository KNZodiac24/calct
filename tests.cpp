#include "calc-tiempo.hpp"
#include <iostream>

int main(){
    std::string tiempos[] = {
        "111:1:1",
        "111:11:1",
        "111:1:11",
        "1111:1:1",
        "1111:11:1",
        "1111:1:11",
        "11111:1:11",
        "10:31:27",
        "01:03:07",
        "2:1:0",
        "10:3",
        "5:07",
        "34",
        "03",
        "9"
    };

    int separaciones[15][3] = {
        {111,1,1},
        {111,11,1},
        {111,1,11},
        {1111,1,1},
        {1111,11,1},
        {1111,1,11},
        {11111,1,11},
        {10,31,27},
        {01,03,07},
        {2,1,0},
        {10,3},
        {5,07},
        {34},
        {03},
        {9}
    };

    int tiemposEnSegundos[] = {
        399661,
        400261,
        399671,
        3999661,
        4000261,
        3999671,
        39999671,
        37887,
        3787,
        7260,
        603,
        307,
        34,
        3,
        9
    };

    std::cout << "VALIDACIONES DE FORMATO:\n";
    for(size_t i = 0; i < 15; ++i){
        std::cout << tiempos[i] << " ::: ";
        if (!validarFormato(tiempos[i])){ std::cout<<"incorrecto\n"; return 1; }
        std::cout << "correcto\n";
    }

    std::cout << "SEPARACIONES DE VALORES DE TIEMPO:\n";
    for (size_t i = 0; i < 15; ++i) {
        std::cout << tiempos[i] << " ::: ";
        if(*separaciones[i] != *separarValoresTiempo(tiempos[i])) { std::cout<<"incorrecto\n"; return 1;}
        std::cout << "correcto\n";
    }

    std::cout << "TRANSFORMACIÓN DE TIEMPO A SEGUNDOS:\n";
    for (size_t i = 0; i < 15; ++i) {
        std::cout << tiempos[i] << " ::: ";
        if(tiemposEnSegundos[i] != transformarTiempoASegundos(separarValoresTiempo(tiempos[i]))) { std::cout<<"incorrecto\n"; std::cout << transformarTiempoASegundos(separarValoresTiempo(tiempos[i])); return 1;}
        std::cout << "correcto\n";
    }

    return 0;
}
