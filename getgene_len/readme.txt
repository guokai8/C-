#######################################################
How to use it?
first: complie the function
clang++ -O3 get_gene_len.cpp -o get_gene_len
second: prepare the site file like this
Chr1,100
染色体名字要对应基因组序列文件的染色体名字例如test.fasta染色体名字为Chr1
第二列是位置，两者以逗号间隔。
third:
./get_gene_len test.fasta tt len >res.fasta
test.fasta 基因组文件
tt 染色体以及位置存放文件
len 需要选取长度的一半，例如选取1000bp 则len应该为500



