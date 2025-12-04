#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

class Wall {
  int* _iSlot; 
  int _iRows;
  int _iColumns;
public:
  Wall(){}
  Wall(int* slots, int rows, int columns) : _iRows(rows+2), _iColumns(columns+2) {
    _iSlot = new int[_iColumns * _iRows];

    for(int i = 0; i < this->_iRows; i++){
      _iSlot[(i * _iColumns)] = 0;
      _iSlot[(i * _iColumns) + _iColumns - 1] = 0;
    }
    for(int j = 0; j < this->_iRows; j++){
      _iSlot[j] = 0;
      _iSlot[((_iRows - 1) * _iColumns) + j ] = 0;
    }

    for(int i = 1; i < this->_iRows-1; i++){
      for(int j = 1; j < this->_iColumns-1; j++){
        _iSlot[(i * _iColumns) + j] = slots[((i-1) * columns) + (j-1)];
      }
    }
  }; 
  
  int findAccessible(int positions){
    int adjacent = 0;
    int removable = 0;
    for (int i = 1; i < this->_iRows-1; i++){
      for  (int j = 1; j < this->_iColumns-1; j++){
        adjacent += (*this)(i-1, j) + (*this)(i+1, j) + (*this)(i, j+1) + (*this)(i,j-1);
        adjacent += (*this)(i-1, j-1) + (*this)(i+1, j+1) + (*this)(i-1, j+1) + (*this)(i+1,j-1);
        if (adjacent < positions && (*this)(i,j) > 0 ) { 
          removable++; 
          //std::cout << "x";
        } else { 
          //if ((*this)(i,j) > 0) { std::cout << "@"; } else {std::cout << "."; }
        }
        adjacent = 0; 
      }
      //std::cout << std::endl;
    }
    return removable;
  }
  int& operator()(int i, int j) {
      return _iSlot[(i * _iColumns) + j];
  }

  const int& operator()(int i, int j) const {
      return _iSlot[(i * _iColumns) + j];
  }
};


int main() {
  std::string filename = "./inputs/day04.txt";
  std::ifstream ifs(filename);
  if(!ifs) { return -1; }
  std::string line;
  int rows = 0;
  int columns = 0;
  int positions = 0;
  std::vector<int> slots;
  while(getline(ifs, line)){
    for(std::string::iterator iter = line.begin(); iter != line.end(); iter++){
      positions++;
      //std::cout << *iter;
      if(*iter - '@' == 0) {
        slots.push_back(1);
      } else {
        slots.push_back(0);
      }
    }
    //std::cout << std::endl;
    rows++;
  }

  columns = positions/rows;
  int* slotsArray = new int[rows * columns] {};

  for(int i =0; i < slots.size(); i++){
    slotsArray[i] = slots[i];
  }

  Wall wall(slotsArray, rows, columns);
  std::cout << "available positions: "  << std::endl << wall.findAccessible(4);  


  // Part 2:


  return 0;
}
