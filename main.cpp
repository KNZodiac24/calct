#include <cstring>
#include "calc-tiempo.hpp"

int main (int argc, char *argv[]) {

    switch(argc){
        case 1: imprimirMensajeAyuda(); break;
        case 2: {
            if(strcmp(argv[1], "-h") == 0){ imprimirMensajeAyuda(); break;}
            std::cout << ERROR_ARGUMENTOS_INVALIDOS; exit(EXIT_FAILURE);
        }
        break;
        case 4: {
            switch(*argv[2]) {
                case '+': std::cout << ejecutarCalculo(argv[1], argv[3], SUMA) << "\n"; break;
                case '-': std::cout << ejecutarCalculo(argv[1], argv[3], RESTA) << "\n"; break;
                default: std::cout << ERROR_ARGUMENTOS_INVALIDOS; exit(EXIT_FAILURE); break;
            }
            break;
        } break;
        default: std::cout << ERROR_ARGUMENTOS_INVALIDOS; exit(EXIT_FAILURE); break;
    }

    return 0;
}
