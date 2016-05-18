Get chromosome sequence by position (like fastacmd in blast)
----------------
How to use it?
* first: complie the function
clang++ -O3 fastacut.cpp -o fastacut
* second: prepare the site file like this
  Chr1,100,300
* third:
  ./fastacut test.fasta tt  >res.fasta
  test.fasta: genome fasta file
  tt: site position



