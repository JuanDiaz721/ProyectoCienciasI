BFS SOLUCIONADOR DE LABERINTOS CON DFS Y BFS

Este es un proyecto de C++ que implementa un solucionador de laberintos visual e interactivo. La aplicación se ejecuta en la terminal (TUI - Text-based User Interface) y utiliza códigos de color ANSI para animar y comparar los algoritmos de Búsqueda en Profundidad (DFS) y Búsqueda en Amplitud (BFS).
El objetivo principal es demostrar visualmente las diferencias fundamentales entre estas dos estrategias de recorrido de grafos: DFS encuentra un camino rápidamente (pero a menudo no el óptimo), mientras que BFS garantiza encontrar el camino más corto.


¿QUE SON DFS Y BFS?

Este proyecto compara dos de los algoritmos más fundamentales para recorrer un grafo (en este caso, el laberinto es un "grafo implícito"):
Búsqueda en Profundidad (DFS - Depth-First Search):
Es un algoritmo que explora "profundamente" en el grafo. Sigue un solo camino hasta que llega a un callejón sin salida, y solo entonces "retrocede" (backtracking) para probar una ruta alternativa. Utiliza una estructura de Pila (LIFO - Last-In, First-Out). Es excelente para determinar si existe un camino, pero no garantiza que el camino encontrado sea el más corto.

Búsqueda en Amplitud (BFS - Breadth-First Search):
Es un algoritmo que explora "por niveles" o "en amplitud". Visita primero el nodo inicial, luego a todos sus vecinos directos, luego a todos los vecinos de esos vecinos, y así sucesivamente. Utiliza una estructura de Cola (FIFO - First-In, First-Out). Su propiedad más importante es que garantiza encontrar el camino más corto (en términos de número de pasos) desde el inicio hasta el fin.


CARACTERISTICAS PRINCIPALES

- Visualización TUI: Interfaz de usuario interactiva que se ejecuta completamente en la consola.
- Animación Paso a Paso: Renderizado en tiempo real de la exploración de los algoritmos.
    \033[46m (Cian): Celda visitada.
    \033[45m (Magenta): Retroceso (Backtracking) de DFS.
    \033[43m (Amarillo): Camino final encontrado por DFS.
    \033[44m (Azul): Camino final (más corto) encontrado por BFS.
- Implementación de DFS: Búsqueda en Profundidad para encontrar el primer camino válido.
- Implementación de BFS: Búsqueda en Amplitud para encontrar el camino más corto garantizado.
- Análisis Comparativo:
    Muestra un "mapa de calor" visual que superpone las celdas exploradas por ambos algoritmos.
    Proporciona una tabla de estadísticas que compara nodos visitados, longitud del camino y tiempo de ejecución.
- Carga de Laberintos: Permite cargar laberintos personalizados desde archivos .txt.
- Código Modular: El proyecto está refactorizado en módulos lógicos (Modelo-Vista-Controlador) para mayor claridad y mantenimiento.


CONCEPTOS CLAVE DEMOSTRADOS

Grafos Implícitos: El laberinto se trata como un grafo donde los nodos son celdas (r, c) y las aristas (vecinos) se calculan al vuelo.
Algoritmos de Recorrido: Implementación de DFS y BFS.
Estructuras de Datos: Uso de Pila (Stack) para DFS y Cola (Queue) para BFS.
Hashing: Uso de std::unordered_map y std::unordered_set para un seguimiento O(1) de celdas visitadas y "padres".
Ingeniería de Software: Separación de la lógica en Interfaz (.hpp) e Implementación (.cpp).


REQUISITOS DE COMPILACION

Un compilador de C++ que soporte C++17 (g++, clang++, MSVC).


INSTRUCCIONES DE COMPILACION

Navega a la carpeta raíz del proyecto en tu terminal y ejecuta:
    # Compila todos los archivos .cpp (nota el "src/") y los enlaza
    g++ src/main.cpp src/utils.cpp src/laberinto.cpp src/busquedas.cpp src/render.cpp src/ui.cpp -o solucionador -std=c++17 -Wall
    # En la terminal ejecuta el comando:
        ./solucionador


INSTRUCCIONES DE USO:

Una vez que el programa solucionador esté en ejecución:
    Se presentará un menú principal en la consola.
    Puedes elegir un laberinto de prueba (1-5) que carga los archivos de la carpeta Laberintos/.
    Puedes cargar un laberinto desde un archivo proporcionando la ruta (ej: Laberintos/maze1_simple.txt).
    El formato de laberinto personalizado debe usar:
    # para paredes.
    (espacio) para caminos libres.
    S para un (1) único punto de inicio.
    E para un (1) único punto de fin.
    Presiona ENTER para avanzar por las diferentes etapas: Animación DFS, Resultado DFS, Animación BFS, Resultado BFS y Comparación final.

