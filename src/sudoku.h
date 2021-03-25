#include <array>
#include <queue>
#include <list>
#ifndef SUDOKU_H
#define SUDOKU_H

const int SUDOKU_SIZE = 9;

class Cuadrante{
    public:

    int inicio_fila, fin_fila;
    int inicio_columna, fin_columna;
};

class State{
    public:

    std::array <std::array <char, SUDOKU_SIZE>, SUDOKU_SIZE> sudoku;
    long long priority;
    long long id;
};

class Action{
public:
    // La accion se define como poner un numero en un casillero del sudoku(matriz)
    int row, col;
    char numero;
    // casilleros vacios columna, casilleros vacios fila, casilleros vacios region 
    int cvc, cvf, cvr;
    long long id;

};

bool operator<(const State& s1, const State& s2);

bool operator<(const Action& a1, const Action& a2);

bool operator<(const std::priority_queue<Action>& q1, const std::priority_queue<Action>& q2);

void show_sudoku(State& s);

Cuadrante get_quadrant(int pos_i, int pos_j);

State transition(State& s, Action& a, long long& priority);

bool is_valid_state(State& s, int pos_i, int pos_j, char numero, int& cvf, int& cvc, int& cvr);

std::list<Action> get_actions(State& s);

bool check_row(State& s, int pos_i, int pos_j, char numero);

bool check_column(State& s, int pos_i, int pos_j, char numero);

bool check_region(State& s, int pos_i, int pos_j, char numero);

bool is_final(State& s);

#endif