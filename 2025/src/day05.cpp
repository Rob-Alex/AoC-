#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>


class Database {
public:
  int long long* _iStartRange;
  int long long* _iEndRange;
  int long long* _iIDs;
  int _iNumInputs;
  int _iNumRanges;
  Database(int long long* startRange, int long long* endRange, int long long* IDs, int long long numInputs, int long long numRanges) : _iStartRange(startRange), _iEndRange(endRange), _iIDs(IDs), _iNumInputs(numInputs), _iNumRanges(numRanges) {};
  std::string toStringInputs(){
    std::stringstream ss;
      for(int i = 0; i < _iNumInputs; i++){
        ss << _iIDs[i] << "\n";
      }
    return ss.str();
  }
  std::string toStringRanges(){
    std::stringstream ss;
      for(int i = 0; i < _iNumRanges; i++){
        ss << _iStartRange[i] << " to " << _iEndRange[i] << "\n";
      }
    return ss.str();
  }
  int checkFresh(){
    int fresh = 0; 
    for(int k = 0; k < _iNumInputs; k++){
      std::cout << "checking: " << _iIDs[k] << " with the following ranges: ";
      for(int i = 0; i < _iNumRanges; i++){
        std::cout << _iStartRange[i] << " to " << _iEndRange[i] << "\n";
        if (_iIDs[k] >= _iStartRange[i] && _iIDs[k] <= _iEndRange[i]){ 
          fresh++;
          k++;
        } 
      }
      std::cout << "next \n";
    }
    return fresh;
  }
};


Database parseInput(std::string filename){
  std::ifstream ifs(filename);
  std::string line;
  bool isInputs = 0;
  int countRanges = 0;
  int countInputs = 0;
  int long long* startRange{}; 
  int long long* endRange{};
  int long long* IDs{};
  while(getline(ifs, line)){
    if (line == ""){
      isInputs = 1; 
    }
    if (!isInputs){
      countRanges++;
      int long long* newStartRange = new int long long[countRanges]; 
      std::copy(startRange, startRange + std::min(countRanges-1, countRanges), newStartRange);
      delete[] startRange;
      startRange = newStartRange;
      
      int long long* newEndRange = new int long long[countRanges];
      std::copy(endRange, endRange + std::min(countRanges-1, countRanges), newEndRange);
      delete[] endRange;
      endRange = newEndRange;

      startRange[countRanges-1] = std::stol(line.substr(0, line.find('-'))); 
      endRange[countRanges-1] = std::stol(line.substr(line.find('-')+1, line.length()));
    }  
    if (isInputs && line != "") { 
      countInputs++;
      int long long* newIDs = new int long long[countInputs];
      std::copy(IDs, IDs + std::min(countInputs-1, countInputs), newIDs);
      delete[] IDs;
      IDs = newIDs;
        
      IDs[countInputs-1] = std::stol(line);
    }
    //std::cout << line << std::endl;
  }
  Database data(startRange, endRange, IDs, countInputs, countRanges);
  return data;
} 
int main() {
  Database data = parseInput("./inputs/day05.txt");
  //std::cout << data.toStringRanges();
  //std::cout << data.toStringInputs();
  std::cout << "fresh: " << data.checkFresh();
  // Part 1:
  

  // Part 2:


  return 0;
}
