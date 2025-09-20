#ifndef CALC_TIEMPO_HPP
#define CALC_TIEMPO_HPP

#include <cmath>
#include <vector>
#include <string>
#include <expected>
#include "ctre.hpp"

#define HORAS_EN_SEGS 3600
#define MINS_EN_SEGS  60
#define SEGS_A_HORAS  1/3600
#define HORAS_A_MINS  60
#define MINS_A_SEGS   60 

#define ERROR_FORMATO "El formato ingresado en uno o ambos tiempos no es válido:\n\t-> Ejecutar el programa con -h para ver el formato correcto y ejemplos de uso\n"
#define ERROR_RANGO_VALORES "Uno o varios de los valores ingresados están fuera del rango válido de tiempo:\n\t-> minutos y segundos deben ser menor o igual a 59\n"

enum Operaciones {
    SUMA,
    RESTA
};

inline std::expected<bool, std::string> validarFormato(std::string tiempo){
    if(tiempo.empty()) return std::unexpected(ERROR_FORMATO);

    short longitudString {static_cast<short>(tiempo.length())};

    if(longitudString >= 1 && longitudString <= 2 ){
        auto matcher {ctre::match<"^[0-9]{1,2}$">};
        if(matcher(tiempo)) return true;
        
        return std::unexpected(ERROR_FORMATO);
    } 
    
    if(longitudString >= 3 && longitudString <= 4 ){
        auto matcher {ctre::match<"^[0-9]{1,2}:[0-9]{1}|[0-9]{1}:[0-9]{1,2}$">};
        if(matcher(tiempo)) return true;

        return std::unexpected(ERROR_FORMATO);
    }

    if(longitudString == 5 ){
        auto matcherMinYSeg {ctre::match<"^[0-9]{1,2}:[0-9]{1,2}$">};
        if(matcherMinYSeg(tiempo)) return true;

        auto matcherHorMinYseg {ctre::match<"^[0-9]{1}:[0-9]{1}:[0-9]{1}$">};
        if(matcherHorMinYseg(tiempo)) return true;

        return std::unexpected(ERROR_FORMATO);
    }

    if(longitudString >= 6 && longitudString <= 8 ){
        auto matcher {ctre::match<"^[0-9]{1,2}:[0-9]{1,2}:[0-9]{2}|[0-9]{1,2}:[0-9]{2}:[0-9]{1,2}|[0-9]{2}:[0-9]{1,2}:[0-9]{1,2}|[0-9]{4}:[0-9]{1}:[0-9]{1}|[0-9]{3}:[0-9]{1,2}:[0-9]{1,2}$">};
        if(matcher(tiempo)) return true;

        return std::unexpected(ERROR_FORMATO);
    }

    if(longitudString > 8 ){
        auto matcher {ctre::match<"^[0-9]{3}:[0-9]{2}:[0-9]{2}|[0-9]{4,}:[0-9]{1,2}:[0-9]{1,2}$">};
        if(matcher(tiempo)) return true;

        return std::unexpected(ERROR_FORMATO);
    }

    return false;
}

// De: https://stackoverflow.com/questions/7726762/finding-all-occurrences-of-a-character-in-a-string
inline std::vector<int> findLocation(std::string sample, char findIt)
{
    std::vector<int> characterLocations {};
    for(size_t i = 0; i < sample.size(); ++i)
        if(sample[i] == findIt)
            characterLocations.push_back(i);

    return characterLocations;
}

inline std::expected<int*, std::string> separarValoresTiempo(std::string tiempo){
    
    if(!tiempo.contains(":")) return new int[3]{ 0, 0, std::stoi(tiempo) };

    std::string horasStr {};
    std::string minsStr {};
    std::string segsStr {};

    std::vector<int> separador { findLocation(tiempo, ':') };

    switch(separador.size()){
        case 1: { horasStr = "0";
                  minsStr = tiempo.substr(0, separador.at(0));
                  segsStr = tiempo.substr(separador.at(0)+1, tiempo.length()-1); 
                }
                break;
        case 2: { horasStr = tiempo.substr(0, separador.at(0));
                  minsStr = tiempo.substr(separador.at(0)+1, separador.at(1));
                  segsStr = tiempo.substr(separador.at(1)+1, tiempo.length()-1);
                }    
                break;
    }

    int horas { std::stoi(horasStr) };
    int mins { std::stoi(minsStr) };
    int segs { std::stoi(segsStr) };

    if(mins > 59 || segs > 59) return std::unexpected(ERROR_RANGO_VALORES);

    return new int[3]{ horas, mins, segs };
}

inline int transformarTiempoASegundos(int* tiempo){
    return tiempo[0]*HORAS_EN_SEGS + tiempo[1]*MINS_EN_SEGS + tiempo[2];
}

inline int calcularTiempo(int t1, int t2, Operaciones op){
    switch (op) {
        case SUMA: return t1 + t2; break;
        case RESTA: return t1 - t2; break;
    }
}

inline std::string convertirResultadoATiempo(int resultadoEnSegs){
    double resultadoAConvertir { double(resultadoEnSegs) };

    double horaDecimal { resultadoAConvertir*SEGS_A_HORAS };
    double parteEnteraHora {};
    double parteFraccionariaHora { std::modf(horaDecimal, &parteEnteraHora) };
    int hora { static_cast<int>(parteEnteraHora) };

    double minutosDecimal { parteFraccionariaHora*HORAS_A_MINS };
    double parteEnteraMins {};
    double parteFraccionariaMins { std::modf(minutosDecimal, &parteEnteraMins) };
    int mins { static_cast<int>(parteEnteraMins) };

    double segundosDecimal { parteFraccionariaMins*MINS_A_SEGS };
    int segs { static_cast<int>(round(segundosDecimal)) };

    if(segs == 60){ ++mins; segs = 0; }

    if(mins == 60){ ++hora; mins = 0; }

    return std::string(std::to_string(hora)+':'+std::to_string(mins)+':'+std::to_string(segs));
}

inline void ejecutarCalculo();

#endif
