//
// Created by Owner on 11/18/2022.
//

#ifndef COMPILERFEATURES_UTIL_HPP
#define COMPILERFEATURES_UTIL_HPP

template<typename DT1, typename DT2>
struct Duo {
    Duo() = default;
    Duo(DT1 _one, DT2 _two) : one(_one), two(_two) {}
    DT1 one;
    DT2 two;
};



#endif //COMPILERFEATURES_UTIL_HPP
