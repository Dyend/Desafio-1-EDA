#include <iostream>
#include <array>
#include <list>
#include <stack>

const int SUDOKU_SIZE  = 9;

class State{
public:
    std::array <std::array <char, SUDOKU_SIZE>, SUDOKU_SIZE> sudoku;
};

class Action{
public:
    // La accion se define como poner un numero en un casillero del sudoku(matriz)
    int row, col, numero;
};

void mostrar_sudoku(State &sudoku);

int is_valid(State& s){
    return 1;
}
// dado un estado del sudoku añade un numero a un casillero de este.
State transition(State &s, Action& a){
    State new_state = s;
    new_state.sudoku[a.row][a.col]=a.numero;
    return new_state;
}

std::list<Action> get_actions(State& s){
    int i, j;
    std::list<Action> actions;

    return actions;
}
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
