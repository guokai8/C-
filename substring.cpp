#include <map>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sequenceData.c"
#include <limits.h>
#define MAX_CHAR 256
struct SuffixTreeNode {
    struct SuffixTreeNode *children[MAX_CHAR];
    struct SuffixTreeNode *suffixLink;
    int start;
    int *end;
    int suffixIndex;
};
typedef long Int64;
typedef struct SuffixTreeNode Node;
char text[500000000]; //Input string
Node *root = NULL; //Pointer to root node
Node *lastNewNode = NULL;
Node *activeNode = NULL;
int activeEdge = -1;
int activeLength = 0;
int remainingSuffixCount = 0;
int leafEnd = -1;
int *rootEnd = NULL;
int *splitEnd = NULL;
std::map<int,int> sl;
int size = -1; //Length of input string
Node *newNode(int start, int *end)
{
    Node *node =(Node*) malloc(sizeof(Node));
    int i;
    for (i = 0; i < MAX_CHAR; i++)
          node->children[i] = NULL;
    node->suffixLink = root;
    node->start = start;
    node->end = end;
    node->suffixIndex = -1;
    return node;
}
int edgeLength(Node *n) {
  if(n == root)
    return 0;
    return *(n->end) - (n->start) + 1;
}
int walkDown(Node *currNode)
{
    if (activeLength >= edgeLength(currNode))
    {
        activeEdge += edgeLength(currNode);
        activeLength -= edgeLength(currNode);
        activeNode = currNode;
        return 1;
    }
    return 0;
}
void extendSuffixTree(int pos)
{
    leafEnd = pos;
    remainingSuffixCount++;
    lastNewNode = NULL;
    while(remainingSuffixCount > 0) {
        if (activeLength == 0)
            activeEdge = pos; //APCFALZ
        if (activeNode->children[text[activeEdge]] == NULL)
        {
            activeNode->children[text[activeEdge]] =
                                          newNode(pos, &leafEnd);
            if (lastNewNode != NULL)
            {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = NULL;
            }
        }
        else
        {
            Node *next = activeNode->children[text[activeEdge]];
            if (walkDown(next))//Do walkdown
            {
                continue;
            }
            if (text[next->start + activeLength] == text[pos])
            {
        if(lastNewNode != NULL && activeNode != root)
        {
          lastNewNode->suffixLink = activeNode;
          lastNewNode = NULL;
        }
                activeLength++;
                break;
            }
            splitEnd = (int*) malloc(sizeof(int));
            *splitEnd = next->start + activeLength - 1;
            Node *split = newNode(next->start, splitEnd);
            activeNode->children[text[activeEdge]] = split;
            split->children[text[pos]] = newNode(pos, &leafEnd);
            next->start += activeLength;
            split->children[text[next->start]] = next;
            if (lastNewNode != NULL)
            {
                lastNewNode->suffixLink = split;
            }
            lastNewNode = split;
        }
        remainingSuffixCount--;
        if (activeNode == root && activeLength > 0) //APCFER2C1
        {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        }
        else if (activeNode != root) //APCFER2C2
        {
            activeNode = activeNode->suffixLink;
        }
    }
}
void setSuffixIndexByDFS(Node *n, int labelHeight)
{
    if (n == NULL)  return;
    int leaf = 1;
    int i;
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (n->children[i] != NULL)
        {
            leaf = 0;
            setSuffixIndexByDFS(n->children[i], labelHeight +
                                  edgeLength(n->children[i]));
        }
    }
    if (leaf == 1)
    {
        n->suffixIndex = size - labelHeight;
    }
}
void freeSuffixTreeByPostOrder(Node *n)
{
    if (n == NULL)
        return;
    int i;
    for (i = 0; i < MAX_CHAR; i++)
    {
        if (n->children[i] != NULL)
        {
            freeSuffixTreeByPostOrder(n->children[i]);
        }
    }
    if (n->suffixIndex == -1)
        free(n->end);
    free(n);
}
void buildSuffixTree()
{
    size = strlen(text);
    int i;
    rootEnd = (int*) malloc(sizeof(int));
    *rootEnd = - 1;
    root = newNode(-1, rootEnd);
    activeNode = root; //First activeNode will be root
    for (i=0; i<size; i++)
        extendSuffixTree(i);
    int labelHeight = 0;
    setSuffixIndexByDFS(root, labelHeight);
}
void strtolower(char *s){
  int i,l;
  l = strlen(s);
  for(i=0;i<l;i++)
    s[i] = tolower(s[i]);
}
void strtoupper(char *s){
  int i,l;
  l = strlen(s);
  for(i=0;i<l;i++)
    s[i] = toupper(s[i]);
}
void tranverse(Node *n,int labelHeight){
  if(n==NULL)
  {
    return;
  }
  int leaf=1;
  int i;
  for(int i=0;i<MAX_CHAR;i++){
    if(n->children[i]!=NULL){
      leaf=0;
      tranverse(n->children[i],labelHeight+edgeLength(n->children[i]));
    }
  }
  if(leaf==1){
    n->suffixIndex=size-labelHeight;
    int dep=labelHeight-(*(n->end)-n->start+1);
    int ss=n->suffixIndex;
    int len=dep+1;
    char *s=new char[len];
    strncpy(s,text+ss,len);
    s[len+1]='\0';
    if(ss+dep!=size-1&&strchr(s,'#')==NULL){
        sl[ss]=len;
    }
  }
}
void findSubstring(Sequence *sequ)
{
  Int64 lb,smin,i,k,j,l,seqcount,numShu;
  lb=0;
  for(i=0;i<sequ->numSeq;i++){
    seqcount=0;
    smin=INT_MAX;
    if(i)
      lb = sequ->borders[i-1] + 1;
    for(j=lb;j<sequ->borders[i];j++){
      if(sl[j]<smin&&sl[j]>0){
        smin=sl[j];
        seqcount=1;
      }else if(sl[j]==smin){
        seqcount++;
      }
    }
    if(smin>0&&smin<INT_MAX){
      printf("%s\t%ld\t%ld\t%ld\n",sequ->headers[i],sequ->borders[i]-lb,seqcount,smin);
      printf("#num\tpos\tlen\tseq\n");
      numShu=1;
      if(i)
        lb = sequ->borders[i-1] + 1;
      else
        lb=0;
      for(j=lb;j<sequ->borders[i];j++){
        if(sl[j] == smin){
          printf("%ld\t%ld\t%ld\t",numShu++,j+1-lb,smin);
          l = j + sl[j];
          for(k=j;k<l;k++) 
            printf("%c",sequ->seq[k]);
          printf("\n");
        }
      }
    }
  }
}
int main(int argc, char *argv[])
{
  Sequence *sequ=NULL;
  int fd=open(argv[1],0);
  fflush(NULL);
  sequ=readFasta(fd);
  close(fd);
  fflush(NULL); 
  strtoupper(sequ->seq);
  strcpy(text, sequ->seq); 
  buildSuffixTree();  
  tranverse(root,0);
  findSubstring(sequ);
  fflush(NULL);
  freeSuffixTreeByPostOrder(root);
  return 0;
}
