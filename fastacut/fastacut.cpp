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
  if(argc<=2){
    std::cerr<<"Usage: "<<argv[0]<<" [fasta] [site_file]"<<std::endl;
    return -1;
  }
  std::map<std::string,std::string> seq_dat=read_fasta(argv[1]);
  std::map<std::string,std::vector<std::string> > site_dat=read_site(argv[2]);
  //std::map<std::string,std::string> res;
  std::map<std::string,std::vector<std::string> >::iterator iter;
//  int len=atoi(argv[3]);
  for(iter=site_dat.begin();iter!=site_dat.end();++iter)
  {
    std::string tmp=iter->first;
    std::vector<std::string> site=iter->second;
    string res=seq_dat[site[0]];
    string tt=tmp+":"+site[0]+":"+site[1]+"--"+site[2];
//    std::cout<<res.substr(site[0],10)<<endl;
    int st=atoi(site[1].c_str());
    int sp=atoi(site[2].c_str());
    print_fasta(tt,res.substr(st-1,sp-st+1));
  }
  return 0;
}
