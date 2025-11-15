#include "ui.hpp"
#include "utils.hpp"
#include <iostream>

int main(){
    // Configuración inicial de la consola
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    enableVTMode();
    enableUTF8Console();
    std::cout.setf(std::ios::unitbuf); // Asegura que la salida se muestre inmediatamente
    // Crear y ejecutar la aplicación
    UI app; 
    app.ejecutar();
    return 0;
}