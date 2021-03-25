#include <array>
#include <iostream>
#include <queue>
#include <list>
#include "sudoku.h"
#include <math.h>

/* Imprime el sudoku*/
void show_sudoku(State& s){
    for(int i = 0; i < s.sudoku.size(); i++){
        for(int j = 0; j < s.sudoku.size(); j++){
            std::cout << s.sudoku[i][j] << "\t";
        }
        std::cout << '\n';

    }
    std::cout << "----------------------------------------------------------------------------------------------" << std::endl;
}


// Re definicion de la comparacion de 2 Actions
bool operator<(const State& s1, const State& s2)
{
    /* Compara la prioridad de 2 state
        la cual fue calculada considerando entre menos casilleros disponibles en la fila,
            columna y region da mayor prioridad */
    return s1.priority < s2.priority;

}



/* Retorna el cuadrante al cual pertenece un casillero*/
Cuadrante get_quadrant(int pos_i, int pos_j){
    Cuadrante cuadrante_actual;
    if(pos_i>5){
        cuadrante_actual.inicio_fila = 6;
        cuadrante_actual.fin_fila = 8;
    }
    else if (pos_i>2){
        cuadrante_actual.inicio_fila = 3;
        cuadrante_actual.fin_fila = 5;
    }
    else {
        cuadrante_actual.inicio_fila = 0;
        cuadrante_actual.fin_fila = 2;
    }

    if(pos_j>5){
        cuadrante_actual.inicio_columna = 6;
        cuadrante_actual.fin_columna = 8;
    }
    else if (pos_j>2){
        cuadrante_actual.inicio_columna = 3;
        cuadrante_actual.fin_columna = 5;
    }
    else {
        cuadrante_actual.inicio_columna = 0;
        cuadrante_actual.fin_columna = 2;
    }
    return cuadrante_actual;
}

// dado un estado del sudoku añade un numero a un casillero de este.
State transition(State& s, Action& a, long long& priority){
    State new_state = s;
    new_state.sudoku[a.row][a.col]=a.numero;
    new_state.id = a.id;
    new_state.priority = priority;
    return new_state;
}

long long identificador_casillero(State& s, char& casillero, int& pos_i, int& pos_j){
    long long identificador;
    int casillero_int;
    if(casillero != '_'){
        casillero_int = casillero - '0';
        // char to int 
        identificador =  (casillero_int + 1) * pow(10, pos_i) * (pos_j + 1);
    }else{
        identificador = pow(10, pos_i) * (pos_j + 1);
    }
    return identificador;
}

/* Engloba las 3 reglas check column, check row, check region */
bool is_valid_state(State& s, int pos_i, int pos_j, char numero, int& cvf, int& cvc, int& cvr, long long& id){
    Cuadrante cuadrante_actual = get_quadrant(pos_i, pos_j);
    int casilleros_vacios_columna = 0, casilleros_vacios_fila = 0, casilleros_vacios_region = 0;
    
    for(int i = 0; i < s.sudoku.size(); i++){

        for(int j = 0; j < s.sudoku.size(); j++){
            if(i == pos_i && j == pos_j)
                id += identificador_casillero(s, numero, i , j);
            else
                id += identificador_casillero(s, s.sudoku[i][j], i , j);

            // Check row rule (misma fila distinta columna)
            if(i == pos_i){
                if(s.sudoku[i][j] == numero){
                    return true;
                }
                else if(s.sudoku[i][j] == '_'){
                    casilleros_vacios_fila++;
                }
            }
            // Check column rule (misma columna distinta fila)
            if(j == pos_j){
                if(s.sudoku[i][j] == numero){
                    return true;
                }
                else if(s.sudoku[i][j] == '_'){
                    casilleros_vacios_columna++;
                }
            }

            // Check region rule
            if(i >= cuadrante_actual.inicio_fila && i <= cuadrante_actual.fin_fila && j >= cuadrante_actual.inicio_columna && j <= cuadrante_actual.fin_columna){
                if(s.sudoku[i][j] == numero)
                    return true;
                else if(s.sudoku[i][j] == '_')
                    casilleros_vacios_region++;
            }

        }
    }
    
    cvc = casilleros_vacios_columna;
    cvf = casilleros_vacios_fila;
    cvr = casilleros_vacios_region;

    

    return false;
}


std::list<Action> get_actions(State& s){
    int i, j;
    std::list<Action> actions;
    /* Se recorre el sudoku*/
    for(int i = 0; i < s.sudoku.size(); i++){
        for(int j = 0; j < s.sudoku.size(); j++){
            /* Si el casillero esta vacio intentamos
                poner todos los numeros posibles de ese casillero siempre
                 y cuando no este repetido en la fila, columna owa region */
            if(s.sudoku[i][j] == '_'){
                int contador = 0;
                int cvf, cvc, cvr;
                long long id = 0;
                for(int n = 1; n < 10 ; n ++){
                    // int to char
                    char numero = '0' + n;
                    if(!is_valid_state(s, i, j , numero, cvf, cvc, cvr, id)){
                        Action action;
                        action.numero = numero;
                        action.row = i;
                        action.col = j;
                        action.cvc = cvc;
                        action.cvf = cvf;
                        action.cvr = cvr;
                        action.id = id;
                        actions.push_back(action);
                        contador++;
                    }
                    
                }
                if(contador == 0){
                    std::list<Action> empty;
                    return empty;
                }

            }
        }
    }
    return actions;
}
// revisa que no quede ningun casillero en blanco ( en 0 ) del sudoku
bool is_final(State& s){

    for(int i = 0; i < s.sudoku.size(); i++){
        for(int j = 0; j < s.sudoku.size(); j++){
            if(s.sudoku[i][j] == '_')
                return false;
        }

    }

    return true;
}
