#pragma once

/**
 * @file busquedas.hpp
 * @brief Define el struct ResultadoBusqueda y la clase estática Busquedas.
 */

#include "laberinto.hpp" // Necesita la definición de Laberinto y Pos
#include <vector>

// Estructura para almacenar los resultados de una búsqueda
struct ResultadoBusqueda {
    std::vector<Pos> camino;      // Camino final de S a E
    std::vector<Pos> visitados;   // Todas las celdas visitadas en orden
    std::vector<Pos> retrocesos;  // Solo para DFS: celdas de donde retrocedió
    long long tiempoMs{0};        // Duración de la búsqueda
    bool exito{false};            // Si se encontró la salida
};

/**
 * @class Busquedas
 * @brief Contiene los algoritmos estáticos DFS y BFS para resolver el laberinto.
 */
class Busquedas {
public:
    /**
     * @brief Resuelve el laberinto usando Búsqueda en Profundidad (DFS).
     * @param lab El laberinto a resolver.
     * @param anim Si se debe animar paso a paso.
     * @param vel Velocidad de animación en ms.
     * @return Un struct ResultadoBusqueda con los hallazgos.
     */
    static ResultadoBusqueda DFS(const Laberinto& lab, bool anim = true, int vel = 150);

    /**
     * @brief Resuelve el laberinto usando Búsqueda en Amplitud (BFS).
     * @param lab El laberinto a resolver.
     * @param anim Si se debe animar paso a paso.
     * @param vel Velocidad de animación en ms.
     * @return Un struct ResultadoBusqueda con los hallazgos.
     */
    static ResultadoBusqueda BFS(const Laberinto& lab, bool anim = true, int vel = 150);
};