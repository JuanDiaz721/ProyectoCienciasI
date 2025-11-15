#include "busquedas.hpp"
#include "estructuras.hpp" // Para Pila y Cola
#include "render.hpp"      // Para dibujarLaberinto (animación)
#include "utils.hpp"       // Para keyRC y pausaMs

#include <unordered_set>
#include <unordered_map>
#include <algorithm> // Para std::reverse
#include <chrono>    // Para medir el tiempo

// Usamos los namespaces para mantener el código de lógica similar al original
using namespace std;
using namespace chrono;

ResultadoBusqueda Busquedas::DFS(const Laberinto& lab, bool anim, int vel) {
    auto t0 = high_resolution_clock::now();
    ResultadoBusqueda R; 
    const int W = lab.columnas();
    
    Pila<Pos> pila; 
    unordered_set<long long> visit, retro; 
    unordered_map<long long, Pos> parent;
    
    Pos s = lab.inicio(), e = lab.salida();
    pila.push(s);
    unordered_set<long long> setVis; // Para la animación

    while(!pila.estaVacia()) {
        Pos cur = pila.top(); 
        long long kcur = keyRC(cur.r, cur.c, W);
        
        if(!visit.count(kcur)) {
            visit.insert(kcur); 
            R.visitados.push_back(cur); 
            setVis.insert(kcur);
            
            if(anim) { 
                dibujarLaberinto(lab, setVis, retro, {}, "DFS (explorando)"); 
                pausaMs(vel); 
            }
            if(cur == e) break; // Encontrado
        }
        
        bool avanzado = false;
        for(const Pos& nb : lab.vecinos(cur)) {
            long long knb = keyRC(nb.r, nb.c, W);
            if(!visit.count(knb)) { 
                parent[knb] = cur; 
                pila.push(nb); 
                avanzado = true; 
                break; // Característica de DFS: toma el primer camino
            }
        }
        
        if(!avanzado) { // Callejón sin salida: retroceder (backtrack)
            retro.insert(kcur); 
            R.retrocesos.push_back(cur); 
            pila.pop();
            
            if(anim) { 
                dibujarLaberinto(lab, setVis, retro, {}, "DFS (retroceso)"); 
                pausaMs(vel); 
            }
        }
    }
    
    // Si se encontró la salida, reconstruir el camino
    if(visit.count(keyRC(e.r, e.c, W))) {
        vector<Pos> path; 
        Pos cur = e;
        while(!(cur == lab.inicio())) { 
            path.push_back(cur); 
            cur = parent[keyRC(cur.r, cur.c, W)]; 
        }
        path.push_back(lab.inicio()); 
        reverse(path.begin(), path.end());
        
        R.camino = path; 
        R.exito = true;
        
        if(anim) { 
            unordered_set<long long> setCam; 
            for(auto& p : path) setCam.insert(keyRC(p.r, p.c, W));
            dibujarLaberinto(lab, setVis, retro, setCam, "DFS (camino encontrado)"); 
            pausaMs(max(vel, 200)); 
        }
    }
    
    R.tiempoMs = duration_cast<milliseconds>(high_resolution_clock::now() - t0).count();
    return R;
}

ResultadoBusqueda Busquedas::BFS(const Laberinto& lab, bool anim, int vel) {
    auto t0 = high_resolution_clock::now();
    ResultadoBusqueda R; 
    const int W = lab.columnas();
    
    Cola<Pos> q; 
    unordered_set<long long> visit; 
    unordered_map<long long, Pos> parent;
    
    Pos s = lab.inicio(), e = lab.salida();
    q.enqueue(s); 
    visit.insert(keyRC(s.r, s.c, W));
    
    unordered_set<long long> setVis; // Para animación
    setVis.insert(keyRC(s.r, s.c, W)); 
    R.visitados.push_back(s);
    
    if(anim) { 
        dibujarLaberinto(lab, setVis, {}, {}, "BFS (inicio)"); 
        pausaMs(vel); 
    }

    while(!q.estaVacia()) {
        Pos cur = q.dequeue(); 
        if(cur == e) break; // Encontrado
        
        for(const Pos& nb : lab.vecinos(cur)) {
            long long knb = keyRC(nb.r, nb.c, W);
            if(!visit.count(knb)) {
                visit.insert(knb); 
                parent[knb] = cur; 
                q.enqueue(nb);
                
                R.visitados.push_back(nb); 
                setVis.insert(knb);
                
                if(anim) { 
                    dibujarLaberinto(lab, setVis, {}, {}, "BFS (explorando)"); 
                    pausaMs(vel); 
                }
            }
        }
    }
    
    // Si se encontró la salida, reconstruir el camino
    if(visit.count(keyRC(e.r, e.c, W))) {
        vector<Pos> path; 
        Pos cur = e;
        while(!(cur == lab.inicio())) { 
            path.push_back(cur); 
            cur = parent[keyRC(cur.r, cur.c, W)]; 
        }
        path.push_back(lab.inicio()); 
        reverse(path.begin(), path.end());
        
        R.camino = path; 
        R.exito = true;
        
        if(anim) { 
            unordered_set<long long> setCam; 
            for(auto& p : path) setCam.insert(keyRC(p.r, p.c, W));
            dibujarLaberinto(lab, setVis, {}, setCam, "BFS (ruta más corta)"); 
            pausaMs(max(vel, 200)); 
        }
    }
    
    R.tiempoMs = duration_cast<milliseconds>(high_resolution_clock::now() - t0).count();
    return R;
}