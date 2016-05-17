#ifndef WRITE_SEQ_HPP
#define WRITE_SEQ_HPP
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;
const int LINELENGTH=80;
void print_fasta(std::string const& header, std::string const& seg, ostream& out = std::cout)
{
    out << ">"<<header << "\n";
    std::string comp(seg.begin(),seg.end());
    size_t i = 0;
    size_t stop = comp.length()/LINELENGTH + ((comp.length()%LINELENGTH)?1:0);
    while(i < stop)
        out << comp.substr(i++*LINELENGTH,LINELENGTH) << "\n";
}
#endif
