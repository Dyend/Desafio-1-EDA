#include <iostream>
#include <array>
#include <list>
#include <stack>

const int SUDOKU_SIZE  = 9;

class Cuadrante{
    public:

    int inicio_fila, fin_fila;
    int inicio_columna, fin_columna;
};

class State{
    public:

    std::array <std::array <char, SUDOKU_SIZE>, SUDOKU_SIZE> sudoku;
};

class Action{
public:
    // La accion se define como poner un numero en un casillero del sudoku(matriz)
    int row, col, numero;
};


// dado un estado del sudoku añade un numero a un casillero de este.
State transition(State &s, Action& a){
    State new_state = s;
    new_state.sudoku[a.row][a.col]=a.numero;
    return new_state;
}

/* Revisa si el numero en el casillero [pos_i][pos_j] está en la misma fila 
   Retorna falso si no esta*/

bool check_row(State& s, int pos_i, int pos_j, int numero){
    for(int i = 0; i < s.sudoku.size(); i++){
        if(s.sudoku[i][pos_j] == numero){
            return true;
        }
    }
    return false;
}
/* Revisa si el numero en el casillero [pos_i][pos_j] está en la misma columna 
   Retorna falso si no esta*/

bool check_column(State& s, int pos_i, int pos_j, int numero){
    for(int i = 0; i < s.sudoku.size(); i++){
        if(s.sudoku[pos_i][i] == numero){
            return true;
        }
    }
    return false;
}

/* Retorna el cuadrante al cual pertenece un casillero*/
Cuadrante get_quadrant(int pos_i, int pos_j){
    Cuadrante cuadrante_actual;
    if(pos_i>5){
        cuadrante_actual.inicio_fila = 6;
        cuadrante_actual.fin_fila = 8;
    }
    else if (pos_i>3){
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
    else if (pos_j>3){
        cuadrante_actual.inicio_columna = 3;
        cuadrante_actual.fin_columna = 5;
    }
    else {
        cuadrante_actual.inicio_columna = 0;
        cuadrante_actual.fin_columna = 2;
    }
    return cuadrante_actual;
}

/* Revisa si el numero en el casillero [pos_i][pos_j] está en la misma region 
   Retorna falso si no esta*/
bool check_region(State& s, pos_i, pos_j, int numero){
    Cuadrante cuadrante_actual = get_quadrant(pos_i,pos_j);
    for(int i=cuadrante_actual.inicio_fila; i < cuadrante_actual.fin_fila; i++){
        for(int j=cuadrante_actual.inicio_columna; j < cuadrante_actual.fin_columna; j++){
            int numero_en_la_casilla = s[i][j];
            if(numero_en_la_casilla == numero){
                return true;
            }
    }
    return false;
}

/* Esto no esta terminado*/
std::list<Action> get_actions(State& s){
    int i, j;
    std::list<Action> actions;
    /* Se recorre el sudoku*/
    for(int i = 0; i < s.sudoku.size(); i++){
        for(int j = 0; j < s.sudoku.size(); j++){
            /* Si el casillero esta vacio intentamos
                poner todos los numeros posibles de ese casillero siempre
                 y cuando no este repetido en la fila, columna o region */
            if(s.sudoku[i][j] == '_'){
                for(int numero = 1; numero < 10 ; numero ++){
                    if(!check_region(s, i, j, numero) && !check_row(s, i, j, numero) && !check_column(s, i, j, numero)){
                        Action action;
                        action.numero = numero;
                        action.row = i;
                        action.col = j;
                        actions.push_back(action);
                    }
                    
                }
            }
        }
    }
    return actions;
}
/* Imprime el sudoku*/
void show_sudoku(State& s){
    for(int i = 0; i < s.sudoku.size(); i++){
        for(int j = 0; j < s.sudoku.size(); j++){
            std::cout << s.sudoku[i][j] << "\t";
        }
        std::cout << '\n';

    }
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

State solve(State& initial){
    std::stack<State> s;
    s.push(initial);
    while(!s.empty()){
    State actual = s.top(); s.pop();
    if(is_final(actual)){
        return actual;
    }
    std::list<Action> actions = get_actions(actual);
    for( Action a : actions)
        s.push(transition(actual, a));
    }
    return initial;
}


std::array<std::array<char, SUDOKU_SIZE>, SUDOKU_SIZE> get_data(){
    // por conveniencia harcodiamos el sudoku para evitar leerlo desde un archivo por ahora
    /* _ representa un casillero vacio*/
    std::array<std::array<char, SUDOKU_SIZE>, SUDOKU_SIZE> initial = {{
        {'5', '9', '_' , '_', '1', '3', '8', '2', '6'},
        {'_', '6', '2', '_', '_', '_', '_', '3', '_'},
        {'_', '_', '3', '9', '_', '_', '5', '1', '_'},
        {'_', '_', '8', '_', '_',  '_', '_', '_', '_',},
        {'4', '_', '_', '3', '7', '5', '_', '9', '8',},
        {'7', '3', '5', '_', '_', '1', '2', '_', '_',},
        {'3', '_', '9', '_', '4', '_', '_', '_', '2',},
        {'2', '8', '_', '7', '_', '6', '_', '_',  '_',},
        {'_', '7', '_', '_', '5', '9', '_', '8', '_',}}};
    return initial;
}


int main() {
    
    State initial; initial.sudoku = get_data(); 
    State resultado = solve(initial); //busqueda de soluciones
    show_sudoku(resultado);
    return 0;
}
