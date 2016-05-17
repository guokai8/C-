--------------------
How to use it?
* first: complie the function
 clang++ -O3 get_gene_len.cpp -o get_gene_len
* second: prepare the site file like this
  Chr1,100
* third:
./get_gene_len test.fasta tt len >res.fasta
test.fasta gemome sequence
tt: chr site
len: the half of the length needed，example: if you need 1000bp,the len is 500



