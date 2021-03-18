#include <iostream>

using namespace std;

#include <iostream>
#include <array>
#include <list>
#include <stack>




class State{
public:
   array<char[9][9]> sudoku;
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

list<Action> get_actions(State& s){
    int i, j;
    list<Action> actions;
    /*
    for(i=0;i<N;i++){
        if(s.cols[i]==0){
            for(j=1; j<N+1; j++){
                s.cols[i]=j;
                if(is_valid(s)){
                   Action a; a.col=i; a.row=j;
                   actions.push_back(a);
                }
            }
            s.cols[i]=0;
            return actions;
        }
    }
    */
    return actions;
}
// revisa que no quede ningun casillero en blanco ( en 0 ) del sudoku
bool is_final(State& s){
    int i;
    for(i=0;i<N;i++)
        if(s.cols[i]==0) return false;

    return true;
}

State solve(State& initial){
  stack<State> s;
  s.push(initial);
  while(!s.empty()){
     State actual= s.pop();
     if(is_final(actual)){
         return actual;
     }
     list<Action> actions = get_actions(actual);

     for( Action a : actions)
            s.push(transition(s,a));
  }
  return initial;
}

/* _ representa un casillero vacio*/

void main() {
    // por conveniencia harcodiamos el sudoku para evitar leerlo desde un archivo por ahora
    State initial = {
        {'5', '9', '_' , '_', '1', '3', '8', '2', '6'},
        {'_', '6', '2', '_', '_', '_', '_', '3', '_'},
        {'_', '_', '3', '9', '_', '_', '5', '1', '_'},
        {'_', '_', '8', '_', '_',  '_', '_', '_', '_',},
        {'4', '_', '_', '3', '7', '5', '_', '9', '8',},
        {'7', '3', '5', '_', '_', '1', '2', '_', '_',},
        {'3', '_', '9', '_', '4', '_', '_', '_', '2',},
        {'2', '8', '_', '7', '_', '6', '_', '_',  '_',},
        {'_', '7', '_', '_', '5', '9', '_', '8', '_',},

    };

    State resultado = solve(initial); //busqueda de soluciones
}
