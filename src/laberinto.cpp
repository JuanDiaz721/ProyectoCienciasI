#include "laberinto.hpp"
#include <algorithm> // Para std::max

Laberinto::Laberinto(const std::vector<std::string>& ln) {
    cargar(ln);
}

bool Laberinto::cargar(const std::vector<std::string>& ln) {
    grid = ln;
    H = (int)grid.size();
    if(H == 0) return false;
    W = 0;
    
    // Encuentra el ancho máximo
    for(auto& s : grid) W = std::max(W, (int)s.size());
    
    int sCount = 0, eCount = 0;
    for(int i = 0; i < H; ++i) {
        auto& s = grid[i];
        // Rellena filas más cortas con espacios
        while((int)s.size() < W) s.push_back(' ');
        
        // Valida caracteres y cuenta S/E
        for(int j = 0; j < W; ++j) {
            char ch = s[j];
            if(!(ch=='#' || ch==' ' || ch=='S' || ch=='E')) return false;
            if(ch == 'S'){ S = {i,j}; sCount++; }
            if(ch == 'E'){ E = {i,j}; eCount++; }
        }
    }
    // El laberinto es válido si hay exactamente un inicio y un fin
    return sCount == 1 && eCount == 1;
}

int Laberinto::filas() const { return H; }
int Laberinto::columnas() const { return W; }
Pos Laberinto::inicio() const { return S; }
Pos Laberinto::salida() const { return E; }

bool Laberinto::dentro(int r, int c) const { 
    return r >= 0 && r < H && c >= 0 && c < W; 
}

bool Laberinto::esPared(int r, int c) const { 
    if(!dentro(r, c)) return true; // Trata fuera de los límites como pared
    return grid[r][c] == '#'; 
}

char Laberinto::celda(int r, int c) const { 
    return grid[r][c]; 
}

std::vector<Pos> Laberinto::vecinos(const Pos& p) const {
    // Direcciones: Arriba, Abajo, Izquierda, Derecha
    static int d4[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}}; 
    
    std::vector<Pos> v;
    v.reserve(4); // Reserva espacio para 4 vecinos como máximo
    
    for(auto& d : d4) {
        int nr = p.r + d[0];
        int nc = p.c + d[1];
        if(dentro(nr, nc) && !esPared(nr, nc)) {
            v.push_back({nr, nc});
        }
    }
    return v;
}