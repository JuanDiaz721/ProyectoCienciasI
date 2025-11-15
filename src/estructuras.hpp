#pragma once

/**
 * @file estructuras.hpp
 * @brief Implementaciones de plantillas para Pila (Stack) y Cola (Queue).
 * * Como son plantillas (templates), la implementación completa debe estar
 * en el archivo .hpp para que el compilador pueda instanciarlas.
 */

#include <vector>
#include <deque>
#include <stdexcept> // Para std::runtime_error

// ===================== TDA PILA (STACK) =====================
template<typename T>
class Pila { 
    std::vector<T> a;
public:
    void push(const T& x){ a.push_back(x); }
    T pop(){ 
        if(a.empty()) throw std::runtime_error("Pila vacía"); 
        T x=a.back(); 
        a.pop_back(); 
        return x; 
    }
    T& top(){ 
        if(a.empty()) throw std::runtime_error("Pila vacía"); 
        return a.back(); 
    }
    bool estaVacia() const { return a.empty(); }
    size_t tamano() const { return a.size(); }
};

// ===================== TDA COLA (QUEUE) =====================
template<typename T>
class Cola { 
    std::deque<T> dq;
public:
    void enqueue(const T& x){ dq.push_back(x); }
    T dequeue(){ 
        if(dq.empty()) throw std::runtime_error("Cola vacía"); 
        T x=dq.front(); 
        dq.pop_front(); 
        return x; 
    }
    bool estaVacia() const { return dq.empty(); }
    size_t tamano() const { return dq.size(); }
};