#include <array>
#include <iostream>
#include <queue>
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
    return s1.priority > s2.priority;

}

// Re definicion de la comparacion de 2 Actions
bool operator<(const Action& a1, const Action& a2)
{
    /* Compara la prioridad de 2 actions
        la cual fue calculada considerando entre menos casilleros disponibles en la fila,
            columna y region da mayor prioridad */
    return a1.priority > a2.priority;

}


// Re definicion de la comparacion de 2 priority queue con priority queue dentro
bool operator<(const std::priority_queue<Action>& q1, const std::priority_queue<Action>& q2)
{
    // mientras menos elementos tenga tiene mayor prioridad ( osea si tiene menos numeros es mejor)
    int p1;
    int p2;
    if(q1.size() > 0)
        p1 = q1.size()*q1.top().priority;
    else
        p1 = q1.size();
    if(q2.size() > 0)
        p2 = q2.top().priority * q2.size();
    else
        p2 = q2.size();
    return p1 < p2;

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
State transition(State& s, Action& a){
    State new_state = s;
    new_state.sudoku[a.row][a.col]=a.numero;
    new_state.priority = a.priority;
    return new_state;
}

/* Engloba las 3 reglas check column, check row, check region */
bool is_valid_state(State& s, int pos_i, int pos_j, char numero, int& prioridad){
    Cuadrante cuadrante_actual = get_quadrant(pos_i, pos_j);
    int casilleros_vacios_columna = 0, casilleros_vacios_fila = 0, casilleros_vacios_region = 0;

    for(int i = 0; i < s.sudoku.size(); i++){

        for(int j = 0; j < s.sudoku.size(); j++){
            
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
    // Se usa la medida donde menos casilleros disponible tenga fila, columna, region
    prioridad = pow(10, ( 9- casilleros_vacios_fila)) + pow(10, ( 9- casilleros_vacios_region)) + pow(10, ( 9- casilleros_vacios_columna));

    return false;
}

/* Revisa si el numero en el casillero [pos_i][pos_j] está en la misma fila 
   Retorna falso si no esta*/

bool check_row(State& s, int pos_i, int pos_j, char numero){
    for(int i = 0; i < s.sudoku.size(); i++){
        if(s.sudoku[i][pos_j] == numero){
            return true;
        }
    }
    return false;
}
/* Revisa si el numero en el casillero [pos_i][pos_j] está en la misma columna 
   Retorna falso si no esta*/

bool check_column(State& s, int pos_i, int pos_j, char numero){
    for(int i = 0; i < s.sudoku.size(); i++){
        if(s.sudoku[pos_i][i] == numero){
            return true;
        }
    }
    return false;
}


/* Revisa si el numero en el casillero [pos_i][pos_j] está en la misma region 
   Retorna falso si no esta*/
bool check_region(State& s, int pos_i, int pos_j, char numero){
    Cuadrante cuadrante_actual = get_quadrant(pos_i,pos_j);
    for(int i=cuadrante_actual.inicio_fila; i < cuadrante_actual.fin_fila; i++){
        for(int j=cuadrante_actual.inicio_columna; j < cuadrante_actual.fin_columna; j++){
            char numero_en_la_casilla = s.sudoku[i][j];
            if(numero_en_la_casilla == numero){
                return true;
            }
        }
    }
    return false;
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
