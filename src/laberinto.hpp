#pragma once

/**
 * @file laberinto.hpp
 * @brief Define la estructura de Posición (Pos) y la clase Laberinto.
 */

#include <vector>
#include <string>

// Estructura para una posición (coordenada) en el laberinto
struct Pos { 
    int r{0}, c{0}; 
    bool operator==(const Pos& o) const { return r==o.r && c==o.c; } 
};

/**
 * @class Laberinto
 * @brief Modela el laberinto como un grafo implícito.
 * * Almacena la cuadrícula y proporciona métodos para interactuar con ella,
 * como encontrar el inicio, el fin y los vecinos válidos de una posición.
 */
class Laberinto {
    std::vector<std::string> grid; 
    int H{0}, W{0}; 
    Pos S{-1,-1}, E{-1,-1};

public:
    Laberinto()=default; 
    explicit Laberinto(const std::vector<std::string>& ln);
    
    // Carga la cuadrícula desde un vector de strings
    bool cargar(const std::vector<std::string>& ln);
    
    // Getters
    int filas() const;
    int columnas() const;
    Pos inicio() const;
    Pos salida() const;
    char celda(int r, int c) const;

    // Lógica del grafo
    bool dentro(int r, int c) const;
    bool esPared(int r, int c) const;
    std::vector<Pos> vecinos(const Pos& p) const;
};