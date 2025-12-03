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
  unsigned long long getStart() { return _ullStartIndex; }
  unsigned long long getEnd(){ return _ullEndIndex; }
};

std::vector<Data> parseData(std::string line) { 
  std::stringstream ss(line);
  std::string range;
  std::string startindex; 
  std::string endindex;
  std::vector<Data> data; 
  while(getline(ss, range, ',')) {
    startindex = range.substr(0, range.find('-')); 
    endindex = range.substr(range.find('-')+1, range.length());
    Data new_entry = Data(std::stol(startindex), std::stol(endindex));  
    data.push_back(new_entry);  
  }
  return data; 
}

unsigned long long hasRepeats(std::string id){
  int length = id.length();
  std::vector<std::string> strings;
  //get repeats 
  for(int i = 2; i <= length; i++){
  //for(int i = 2; i < 3; i++){ this was for part 1
    if ((length % i)==0){
      bool repeater = 1;
      strings.clear();
      for(int pos = 0; pos < length; pos+=(length/i)){
        strings.push_back(id.substr(pos, length/i)); 
        if (strings.size() > 1) {
          for (int j = 1; j < strings.size(); j++){
            if (strings[j] != strings[j-1]) {
              repeater = 0;
            }
          }
        }
      }
      if (repeater){
        return std::stol(strings[0]);
      }
    }
  } 
  return 0;
}

int main() {
  std::string filename = "./inputs/day02.txt";
  std::ifstream ifs(filename);
  if(!ifs) { return -1; }
  unsigned long long total = 0;
  std::string line;
  getline(ifs, line);
  std::vector<Data> all = parseData(line); 
  for(Data single : all){
    for(unsigned long long i = single.getStart(); i <=single.getEnd(); i++){
      std::string sequence = std::to_string(i);
      if(hasRepeats(sequence) > 0){
        total += i;
      }
    }
  }
  printf("%lld",total);
  return 0;
}
