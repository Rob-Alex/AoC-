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


bool order_joltage(Battery* first, Battery* second){
  return (first->getJoltage() > second->getJoltage());
}

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
  /* bubble sort joltage 
  void sort_by_joltage(){
    if(_pHead == _pTail){
      return; 
    }
    bool swaps = true;
    while (swaps) {
      swaps = false;
      for (BatteryNode* iter = _pHead; iter != nullptr; iter = iter->_pNext){
        if (iter->_pNext == nullptr){
          break;
        }
        BatteryNode* first = iter;
        BatteryNode* second = iter->_pNext;
        if (order_joltage(first->_pBattery, second->_pBattery)) {
          Battery* tmpBattery = second->_pBattery;
          second->_pBattery = first->_pBattery;
          first->_pBattery = tmpBattery;
          swaps = true;
        }
      }
    }
  }
  */

  int makeBattery(){
    BatteryList bigBattery[12]; 
    bigBattery->_pHead = _pHead; 
    bigBattery->_pTail = nullptr;
    int position = 12;
    for (BatteryNode* iter1 = bigBattery->_pHead; iter1 != nullptr; iter1 = iter1->_pNext){ 
      BatteryNode* MinimumPosition = _pTail-position; 
      for (BatteryNode* iter2 = bigBattery->_pHead->_pNext; iter2 != (_pTail - position); iter2 = iter2->_pNext){
        if (iter1 != nullptr){
        std::cout << iter2->_pBattery->getJoltage() << std::endl;
        }
      }
    }
    return 0;
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

int main() {

  std::string filename = "./inputs/day03-test.txt";
  std::ifstream ifs(filename);
  if(!ifs) { return -1; }

  std::string line;

  int totalJoltage = 0;
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
    totalJoltage += batteries.makeBattery(); 
    batteries.empty();
  }
  printf("%d",totalJoltage);

  return 0;
}
