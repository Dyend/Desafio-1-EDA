#include <iostream>
#include <array>
#include <string>
#include <fstream>

const int SUDOKU_SIZE2 = 9;

std::array<std::array<char, SUDOKU_SIZE2>, SUDOKU_SIZE2> init_sudoku(){
  std::array<std::array<char, SUDOKU_SIZE2>, SUDOKU_SIZE2> SUDOKU;
  for (int i = 0; i < SUDOKU_SIZE2; i++){
    std::array<char, SUDOKU_SIZE2> fila;
    for(int j = 0; j < SUDOKU_SIZE2; j++){
      fila[j] = '_';
    }
    SUDOKU[i] = fila;
  }
  return SUDOKU;
}

std::array<std::array<char, SUDOKU_SIZE2>, SUDOKU_SIZE2> sudoku_maker()
{
  std::array<std::array<char, SUDOKU_SIZE2>, SUDOKU_SIZE2> SUDOKU = init_sudoku();
  std::array<char, SUDOKU_SIZE2> fila;
  std::fstream myfile;
  std::string line, value, index;
  int x, y;
  int startdelimiter = 0, stopdelimiter = 0;
  int novena_casilla = 0;
  int index_inicial=-1, index_actual=0;
  int size = SUDOKU_SIZE2;
  myfile.open("sudoku.txt");
  if (myfile.is_open()){
    while (std::getline(myfile,line)){
      if (line.find("solution") != std::string::npos){
        break;
      }
      if (line.find("index") != std::string::npos){
        startdelimiter = line.find(">");
        startdelimiter ++;
        stopdelimiter = line.find("</index>");
        index = line.substr(startdelimiter, stopdelimiter - startdelimiter);
        index_actual = stoi(index);
        x = index_actual / size;
        y = index_actual % size;
        std::getline(myfile,line);
        if (line.find("value") != std::string::npos){
          startdelimiter = line.find(">");
          startdelimiter ++;
          stopdelimiter = line.find("</value>");
          value = line.substr(startdelimiter, stopdelimiter - startdelimiter);
          SUDOKU[x][y] = value[0];
        } 
      }
    }
    myfile.close();
  }
  else{
    std::cout <<"Unable to open file"<< "\n";
  }
  return SUDOKU;
}