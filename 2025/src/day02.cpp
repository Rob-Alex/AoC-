#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class Data{
public:
  unsigned long long _ullStartIndex; 
  unsigned long long _ullEndIndex; 
  Data(unsigned long long start, unsigned long long end) : _ullStartIndex(start), _ullEndIndex(end) {};
  unsigned long long getStart() { return this->_ullStartIndex; }
  unsigned long long getEnd(){ return this->_ullEndIndex; }
};

std::vector<Data> parseData(std::string line) { 
  std::stringstream ss(line);
  std::string range;
  std::string startindex; 
  std::string endindex;
  std::vector<Data> data; 
  while(getline(ss, range, ',')) {
    startindex = range.substr(0, range.find('-')); 
    endindex = range.substr(range.find('-'), range.length());
    Data new_entry = Data(std::stol(startindex), std::stol(endindex));  
    data.push_back(new_entry);  
  }
  return data; 
}

int main() {
  std::string filename = "./inputs/day02.txt";
  std::ifstream ifs(filename);
  if(!ifs) { return -1; }

  std::string line;
  getline(ifs, line);
  std::vector<Data> all = parseData(line); 
  for(Data single : all){
     
  }
  return 0;
}
