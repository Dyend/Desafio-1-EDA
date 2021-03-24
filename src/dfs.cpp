#include <queue>
#include <iostream>
#include <stack>
#include "sudoku.h"
#include "dfs.h"

std::priority_queue<Action> get_actions(State& s){
    int i, j;
    std::priority_queue<Action> actions;
    /* Se recorre el sudoku*/
    for(int i = 0; i < s.sudoku.size(); i++){
        for(int j = 0; j < s.sudoku.size(); j++){
            /* Si el casillero esta vacio intentamos
                poner todos los numeros posibles de ese casillero siempre
                 y cuando no este repetido en la fila, columna owa region */
            if(s.sudoku[i][j] == '_'){
                int contador = 0;
                int prioridad;
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

State dfs(State& initial){
    std::cout << "Iniciando Depth first search... " << std::endl;
    std::stack<State> s;
    s.push(initial);
    long long contador = -1;
    while(!s.empty()){
        State actual = s.top(); s.pop();
        //show_sudoku(actual);
        contador++;
        //std::cout << contador << std::endl;
        if(is_final(actual)){
            std::cout << "Total de iteraciones: " << contador << std::endl;
            return actual;
        }
        std::priority_queue<Action> pq_actions = get_actions(actual);
        // iterando sobre la cola de prioridad de acciones
        
        while(!pq_actions.empty()){
            Action a = pq_actions.top(); pq_actions.pop();
            s.push(transition(actual, a));

        }

        
    }
    return initial;
}
