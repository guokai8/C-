#######################################################
How to use it?
first: complie the function
clang++ -O3 fastacut.cpp -o fastacut
second: prepare the site file like this
Chr1,100,300
染色体名字要对应基因组序列文件的染色体名字例如test.fasta染色体名字为Chr1
第二列是起始位置，第三列是结束位置，两者以逗号间隔。
third:
./fastacut test.fasta tt  >res.fasta
test.fasta 基因组文件
tt 染色体以及位置存放文件



