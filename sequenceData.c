/*Description: This script is writed for reading fasta and combining seq together 
* Modified by Kai Guo ###
* Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * File created on Sun Jun  6 10:34:31 2004.
 *   You should have received a copy of the GNU General Public License
 *   along with shustring; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *****************************************************************/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"
#include "sequenceData.h"
//#include "interface.c"
#include "eprintf.c"
typedef long Int64;
/////* reverse and complement a sequence */
char *strdup2(char *s){
     char *p; 
          
     p = (char *) emalloc(strlen(s)+1);    /* +1 for '\0' */
     if (p != NULL)
       p = strcpy(p,s);
     return p;
   }   
Sequence *revcomp(Sequence *seq){
  Int64 i,j,n;
  char c;
  Sequence *newSeq;
  newSeq = (Sequence *)emalloc(sizeof(Sequence));

  n = strlen(seq->seq);
  newSeq->seq = (char *) emalloc((n+1)*sizeof(char));

  newSeq->id = strdup2(seq->id);
  j=0;
  for(i = n-1; i >= 0; i--){
    c = seq->seq[i];
    switch(c){
      case '#':
	newSeq->seq[j++] = '#';
	break;
      case 'a':
	newSeq->seq[j++] ='t';
	break;
      case 'c':
	newSeq->seq[j++] ='g';
	break;
      case 'g':
	newSeq->seq[j++] ='c';
	break;
      case 't':
	newSeq->seq[j++] ='a';
	break;
      case 'A':
	newSeq->seq[j++] ='T';
	break;
      case 'C':
	newSeq->seq[j++] ='G';
	break;
      case 'G':
	newSeq->seq[j++] ='C';
	break;
      case 'T':
	newSeq->seq[j++] ='A';
	break;
      default:
	newSeq->seq[j++] =c;
	break;
    }
  }
  newSeq->seq[n]='\0';
  return newSeq; 
}
/* read FASTA-formatted sequence data from an open file descriptor */
Sequence *readFasta(int fd){
  Sequence *s;
  char *buf;
  Int64 headerOpen, c, maxLen;
  Int64 headerLen, i;
  buf = (char *)emalloc(BUFSIZ*sizeof(char));
  s = (Sequence *)emalloc(sizeof(Sequence));
  s->id = "SeqId\n";
  s->seq = NULL;
  s->borders = NULL;
  s->headers = NULL;
  headerOpen = 0;
  s->len = 0;
  s->numSeq = 0;
  maxLen = 0;
  headerLen = 0;
  while((c = read(fd,buf,BUFSIZ)) > 0){
    if(s->len + c > maxLen){
      if(maxLen >= BUFSIZ)
	maxLen *= 2;
      else
	maxLen = BUFSIZ + 1;
      s->seq = (char *)erealloc(s->seq,maxLen*sizeof(char));
    }
    for(i=0; i<c; i++){
      if(buf[i] == '>'){
	headerOpen = 1;
	/* take care of sequence borders */
	s->borders = (Int64 *)erealloc(s->borders,(s->numSeq+1)*sizeof(Int64));
	if(s->numSeq >= 1){
	  s->seq[s->len] = '#';//\1  /* unique character to terminate each sequence */
	  s->len++;
	  s->borders[s->numSeq-1] = s->len-1;
	}
	/* take care of sequence headers */
	s->headers = (char **)erealloc(s->headers,(s->numSeq+1)*sizeof(char *));
	s->headers[s->numSeq] = (char *)emalloc(BUFSIZ*sizeof(char));
	headerLen = 0;
	s->numSeq++;
      }
      if(headerOpen){
	if(buf[i] == '\n'){
	  headerOpen = 0;
	  s->headers[s->numSeq-1][headerLen] = '\0';
	  s->headers[s->numSeq-1] = (char *)erealloc(s->headers[s->numSeq-1],(headerLen+1)*sizeof(char));
	}
	else if(headerLen < BUFSIZ && isprint(buf[i]))
	  s->headers[s->numSeq-1][headerLen++] = buf[i];
      }else if(buf[i] != '\n'){
	s->seq[s->len] = buf[i];
	s->len++;
      }
    }
  }
  /* add last border */
  s->seq[s->len] = '$';
  //s->seq[s->len] = '\1';
  s->len++;
  /* set end of last sequence read */
  s->borders[s->numSeq - 1] = s->len - 1;
  /* trim sequence to actual size */
  s->seq = (char *)erealloc(s->seq,s->len*sizeof(char));
  return s;
}
/* freeSequence: free the data structure Sequence */
Sequence *freeSequence(Sequence *seq){
  free(seq->id);
  free(seq->seq);
  free(seq);
  return seq;
}
//int main(int argc,char *argv[]){
//  char text[1000000];
//  Sequence *sequence =NULL;
////  Args *args;
////  args = getArgs(argc, argv);
//  int fd=open(argv[1],0);
//  printf("%s\n",argv[1]);
//  fflush(NULL);
//  sequence=readFasta(fd);
//  close(fd);
//  fflush(NULL);
//  strtoupper(sequence->seq);
//  //printf("%s\n",sequence->seq);
//  strcpy(text,sequence->seq);
// // printf("%s\n",text);
//  printf("%ld\n",sequence->borders[0]);
//  return 0;
//}
