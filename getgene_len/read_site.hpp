#ifndef READ_SITE_HPP
#define READ_SITE_HPP
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
std::map<std::string,int> read_site(char *filename)
{
  std::ifstream input(filename);
  if(!input.good()){
      std::cerr<<"Error opening '"<<filename<<"'. Bailing out."<<std::endl;
    }
  std::map<std::string,int> res;
  std::string line;
  std::vector<std::string>lres;
  while(std::getline(input,line).good()){
    istringstream ss(line);
    string field;
    char spliter=',';
    while(!ss.eof()){
      getline(ss,field,spliter);
      lres.push_back(field);
    }
  }
  for(int i=0;i<lres.size();i+=2)
  {
    string tmp=lres[i];
    int site=atoi(lres[i+1].c_str());
    res.insert(pair<string,int>(tmp,site));
  }
  return res;
}
#endif
