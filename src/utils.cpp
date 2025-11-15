#include "utils.hpp"
#include <iostream>
#include <thread>
#include <chrono>

// Manejo específico para Windows
#ifdef _WIN32
  #include <windows.h>
  void enableVTMode() {
      HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
      if (hOut == INVALID_HANDLE_VALUE) return;
      DWORD mode = 0;
      if (!GetConsoleMode(hOut, &mode)) return;
      mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
      SetConsoleMode(hOut, mode);
  }
  void enableUTF8Console() {
      SetConsoleOutputCP(CP_UTF8);
      SetConsoleCP(CP_UTF8);
  }
#else
  // En otros sistemas (Linux, macOS), esto suele funcionar por defecto.
  void enableVTMode() {}
  void enableUTF8Console() {}
#endif

// Funciones multiplataforma
void clearScreen() { 
    std::cout << "\x1b[2J\x1b[H" << std::flush; 
}

void pausaMs(int ms) { 
    if (ms > 0) 
        std::this_thread::sleep_for(std::chrono::milliseconds(ms)); 
}