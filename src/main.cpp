#include <iostream>
#include <chrono>
#include "sudoku.h"
#include "sudokumaker.h"
#include "dfs.h"
#include "bfs.h"

int select_algorithm(){
    int opcion = -1;
    // Selecciona el metodo para resolver el sudoku
    while(opcion != 0){
        std::cout << "Seleccione un metodo para resolver el problema: " << std::endl;
        std::cout << "[1] Depth first search " << std::endl;
        std::cout << "[2] Best-first search " << std::endl;
        std::cout << "[3] Exit " << std::endl;
        std::cin >> opcion;
        if(opcion == 1 || opcion == 2 || opcion == 3)
            return opcion;
        else
            std::cout << "Ha ingresado una opcion incorrecta por favor intentelo de nuevo" << std::endl;

    }
    return 0;
}


int main() {

    int opcion = select_algorithm();
    State initial; initial.sudoku = sudoku_maker();
    std::cout << "Sudoku inicial : " << std::endl;
    show_sudoku(initial);
    initial.priority = 0;
    State resultado;
    auto start = std::chrono::steady_clock::now();
    if(opcion == 1)
        resultado = dfs(initial);
    //else if(opcion == 2)
        //resultado = bfs(initial);
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    show_sudoku(resultado);
    std::cout << "Tiempo total de ejecucion: " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
    return 0;
    
}
