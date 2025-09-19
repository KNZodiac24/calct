#ifndef CALC_TIEMPO_HPP
#define CALC_TIEMPO_HPP

#include <vector>
#include <string>
#include "ctre.hpp"

#define HORAS_A_SEGS 3600
#define MINS_A_SEGS  60

enum Operaciones {
    SUMA,
    RESTA
};

inline bool validarFormato(std::string tiempo){
    if(tiempo.empty()) return false;

    short longitudString {static_cast<short>(tiempo.length())};

    if(longitudString >= 1 && longitudString <= 2 ){
        auto matcher {ctre::match<"^[0-9]{1,2}$">};
        if(matcher(tiempo)) return true;
        
        return false;
    } 
    
    if(longitudString >= 3 && longitudString <= 4 ){
        auto matcher {ctre::match<"^[0-9]{1,2}:[0-9]{1}|[0-9]{1}:[0-9]{1,2}$">};
        if(matcher(tiempo)) return true;

        return false;
    }

    if(longitudString == 5 ){
        auto matcherMinYSeg {ctre::match<"^[0-9]{1,2}:[0-9]{1,2}$">};
        if(matcherMinYSeg(tiempo)) return true;

        auto matcherHorMinYseg {ctre::match<"^[0-9]{1}:[0-9]{1}:[0-9]{1}$">};
        if(matcherHorMinYseg(tiempo)) return true;

        return false;
    }

    if(longitudString >= 6 && longitudString <= 8 ){
        auto matcher {ctre::match<"^[0-9]{1,2}:[0-9]{1,2}:[0-9]{2}|[0-9]{1,2}:[0-9]{2}:[0-9]{1,2}|[0-9]{2}:[0-9]{1,2}:[0-9]{1,2}|[0-9]{4}:[0-9]{1}:[0-9]{1}|[0-9]{3}:[0-9]{1,2}:[0-9]{1,2}$">};
        if(matcher(tiempo)) return true;

        return false;
    }

    if(longitudString > 8 ){
        auto matcher {ctre::match<"^[0-9]{3}:[0-9]{2}:[0-9]{2}|[0-9]{4,}:[0-9]{1,2}:[0-9]{1,2}$">};
        if(matcher(tiempo)) return true;

        return false;
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

inline int* separarValoresTiempo(std::string tiempo){
    
    if(!tiempo.contains(":")) return new int[3]{ 0, 0, std::stoi(tiempo) };

    std::string horas {};
    std::string mins {};
    std::string segs {};

    std::vector<int> separador { findLocation(tiempo, ':') };

    switch(separador.size()){
        case 1: { horas = "0";
                  mins = tiempo.substr(0, separador.at(0));
                  segs = tiempo.substr(separador.at(0)+1, tiempo.length()-1);
                }
                break;
        case 2: { horas = tiempo.substr(0, separador.at(0));
                  mins = tiempo.substr(separador.at(0)+1, separador.at(1));
                  segs = tiempo.substr(separador.at(1)+1, tiempo.length()-1);
                }    
                break;
    }

    return new int[3]{ std::stoi(horas), std::stoi(mins), std::stoi(segs) };
}

inline int transformarTiempoASegundos(int* tiempo){
    return tiempo[0]*HORAS_A_SEGS + tiempo[1]*MINS_A_SEGS + tiempo[2];
}

inline int calcularTiempo(int t1, int t2, Operaciones op){
    switch (op) {
        case SUMA: return t1 + t2; break;
        case RESTA: return t1 - t2; break;
    }
}

#endif
