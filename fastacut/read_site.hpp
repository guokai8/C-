#ifndef READ_SITE_HPP
#define READ_SITE_HPP
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
std::map<std::string,std::vector<std::string> > read_site(char *filename)
{
  std::ifstream input(filename);
  if(!input.good()){
      std::cerr<<"Error opening '"<<filename<<"'. Bailing out."<<std::endl;
    }
  std::map<std::string,std::vector<std::string> > res;
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
  for(int i=0;i<lres.size();i+=4)
  {
    string gene=lres[i];
    std::vector<std::string> xx;
    string chr=lres[i+1];
    xx.push_back(chr);
    std::string site1=lres[i+2];
    xx.push_back(site1);
    std::string site2=lres[i+3];
    xx.push_back(site2);
    res.insert(pair<std::string,std::vector<std::string> >(gene,xx));
  }
  return res;
}
#endif
