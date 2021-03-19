#include <iostream>
#include <array>
#include <list>
#include <stack>
#include <queue>
#include <math.h>

const int SUDOKU_SIZE  = 9;

class Cuadrante{
    public:

    int inicio_fila, fin_fila;
    int inicio_columna, fin_columna;
};

class State{
    public:

    std::array <std::array <char, SUDOKU_SIZE>, SUDOKU_SIZE> sudoku;
    int priority;

};

class Action{
public:
    // La accion se define como poner un numero en un casillero del sudoku(matriz)
    int row, col;
    char numero;
    int priority;

};

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

std::priority_queue<Action> get_actions(State& s){
    int i, j;
    /* Cola de prioridad que contiene una cola de prioridad por cada casillero vacio del sudoku,
        la prioridad la tiene el que tenga menos posibilidades por casillero */
    std::priority_queue<Action> actions;
    /* Se recorre el sudoku*/
    for(int i = 0; i < s.sudoku.size(); i++){
        for(int j = 0; j < s.sudoku.size(); j++){
            /* Si el casillero esta vacio intentamos
                poner todos los numeros posibles de ese casillero siempre
                 y cuando no este repetido en la fila, columna o region */
            if(s.sudoku[i][j] == '_'){
                int contador = 0;
                int prioridad;
                // sub cola de prioridad que contiene los numeros posibles para un casillero
                for(int n = 1; n < 10 ; n ++){
                    // int to char
                    char numero = '0' + n;
                    if(!is_valid_state(s, i, j , numero, prioridad)){
                        Action action;
                        action.numero = numero;
                        action.row = i;
                        action.col = j;
                        action.priority = prioridad;
                        actions.push(action);
                        contador++;
                    }
                    
                }
                if(contador == 0){
                    std::priority_queue<Action> empty;
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

State solve(State& initial){
    std::stack<State> s;
    s.push(initial);
    long long contador = -1;
    while(!s.empty()){
        State actual = s.top(); s.pop();
        //show_sudoku(actual);
        contador++;
        std::cout << contador << std::endl;
        if(is_final(actual)){
            std::cout << contador << std::endl;
            return actual;
        }
        std::priority_queue<Action> pq_actions = get_actions(actual);
        // iterando sobre la cola de prioridad de cola de prioridades de acciones
        
        while(!pq_actions.empty()){
            Action a = pq_actions.top(); pq_actions.pop();
            s.push(transition(actual, a));

        }

        
    }
    return initial;
}


std::array<std::array<char, SUDOKU_SIZE>, SUDOKU_SIZE> get_data(){
    // por conveniencia harcodiamos el sudoku para evitar leerlo desde un archivo por ahora
    /* _ representa un casillero vacio*/
    std::array<std::array<char, SUDOKU_SIZE>, SUDOKU_SIZE> initial = {{
        {'_', '3', '5' , '_', '_', '7', '2', '_', '4'},
        {'9', '_', '_', '_', '_', '8', '3', '_', '_'},
        {'4', '8', '6', '3', '_', '2', '5', '7', '_'},
        {'6', '_', '3', '8', '_',  '_', '9', '2', '5',},
        {'7', '_', '_', '_', '_', '_', '_', '3', '_',},
        {'8', '_', '2', '5', '4', '3', '_', '6', '7',},
        {'3', '_', '_', '6', '_', '_', '_', '5', '2',},
        {'2', '6', '_', '_', '3', '5', '_', '_',  '_',},
        {'_', '7', '_', '_', '_', '_', '_', '4', '_',}}};
    return initial;
}


int main() {
    
    State initial; initial.sudoku = get_data(); 
    initial.priority = 0;
    State resultado = solve(initial); //busqueda de soluciones
    show_sudoku(resultado);
    return 0;
}
