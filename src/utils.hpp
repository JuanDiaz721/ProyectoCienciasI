#pragma once

/**
 * @file utils.hpp
 * @brief Declaraciones de funciones de utilidad para la consola y la aplicación.
 */

// Habilita el modo de terminal virtual VT (para colores ANSI) en Windows
void enableVTMode();

// Habilita UTF-8 en la consola de Windows
void enableUTF8Console();

// Limpia la pantalla de la consola
void clearScreen();

// Pausa la ejecución por un número de milisegundos
void pausaMs(int ms);

/**
 * @brief Genera una clave única (long long) a partir de coordenadas de fila y columna.
 * * Esencial para usar (r, c) como claves en unordered_set y unordered_map.
 * @param r Fila
 * @param c Columna
 * @param W Ancho total del laberinto (para evitar colisiones)
 * @return Clave única de 64 bits.
 */
static inline long long keyRC(int r, int c, int W) { 
    return 1LL * r * W + c; 
}