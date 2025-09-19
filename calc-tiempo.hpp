#ifndef CALC_TIEMPO
#define CALC_TIEMPO

#include "ctre.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

#define HORAS_A_SEGS 3600
#define MINS_A_SEGS  60

enum Operaciones {
    SUMA,
    RESTA
};

bool validarFormato(std::string tiempo){
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
std::vector<int> findLocation(std::string sample, char findIt)
{
    std::vector<int> characterLocations;
    for(int i =0; i < sample.size(); i++)
        if(sample[i] == findIt)
            characterLocations.push_back(i);

    return characterLocations;
}

int* separarValoresTiempo(std::string tiempo){
    
    if(!tiempo.contains(":")){
        return new int[3]{ 0, 0, std::stoi(tiempo) };
    }

    std::vector<int> separador { findLocation(tiempo, ':') };

    if(separador.size() == 1){
        std::string mins { tiempo.substr(0, separador.at(0))};
        std::string segs { tiempo.substr(separador.at(0)+1, tiempo.length()-1) };
        return new int[3]{ 0, std::stoi(mins), std::stoi(segs)};
    }

    if(separador.size() == 2){
        std::string horas { tiempo.substr(0, separador.at(0))};
        std::string mins { tiempo.substr(separador.at(0)+1, separador.at(1)) };
        std::string segs { tiempo.substr(separador.at(1)+1, tiempo.length()-1) };
        return new int[3]{ std::stoi(horas), std::stoi(mins), std::stoi(segs)};
    }

    return nullptr;
}

int transformarTiempoASegundos(int* tiempo){ 
    return tiempo[0]*HORAS_A_SEGS + tiempo[1]*MINS_A_SEGS + tiempo[2];
}

#endif
