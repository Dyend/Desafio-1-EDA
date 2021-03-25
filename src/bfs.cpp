#include <queue>
#include <iostream>
#include <list>
#include <set>
#include <math.h>
#include "sudoku.h"
#include "bfs.h"



long long bfs_priority(Action& a, State& previous){
    long long priority = previous.priority + pow(10, ( 9- a.cvf)) + pow(10, ( 9-  a.cvr)) + pow(10, ( 9- a.cvc));
    return priority;
}

State bfs(State& initial){
    std::cout << "Iniciando Best first search... " << std::endl;
    std::priority_queue<State> s;
    std::set<long long> visited;

    s.push(initial);
    long long contador = -1;
    while(!s.empty()){
        State actual = s.top(); s.pop();
        if(visited.find(actual.id) != visited.end() )
            continue;
        visited.insert(actual.id);
        std::cout << "State ID: " << actual.id << std::endl;
        std::cout << "Priority actual : " << actual.priority << std::endl;
        std::cout << "PQ size : " << s.size() << std::endl;
        std::cout << "Visited size : " << visited.size() << std::endl;
        contador++;
        //std::cout << contador << std::endl;
        if(is_final(actual)){
            std::cout << "Total de iteraciones: " << contador << std::endl;
            return actual;
        }
        std::list<Action> actions = get_actions(actual);

        for(Action a : actions){ 
            long long priority = bfs_priority(a, actual); 
            s.push(transition(actual, a, priority));
        }

        
    }
    return initial;
}
