#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iterator>
#include "read_fasta.hpp"
#include "write_fasta.hpp"
#include "read_site.hpp"
using namespace std;
int main(int argc,char **argv){
  if(argc<=3){
    std::cerr<<"Usage: "<<argv[0]<<" [fasta] [site_file] [length]"<<std::endl;
    return -1;
  }
  std::map<std::string,std::string> seq_dat=read_fasta(argv[1]);
  std::map<std::string,int> site_dat=read_site(argv[2]);
  //std::map<std::string,std::string> res;
  std::map<std::string,int>::iterator iter;
  int len=atoi(argv[3]);
  for(iter=site_dat.begin();iter!=site_dat.end();++iter)
  {
    string tmp=iter->first;
    int site=iter->second;
    string res=seq_dat[tmp];
    string tt=tmp+":"+to_string((site-len)>0?(site-len):0)+"--"+to_string(site+len);
    print_fasta(tt,res.substr((site-len)>0?(site-len):0,len*2));
  }
  return 0;
}
