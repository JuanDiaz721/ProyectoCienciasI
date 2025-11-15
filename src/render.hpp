#pragma once

/**
 * @file render.hpp
 * @brief Declaraciones de funciones para dibujar en la consola.
 */

#include "laberinto.hpp"
#include "busquedas.hpp" // Para ResultadoBusqueda
#include <string>
#include <unordered_set>

/**
 * @brief Dibuja el estado actual del laberinto durante una búsqueda (animación).
 */
void dibujarLaberinto(const Laberinto& lab,
                      const std::unordered_set<long long>& setVisitados,
                      const std::unordered_set<long long>& setRetrocesos,
                      const std::unordered_set<long long>& setCamino,
                      const std::string& titulo);

/**
 * @brief Dibuja el estado final de una búsqueda (resultado).
 */
void pintarEstadoFinal(const Laberinto& lab,
                       const ResultadoBusqueda& R,
                       const std::string& titulo,
                       bool azulCamino);

/**
 * @brief Muestra una visualización y tabla comparativa de DFS y BFS.
 */
void mostrarComparacion(const Laberinto& lab,
                        const ResultadoBusqueda& Rdfs,
                        const ResultadoBusqueda& Rbfs);