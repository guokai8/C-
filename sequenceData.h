/***** sequenceData.h *********************************************
 * Description: Header file for sequence manipulation tasks.
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * File created on Sun Jun  6 10:34:25 2004.
 * Modified by Kai Guo: guokai8@gmail.com
 *****************************************************************/
#define SEQLINE 1000       /* maximal length of one line in FASTA file; hard bound */
#define SEQBUFFER 5000000  /* define the size of the sequence buffer */
#define DICSIZE 256

/* basic sequence type representing >= 1 entry in FASTA file */
typedef struct sequence{
  char *seq;              /* the sequence */
  char *id;               /* the sequence id */
  int numSeq;             /* number of sequences represented */
  Int64 *borders;         /* position of last character of sequence in seq */
  char **headers;         /* FASTA header lines */
  Int64 len;              /* sequence length */
  Int64 *pos;             /* sequence positions corresponding to suffix array positions */
} Sequence;

Sequence *revcomp(Sequence *seq);
Sequence *getNextSequence(FILE *fp);
int *getDnaDictionary(int *dic);
int *getRestrictedDnaDictionary(int *dic);
Sequence *freeSequence(Sequence *seq);
Sequence *getPermanentNextSequence(FILE *fp);
void convertToAcgt(Sequence *seq);
void resetSequenceReader();
Sequence *readFasta(int fd);
