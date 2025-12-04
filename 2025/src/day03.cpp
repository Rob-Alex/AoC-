#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include <sstream>

class Battery {
  int _iPos; 
  int _iJoltage;
public:
  Battery() { };
  Battery(int pos, int joltage) : _iPos(pos), _iJoltage(joltage) {};
  int getPos(){ return _iPos; }
  int getJoltage() { return _iJoltage; }
  void setPos(int pos) { this->_iPos = pos; }
  void setJoltage(int joltage) { this->_iJoltage = joltage; }
};

struct BatteryNode {
  BatteryNode* _pNext;
  BatteryNode* _pPrev;
  Battery* _pBattery; 
};

class BatteryList {
  BatteryNode* _pHead;
  BatteryNode* _pTail;
public:
  BatteryList() { 
    _pHead = nullptr;
    _pTail = nullptr; 
  }
  void push_back(Battery* b){
    BatteryNode* newNode = new BatteryNode;
    newNode->_pBattery = b;
    if (_pHead == nullptr){
      newNode->_pNext = nullptr;
      newNode->_pPrev = nullptr;
      _pHead = newNode;
      _pTail = newNode;
    } else {
      _pTail->_pNext = newNode; 
      newNode->_pPrev = _pTail;
      newNode->_pNext = nullptr;
      _pTail = newNode; 
    }
  }
  BatteryNode* getHead(){
    return _pHead;
  }
  BatteryNode* getTail(){
    return _pTail;
  } 

  // find the battery joltage (part 1) 
  /*int makeBattery(){
    BatteryNode* firstBatteryNode = _pHead;
    BatteryNode* secondBatteryNode = _pTail;
    for (BatteryNode* iter = _pHead->_pNext; iter != _pTail; iter = iter->_pNext){
      if (firstBatteryNode->_pBattery->getJoltage() < iter->_pBattery->getJoltage()){
        firstBatteryNode = iter; 
      } 
    }
    for (BatteryNode* iter = _pTail; iter != firstBatteryNode; iter = iter->_pPrev){
      if (secondBatteryNode->_pBattery->getJoltage() < iter->_pBattery->getJoltage()){
        secondBatteryNode = iter;
      }
    }
    return (firstBatteryNode->_pBattery->getJoltage() * 10) + (secondBatteryNode->_pBattery->getJoltage());
  }*/

  void empty(){
    BatteryNode* currBattery = _pHead;
    while(currBattery != nullptr){
      BatteryNode* next = currBattery->_pNext;
      delete currBattery->_pBattery;
      delete currBattery;
      currBattery = next; 
    }
    _pHead = nullptr;
    _pTail = nullptr;
  }
  std::string toString(){
    std::stringstream ss;
    for (BatteryNode* iter = _pHead; iter != nullptr; iter = iter->_pNext){
      ss << iter->_pBattery->getJoltage();
    }
    return ss.str();
  }
};

//987654321111111
//811111111111119
//234234234234278
//818181911112111
//forward iteration  
/*
int makeBattery(BatteryList batteries, int positions){ 
    BatteryList bigBatteries;
    
    BatteryNode* minimumPosition;  
    int filled_spaces = 0;
    while (filled_spaces < positions){
      minimumPosition = batteries.getTail()->_pPrev;
      for (int i = 0; i <= (positions - filled_spaces); i++){
        minimumPosition = minimumPosition->_pPrev;
      }
      BatteryNode* current = minimumPosition; 
      for (BatteryNode* iter = minimumPosition; iter != nullptr; iter = iter->_pPrev){
        if (current->_pBattery->getJoltage() < iter->_pBattery->getJoltage()){ 
          //std::cout << iter->_pBattery->getJoltage() << ","; 
          minimumPosition = iter;
        }
      }
      current = minimumPosition;
      //for (BatteryNode* iter = minimumPosition; iter != nullptr; iter = iter->_pNext){
      //  if(current->_pBattery->getJoltage() < iter->_pBattery->getJoltage()){
          //current = iter;
      //  }
      //}
      bigBatteries.push_back(current->_pBattery);
      filled_spaces++;
    }
    std::cout << "big batteries: " << bigBatteries.toString();
    return 0;
}*/

//part 2 solution
unsigned long long makeBattery(BatteryList batteries, int position){
  BatteryList bigBatteries;
  int filled_spaces = 0;
  BatteryNode* start = batteries.getHead();

  while(filled_spaces < position){
    int remaining = position - filled_spaces;
    BatteryNode* endNode = batteries.getTail();
    for (int i = 0; i < (remaining - 1); i++){
      endNode = endNode->_pPrev;
    }
    BatteryNode* maxNode = start;
    for(BatteryNode* iter = start; iter != endNode->_pNext; iter = iter->_pNext){
      if (maxNode->_pBattery->getJoltage() < iter->_pBattery->getJoltage()){
        maxNode = iter;
      }
    }
    bigBatteries.push_back(maxNode->_pBattery);

    start = maxNode->_pNext;
    filled_spaces++;
  }
  return std::stol(bigBatteries.toString());
}

int main() {

  std::string filename = "./inputs/day03.txt";
  std::ifstream ifs(filename);
  if(!ifs) { return -1; }

  std::string line;

  unsigned long long totalJoltage = 0;
  BatteryList batteries; 
  while(getline(ifs, line)){
    int position = 0;
    for(std::string::iterator it = line.begin() ; it != line.end(); it++){
      Battery* new_entry = new Battery;
      new_entry->setPos(position);
      new_entry->setJoltage(*it - '0');
      batteries.push_back(new_entry);
      position++;
    }
    //batteries.sort_by_joltage();
    totalJoltage += makeBattery(batteries, 12); 
    batteries.empty();
  }
  printf("%lld",totalJoltage);

  return 0;
}
