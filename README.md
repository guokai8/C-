//################################################################################
//# Author:Kai Guo guokai8@gmail.com ##############################################
//# 
//# Last modified: 2016-05-09 19:37######################################
//# 
//# Filename: README.txt
//# 
//# Description: This script is part of big project####
//#################################################################################
## This program was written for slove the problem below:
## Devise a fast and practical computation to generate all the shortest unique subsequences of the rice genome
#################################################
## I make a short description below:
## First: I read all the chromosome and combine all the sequence with character “#” and end with “$”.
## I also record each length of the chromosome. Then I construct the   "Ukkonen's Suffix Tree” . 
## Second: To use suffix trees for detecting unique substrings, notice that the path label of any leaf is a unique substring. 
## The set of shortest unique substrings at every position can therefore be discovered by traversing the tree once and looking 
## up the string depth of the parent node of every leaf. This value plus one is the desired length of the shortest unique string
## that starts at the position indicated by the leaf.If the substring contain character “#” I remove this substring.
## Then I store all these substring in a associative array, key is the position and value is the length of substring.
## Third: I exact all the substrings of each chromosome and find the shortest length of substring, then I print out
## all these substring with the shortest length with chromosome name, start position and end position.
## Finally: I could got the shortest substrings of each chromosome.It needed O(N) time to construct the tree also need O(N) to find the substring.
###################################################
### The prohram was tested under all UNIX-like platform also include Mac OS
### Just complied it by g++ or clang++ (ingored the warnings)
g++ substring.cpp -o substring
### TEST IT 
./substring in.fasta >out.txt
###################################################
