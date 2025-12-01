#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

int parseRotation(std::string rotation){
  int dir = 1;
  int length = 0;
  if (rotation[0] == 'L') { dir = -1; }
  for(std::string::const_iterator it = rotation.begin()+1; it != rotation.end(); ++it){
    length++;
  }
  return std::stoi(rotation.substr(1,length))*dir;
}

class Dial{
  int _iStartPos;
  int _iMaxValue;
  int _iMinValue;
  int _iCurrPos; 
  int _iPsswrd = 0;
public:
  Dial() : _iStartPos(50), _iMaxValue(99), _iMinValue(0) { 
    _iCurrPos = _iStartPos;
  }
  Dial(int iStartPos, int iMaxValue, int iMinValue) : _iStartPos(iStartPos), _iMaxValue(iMaxValue), _iMinValue(iMinValue) {  
    _iCurrPos = _iStartPos;
  }
  //modular arithmetic 
  //e.g. with safe LX increments by X 
  //               RX decrements by X
  //e.g. Pos: 99, L1 -> 0, Pos: 1, R2 -> 99
  //so this should work for numbers up to 
  void turnDial(int rotation){
    //version 2 
    int remainder = rotation - (rotation/(_iMaxValue+1))*(_iMaxValue+1);
    _iPsswrd+=(abs(rotation)/(_iMaxValue+1));
    if ((_iCurrPos + remainder > _iMaxValue) || (_iCurrPos + remainder < _iMinValue))  {
      if (_iCurrPos + remainder != _iMinValue && _iCurrPos + remainder != (_iMaxValue + 1) && _iCurrPos != 0) { _iPsswrd++; } 
    }
    _iCurrPos = (_iCurrPos + rotation) % (_iMaxValue + 1);
    if (_iCurrPos < 0) { _iCurrPos = (_iMaxValue+1) + _iCurrPos; }
     
    if (_iCurrPos == 0) { _iPsswrd++; }
    //printf("Current Position: %d \t Zeros: %d \n", _iCurrPos, _iPsswrd);
    //version 1
    /*
    //printf("Curr Pos: %d \t with rotation: %d",_iCurrPos, rotation); 
    if ((_iCurrPos + rotation) < _iMinValue) {
      rotation = (_iMaxValue+1) + rotation%(_iMaxValue+1);
    }
    _iCurrPos = (_iCurrPos + rotation%(_iMaxValue+1)) % (_iMaxValue + 1); 
    if (_iCurrPos == 0) { _iPsswrd++; }
    */
    //printf("\t Curr Pos after rotation: %d \t crossing zero %d times\n",_iCurrPos, _iPsswrd); 
  };

  int getPsswrd(){
    return this->_iPsswrd;
  }
};

int main() {
  // Advent of Code 2025 - Day 01
  // Part 1:
  // get inputs 
  std::string filename = "./inputs/day01.txt";
  std::ifstream ifs(filename);
  if(!ifs) { return -1; }

  Dial dial; 
  int rotation = 0;  
  std::string line;

  while(getline(ifs, line)){
    rotation = parseRotation(line);
    dial.turnDial(rotation); 
  }
  printf("Password %d\n",dial.getPsswrd());

  return 0;
}
