#pragma once

#include <iostream>
#include <string>

template <typename K, typename V>
struct TPair {  
    K Key;
    V Value;
    TPair(){}
    TPair(K tmpK, V tmpV): 
            Key(tmpK), Value(tmpV){}

};

template <typename K, typename V>
std::istream& operator>>(std::istream& in, TPair<K, V>& p) {
    in >> p.Key >> p.Value;
    return in;
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& out, const TPair<K, V>& p) {
    out << p.Key << '\t' << p.Value;
    return out;
}

template <typename K, typename V>
bool operator< (TPair<K, V> lhs, TPair<K, V> rhs){
    // Для стабильной сортировки сравниваем только ключи
    return lhs.Key < rhs.Key;
}