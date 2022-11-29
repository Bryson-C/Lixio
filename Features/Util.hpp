//
// Created by Owner on 11/18/2022.
//

#ifndef COMPILERFEATURES_UTIL_HPP
#define COMPILERFEATURES_UTIL_HPP

#include <iostream>
#include <any>

template<typename DT1, typename DT2>
struct Duo {
    Duo() = default;
    Duo(DT1 _one, DT2 _two) : one(_one), two(_two) {}
    DT1 one;
    DT2 two;
};

template<typename DT1, typename DT2, typename DT3>
struct Triple {
    Triple() = default;
    Triple(DT1 _one, DT2 _two, DT3 _three) : one(_one), two(_two), three(_three) {}
    DT1 one;
    DT2 two;
    DT3 three;
};




#endif //COMPILERFEATURES_UTIL_HPP
