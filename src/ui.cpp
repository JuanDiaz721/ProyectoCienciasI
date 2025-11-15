#include "ui.hpp"
#include "laberinto.hpp"
#include "busquedas.hpp"
#include "render.hpp"
#include "utils.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

// Usamos los namespaces para mantener el código de lógica similar al original
using namespace std;

/**
 * @brief (Función estática de ayuda) Divide un string en líneas.
 */
static vector<string> splitLines(const string& s) {
    vector<string> v; 
    string cur;
    for(char ch : s) {
        if(ch == '\n') { 
            v.push_back(cur); 
            cur.clear(); 
        } else {
            cur.push_back(ch); 
        }
    }
    if(!cur.empty()) v.push_back(cur);
    return v;
}

void UI::ejecutar() {
    while(true) {
        clearScreen();
        cout << "===============================================\n";
        cout << "  SOLUCIONADOR DE LABERINTOS - DFS & BFS (TUI) \n";
        cout << "===============================================\n\n";
        cout << "1) Seleccionar laberinto de prueba\n";
        cout << "2) Cargar laberinto desde archivo\n";
        cout << "3) Salir\n\n";
        cout << "Opción: " << std::flush;

        int op; 
        if(!(cin >> op)) { 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue; 
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
        
        if(op == 3) { 
            cout << "\n¡Hasta pronto!\n" << std::flush; 
            break; 
        }

        vector<string> lineas;
        if(op == 1) {
            cout << "\n=== Laberintos Disponibles ===\n";
            cout << "1) Laberinto Simple (maze1_simple.txt)\n";
            cout << "2) Laberinto Mediano (maze2_medium.txt)\n";
            cout << "3) Laberinto Complejo (maze3_complex.txt)\n";
            cout << "4) Laberinto sin solución (maze4_no_solution.txt)\n";
            cout << "5) Laberinto con ciclos (maze5_loopy_open.txt)\n\n";
            cout << "Seleccione: " << std::flush;
            
            int idx; 
            if(!(cin >> idx)) { 
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                continue; 
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(idx < 1 || idx > 5) { 
                cout << "Opción inválida.\n" << std::flush; 
                pausaMs(1200); 
                continue; 
            }

            // Usamos las rutas de archivo ya que las tenemos
            string rutas[5] = {
                "Laberintos/maze1_simple.txt",
                "Laberintos/maze2_medium.txt",
                "Laberintos/maze3_complex.txt",
                "Laberintos/maze4_no_solution.txt",
                "Laberintos/maze5_loopy_open.txt"
            };
            string ruta = rutas[idx - 1];
            ifstream fin(ruta);
            if(!fin.is_open()) { 
                cout << "No se pudo abrir el archivo de prueba: " << ruta << "\n" << std::flush; 
                pausaMs(2000); 
                continue; 
            }
            string s; 
            while(getline(fin, s)) lineas.push_back(s); 
            fin.close();

        } else if(op == 2) {
            cout << "\nRuta del archivo (ej: Laberintos/mi_lab.txt): " << std::flush;
            string ruta; 
            getline(cin, ruta); 
            ifstream fin(ruta);
            if(!fin.is_open()) { 
                cout << "No se pudo abrir el archivo: " << ruta << "\n" << std::flush; 
                pausaMs(1200); 
                continue; 
            }
            string s; 
            while(getline(fin, s)) lineas.push_back(s); 
            fin.close();
        } else { 
            cout << "\nOpción inválida.\n" << std::flush; 
            pausaMs(1200); 
            continue; 
        }

        Laberinto lab; 
        if(!lab.cargar(lineas)) {
            cout << "\nArchivo/entrada inválida. Asegúrate de tener exactamente un 'S' y un 'E',\n";
            cout << "y usar solo '#', espacio, 'S', 'E'.\n" << std::flush; 
            pausaMs(2500); 
            continue;
        }

        // Configuración de animación
        const int vel = 150; // Velocidad media
        const bool anim = true;

        cout << "\nPresione ENTER para iniciar DFS..." << std::flush; 
        cin.get();
        auto Rdfs = Busquedas::DFS(lab, anim, vel);
        pintarEstadoFinal(lab, Rdfs, "Resultado Final DFS", /*azulCamino*/ false);
        
        cout << "\n-----------------------------------------------\n";
        cout << "  Estadísticas DFS (Backtracking)\n";
        cout << "-----------------------------------------------\n";
        cout << (Rdfs.exito ? "Estado:              OK (camino encontrado)\n"
                           : "Estado:              ERROR (no hay camino)\n");
        cout << "Nodos visitados:     " << Rdfs.visitados.size() << "\n";
        if(Rdfs.exito) cout << "Longitud del camino: " << Rdfs.camino.size() << "\n";
        if(!Rdfs.retrocesos.empty()) cout << "Retrocesos (DFS):    " << Rdfs.retrocesos.size() << "\n";
        cout << "Tiempo (ms):         " << Rdfs.tiempoMs << "\n" << std::flush;

        if(!Rdfs.exito) {
            cout << "\nNo hay camino; no se ejecutará BFS.\n\n";
            cout << "ENTER para volver al menú..." << std::flush; 
            cin.get(); 
            continue;
        }

        cout << "\nENTER para continuar con BFS..." << std::flush; 
        cin.get();
        auto Rbfs = Busquedas::BFS(lab, anim, vel);
        pintarEstadoFinal(lab, Rbfs, "Resultado Final BFS", /*azulCamino*/ true);
        
        cout << "\n-----------------------------------------------\n";
        cout << "  Estadísticas BFS (Ruta más corta)\n";
        cout << "-----------------------------------------------\n";
        cout << (Rbfs.exito ? "Estado:              OK (camino encontrado)\n"
                           : "Estado:              ERROR (no hay camino)\n");
        cout << "Nodos visitados:     " << Rbfs.visitados.size() << "\n";
        if(Rbfs.exito) cout << "Longitud del camino: " << Rbfs.camino.size() << "\n";
        cout << "Tiempo (ms):         " << Rbfs.tiempoMs << "\n" << std::flush;

        cout << "\nENTER para ver comparación..." << std::flush; 
        cin.get();
        mostrarComparacion(lab, Rdfs, Rbfs);

        cout << "\nENTER para volver al menú..." << std::flush; 
        cin.get();
    }
}