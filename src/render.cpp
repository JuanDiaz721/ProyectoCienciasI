#include "render.hpp"
#include "utils.hpp" // Para clearScreen y keyRC
#include <iostream>
#include <iomanip> // Para std::setw (aunque el original usa padding manual)

// Usamos los namespaces para mantener el código de lógica similar al original
using namespace std;

// ===================== RENDER PASO A PASO =====================
void dibujarLaberinto(const Laberinto& lab,
                      const unordered_set<long long>& setVisitados,
                      const unordered_set<long long>& setRetrocesos,
                      const unordered_set<long long>& setCamino,
                      const string& titulo) {
    clearScreen();
    cout << "\n=== " << titulo << " ===\n\n";
    cout << "\033[42m  \033[0m Inicio  \033[41m  \033[0m Salida  \033[46m  \033[0m Visitado  ";
    if(!setRetrocesos.empty()) cout << "\033[45m  \033[0m Retroceso  ";
    cout << "\033[43m  \033[0m Camino\n\n" << std::flush;

    int H = lab.filas(), W = lab.columnas();
    for(int r = 0; r < H; ++r) {
        for(int c = 0; c < W; ++c) {
            char ch = lab.celda(r, c); 
            long long k = keyRC(r, c, W);
            
            if(ch == '#') cout << "\033[40m##\033[0m"; // Pared
            else if(ch == 'S') cout << "\033[42m  \033[0m"; // Inicio
            else if(ch == 'E') cout << "\033[41m  \033[0m"; // Fin
            else if(setCamino.count(k)) cout << "\033[43m  \033[0m"; // Camino
            else if(setRetrocesos.count(k)) cout << "\033[45m  \033[0m"; // Retroceso
            else if(setVisitados.count(k)) cout << "\033[46m  \033[0m"; // Visitado
            else cout << "  "; // Vacío
        } 
        cout << "\n";
    }
    cout << "\n" << std::flush;
}

// ===================== RENDER ESTADO FINAL =====================
void pintarEstadoFinal(const Laberinto& lab,
                       const ResultadoBusqueda& R,
                       const string& titulo,
                       bool azulCamino) {
    unordered_set<long long> setVis, setCam;
    const int W = lab.columnas();
    for (auto& p : R.visitados) setVis.insert(keyRC(p.r, p.c, W));
    for (auto& p : R.camino)   setCam.insert(keyRC(p.r, p.c, W));

    clearScreen();
    cout << "\n=== " << titulo << " ===\n\n";
    cout << (azulCamino ? "\033[44m  \033[0m Camino final (BFS)\n\n"
                        : "\033[43m  \033[0m Camino final (DFS)\n\n");

    for (int r = 0; r < lab.filas(); ++r) {
        for (int c = 0; c < lab.columnas(); ++c) {
            char ch = lab.celda(r, c);
            long long k = keyRC(r, c, W);
            if (ch == '#') cout << "\033[40m##\033[0m";
            else if (ch == 'S') cout << "\033[42m  \033[0m";
            else if (ch == 'E') cout << "\033[41m  \033[0m";
            else if (setCam.count(k)) cout << (azulCamino ? "\033[44m  \033[0m" : "\033[43m  \033[0m");
            else if (setVis.count(k)) cout << "\033[46m  \033[0m";
            else cout << "  ";
        }
        cout << "\n";
    }
    cout << std::flush;
}

// ===================== COMPARACIÓN =====================
void mostrarComparacion(const Laberinto& lab,
                        const ResultadoBusqueda& Rdfs,
                        const ResultadoBusqueda& Rbfs) {
    const int W = lab.columnas();
    unordered_set<long long> vDFS, vBFS, cDFS, cBFS, vAmbos, cAmbos;
    
    for(auto& p : Rdfs.visitados) vDFS.insert(keyRC(p.r, p.c, W));
    for(auto& p : Rbfs.visitados) vBFS.insert(keyRC(p.r, p.c, W));
    for(auto& p : Rdfs.camino)    cDFS.insert(keyRC(p.r, p.c, W));
    for(auto& p : Rbfs.camino)    cBFS.insert(keyRC(p.r, p.c, W));
    
    // Intersecciones
    for(auto x : vDFS) if(vBFS.count(x)) vAmbos.insert(x);
    for(auto x : cDFS) if(cBFS.count(x)) cAmbos.insert(x);

    clearScreen();
    cout << "\n=== Comparación Completa de Exploración ===\n\n";
    cout << "\033[42m  \033[0m Inicio  \033[41m  \033[0m Salida  ";
    cout << "\033[43m  \033[0m Camino DFS  \033[44m  \033[0m Camino BFS  \033[47m\033[30m**\033[0m Camino compartido\n";
    cout << "\033[46m  \033[0m Visitado por ambos  \033[43m\033[2m::\033[0m Solo DFS  \033[44m\033[2m::\033[0m Solo BFS\n\n";

    for(int r = 0; r < lab.filas(); ++r) {
        for(int c = 0; c < lab.columnas(); ++c) {
            char ch = lab.celda(r, c); 
            long long k = keyRC(r, c, W);
            if(ch == '#') cout << "\033[40m##\033[0m";
            else if(ch == 'S') cout << "\033[42m  \033[0m";
            else if(ch == 'E') cout << "\033[41m  \033[0m";
            else if(cDFS.count(k) && cBFS.count(k)) cout << "\033[47m\033[30m**\033[0m"; // Camino compartido
            else if(cDFS.count(k)) cout << "\033[43m  \033[0m"; // Camino DFS
            else if(cBFS.count(k)) cout << "\033[44m  \033[0m"; // Camino BFS
            else if(vAmbos.count(k)) cout << "\033[46m  \033[0m"; // Visitado por ambos
            else if(vDFS.count(k)) cout << "\033[43m\033[2m::\033[0m"; // Visitado solo DFS
            else if(vBFS.count(k)) cout << "\033[44m\033[2m::\033[0m"; // Visitado solo BFS
            else cout << "  ";
        } 
        cout << "\n";
    }

    // Tabla de métricas
    auto pad = [](size_t n) { return string(n < 12 ? 12 - n : 0, ' '); };
    cout << "\n=== Comparación de Métricas ===\n";
    cout << "                      DFS" << pad(3) << "BFS\n";
    cout << "----------------------------------------\n";
    cout << "Nodos visitados:     " << Rdfs.visitados.size()
         << pad(to_string(Rdfs.visitados.size()).size())
         << Rbfs.visitados.size() << "\n";
    cout << "Longitud camino:     " << Rdfs.camino.size()
         << pad(to_string(Rdfs.camino.size()).size())
         << Rbfs.camino.size() << "\n";
    cout << "Tiempo (ms):         " << Rdfs.tiempoMs
         << pad(to_string(Rdfs.tiempoMs).size())
         << Rbfs.tiempoMs << "\n";
    cout << std::flush;
}