//################################################################################
//# Author:Kai Guo guokai8@gmail.com ##############################################
//# 
//# Last modified: 2015-01-10 21:30######################################
//# 
//# Filename: read_fasta.cpp
//# 
//# Description: This script is writed for read fasta file####
//#################################################################################
#ifndef READ_FASTA_HPP
#define READ_FASTA_HPP
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
using namespace std;
std::map<std::string,std::string> read_fasta(char *filename)
{
    std::ifstream input(filename);
    if(!input.good()){
      std::cerr<<"Error opening '"<<filename<<"'. Bailing out."<<std::endl;
    }
    std::map<std::string,std::string> lres;
    std::string line,name,content;
    while(std::getline(input,line).good()){
      if(line.empty()||line[0]=='>'){
        if(!name.empty()){
          lres[name]=content;
          name.clear();
        }
        if(!line.empty()){
          istringstream ss(line);
          string field;
          char spliter=' ';
          getline(ss,field,spliter);
          name=field.substr(1,field.length());
        }
        content.clear();
      }else if(!name.empty()){
        if(line.find(' ')!=std::string::npos){
          name.clear();
          content.clear();
        }else{
          content +=line;
        }
      }
    }
    lres[name]=content;
    return lres;
//    if(!name.empty()){
//      std::cout<<name<<" : "<<content<<std::endl;
//      std::cout<<"sequence length: "<<content.length()<<std::endl;
//    }
}
std::vector<std::string> read_fasta_vec(char *file){
  std::ifstream input(file);
  std::string line,name,content;
  std::vector<std::string> allname;
  std::vector<std::string> allcontent;
  while(std::getline(input,line).good()){
    if(line.empty()||line[0]=='>'){
      if(!name.empty()){
        allcontent.push_back(content);
        name.clear();
      }
      if(!line.empty()){
        name=line.substr(1);
        allname.push_back(name);
      }
      content.clear();
    }else if(!name.empty()){
      if(line.find(' ')!=std::string::npos){
        name.clear();
        content.clear();
      }else{
        content +=line;
      }
    }
  }
  allcontent.push_back(content);
  return allcontent;
}
#endif
