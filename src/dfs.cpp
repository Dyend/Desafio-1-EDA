#include <queue>
#include <iostream>
#include <stack>
#include <math.h>
#include <list>
#include "sudoku.h"
#include "dfs.h"


long long dfs_priority(Action& a){
    long long priority = pow(10, ( 9- a.cvf)) + pow(10, ( 9-  a.cvr)) + pow(10, ( 9- a.cvc));
    return priority;
}

std::stack<State> reverse_pq(std::priority_queue<State> pq){
    std::stack<State> reversed;
    while(!pq.empty()){
            State sub_estado = pq.top(); pq.pop();
            reversed.push(sub_estado);

    }
    return reversed;
}

State dfs(State& initial){
    std::cout << "Iniciando Depth first search... " << std::endl;
    std::stack<State> s;
    s.push(initial);
    long long contador = -1;
    while(!s.empty()){
        State actual = s.top(); s.pop();
        //std::cout << actual.priority << std::endl;
        //show_sudoku(actual);
        contador++;
        //std::cout << contador << std::endl;
        if(is_final(actual)){
            std::cout << "Total de iteraciones: " << contador << std::endl;
            return actual;
        }
        // obtiene las acciones sin prioridad
        std::list<Action> actions = get_actions(actual);
        // cola para ordenar acciones por la prioridad
        std::priority_queue<State> sub_estados_pq;
        // iterando sobre la lista de acciones
        for(Action a : actions){ 
            long long priority = dfs_priority(a); 
            sub_estados_pq.push(transition(actual, a, priority));
        }
        std::stack<State> sub_estados_stack = reverse_pq(sub_estados_pq);
        // luego que las acciones estan ordenadas en la priority queue son insertadas en la pila
        while(!sub_estados_stack.empty()){
            State sub_estado = sub_estados_stack.top(); sub_estados_stack.pop();
            
            s.push(sub_estado);

        }

        
    }
    return initial;
}
