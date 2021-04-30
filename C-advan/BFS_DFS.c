#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"graphlib.h"
#include "fields.h"
#include "jval.h"
#define MAXSTATION 10
void readFile(JRB st,graph graph)
{
  int n,i;
  IS is;
  char *name;
  int s1,s2,sign;
  is=new_inputstruct("station.txt");
  while(get_line(is)>=0){
    if(is->NF>1){
      name=strdup(is->fields[0]);
      sign=atoi(is->fields[1]);
      jrb_insert_int(st,sign,new_jval_s(name));
    }
  }
  is=new_inputstruct("stmap.txt");
  while(get_line(is)>=0){
    if(is->NF>1){
      for(i=0;i<is->NF-1;i++)
	{
	  s1=atoi(is->fields[i]);
	  s2=atoi(is->fields[i+1]);
	  addedge(graph,s1,s2);
	}
    }
  }
}
void DFS(graph graph,int u,int mark[MAXSTATION][2],int* d)
{
  int v;
  JRB tree,node=jrb_find_int(graph,u);
  if(node!=NULL){
    mark[u-1][0]=1;
    mark[*d][1]=u;
    (*d)++;
    tree=(JRB)(node->val).v;
    jrb_traverse(node,tree){
      v=(node->key).i;
      if(mark[v-1][0]==0)
	DFS(graph,v,mark,d);
    }
    
  }
}
void BFS(graph graph,int u,int mark[MAXSTATION][2],int* d,int *b)
{
  int v,w;
  JRB tree,node=jrb_find_int(graph,u);
  if(node!=NULL)
    {
      if(mark[u-1][0]==0)
	{
	  mark[u-1][0]=1;
	  mark[*d][1]=u;
	  (*d)++;
	
	  tree=(JRB)(node->val).v;
	  jrb_traverse(node,tree){
	    v=(node->key).i;
	    if(mark[v-1][0]==0)
	      {
		mark[v-1][0]=1;
		mark[*d][1]=v;
		(*d)++;
	      }
	  }
	  w=mark[*b][1];
	  BFS(graph,w,mark,d,b);
	}
      else{
	tree=(JRB)(node->val).v;
	jrb_traverse(node,tree){
	  v=(node->key).i;
	  if(mark[v-1][0]==0)
	      {
		mark[v-1][0]=1;
		mark[*d][1]=v;
		(*d)++;
	      }
	  }
	(*b)++;
	w=mark[*b][1];
	BFS(graph,w,mark,d,b);
      }
    }
}
int main()
{
  int dfs[MAXSTATION][2],bfs[MAXSTATION][2];
  int n,i,j,x;
  int out[100];
  graph g=creategraph(100);
  JRB st=make_jrb();
  int d=0,b1=0,b2=1;
  readFile(st,g);
  printf("DFS ");
  for(i=0;i<MAXSTATION;i++)
    for(j=0;j<2;j++)
      {
	dfs[i][j]=0;
	bfs[i][j]=0;
      }
  DFS(g,1,dfs,&d);
  BFS(g,1,bfs,&b1,&b2);
  for(j=1,i=0;i<MAXSTATION;i++)
    printf("%d ",dfs[i][j]);
  printf("\nBFS ");
  for(j=1,i=0;i<MAXSTATION;i++)
    printf("%d ",bfs[i][j]);
  printf("\n");
  return 0;
}
