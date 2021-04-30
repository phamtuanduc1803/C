#include<stdio.h>
#include<stdlib.h>
#include"jval.h"
#include"jrb.h"
#define INFINITIVE_VALUE 1000000
#define maxSize 10
typedef struct 
{
  JRB edges;
  JRB vertices;
}Graph;
typedef struct
{
  int edge;
  double cost;
}path;
typedef struct NODE
{
  int a;
  struct NODE *next;
}node;
typedef struct QUEUE
{
  node *rear;
  node *front;
}queue;
queue *Init()
{
  queue *new;
  new=(queue*)malloc(sizeof(queue));
  new->rear==NULL;
  new->front==NULL;
  return new;
}
node *NewNode(int x)
{
  node *new=(node*)malloc(sizeof(node));
  new->a=x;
  new->next=NULL;
  return new;
}
queue *enqueue(queue *q,int x)
{
  node *new=NewNode(x);
  if(q->front==NULL)
    {
      q->front=new;
      q->rear=q->front;
    }
  else
    {
      q->rear->next=new;
      q->rear=q->rear->next;
    }
  return q;
}
int dequeue(queue *q)
{
  int x;
  if(q->front==NULL)
    {
      return -1;
    }
  else
    {
      node *p=q->front;
      x=p->a;
      q->front=q->front->next;
      free(p);
      return x;
    }
}
int sizeofQueue(queue *q)
{
  int count=0;
  node *p=q->front;
  while(p!=NULL)
    {
      p=p->next;
      count++;
    }
  return count;
}

Graph creat_graph()
{
  Graph g;
  g.edges=make_jrb();
  g.vertices=make_jrb();
  return g;
}
int hasEdge(Graph graph,int v1,int v2)
{
  JRB node,tree;
  node=jrb_find_int(graph.edges,v1);
  if(node==NULL)
    return 0;
  tree=(JRB)(node->val.v);
  node=jrb_find_int(tree,v2);
  if(node==NULL)
    return 0;
  else return 1;
}
void addVertice(Graph graph,int v)
{
  JRB node=jrb_find_int(graph.vertices,v);
  if(node==NULL)
    jrb_insert_int(graph.vertices,v,new_jval_d(0));
}
void addEdge(Graph graph, int v1, int v2,double s)
{
    JRB node, tree;
    if (hasEdge(graph,v1,v2) == 0)
    {
        node = jrb_find_int(graph.edges, v1);
        if (node == NULL)
        {
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree));
            jrb_insert_int(tree, v2, new_jval_d(s));
        }
        else
        {
            tree = (JRB)jval_v(node->val);
            jrb_insert_int(tree, v2, new_jval_d(s));
        }
    }
}
double getEdgeValue(Graph graph,int v1,int v2)
{
  JRB node,tree;
  node=jrb_find_int(graph.edges,v1);
  if(node==NULL)
    return 0;
  else{
    tree=(JRB)(node->val.v);
    node=jrb_find_int(tree,v2);
    if(node==NULL)
      return INFINITIVE_VALUE;
    else return (double)(node->val.d);
  }
}
JRB make_visit(Graph graph)
{
  JRB visit=graph.vertices;
  return visit;
}
double visitCheck(JRB visit, int v)
{
  JRB node;
  node=jrb_find_int(visit,v);
  if(node==NULL)
    return -1;
  else return (double)(node->val).d;
}
void visited(JRB visit,int v)
{
  JRB node=jrb_find_int(visit,v);
  (node->val).d=1;
}
JRB make_cost(Graph graph,int v)
{
  JRB node,cost=make_jrb();
  path *p;
  int u;
  jrb_traverse(node,graph.vertices)
    {
      u=(int)(node->key).i;
      if(u!=v){
	p=malloc(sizeof(path*));
	p->edge=-1;
	p->cost=INFINITIVE_VALUE;
	jrb_insert_int(cost,u,new_jval_v(p));
      }
      else
	{
	  p=malloc(sizeof(path*));
	  p->edge=v;
	  p->cost=0;
	  jrb_insert_int(cost,u,new_jval_v(p));
	}
    }
  return cost;
}
void cap_nhat(JRB cost, int v1,int v2, double s)
{
  JRB node;
  path *s1,*s2;
  node=jrb_find_int(cost,v1);
  s1=(path*)(node->val).v;
  node=jrb_find_int(cost,v2);
  s2=(path*)(node->val).v;
  if(s+s1->cost<s2->cost)
    {
      s2->cost=s+s1->cost;
      s2->edge=v1;
      (node->val).v=s2;
    }
}
void dijkstra(Graph graph,JRB visit,JRB cost,queue *q,int v)
{
  JRB node,tree;
  int u;
  double s;
  node=jrb_find_int(graph.edges,v);
  if(node!=NULL)
    {
      tree=(JRB)(node->val).v;
      jrb_traverse(node,tree)
	{
	  u=(int)(node->key).i;
	  s=(double)(node->val).d;
	  if(visitCheck(visit,u)==0)
	    {
	      q=enqueue(q,u);
	      visited(visit,u);
	    }
	  cap_nhat(cost,v,u,s);
	}
      if(visitCheck(visit,v)==0)
	visited(visit,v);
      u=dequeue(q);
      dijkstra(graph,visit,cost,q,u);
    }
}
void shortestPath(Graph graph,int v1,int v2,int Path[],int *i)
{
  
  JRB node,cost=make_cost(graph,v1),visit=make_visit(graph);
  queue *q=Init();
  dijkstra(graph,visit,cost,q,v1);
  path *s;
  int u=v2;
  while(1)
    {
      node=jrb_find_int(cost,u);
      s=(path*)(node->val).v;
      u=s->edge;
      Path[*i]=u;
      (*i)++;
      if(u==v1)
	break;
    }
}
int main()
{
  Graph g=creat_graph();
  addVertice(g,1);
  addVertice(g,2);
  addVertice(g,3);
  addVertice(g,4);
  addVertice(g,5);
  addVertice(g,6);
  addEdge(g,1,2,10);
  addEdge(g,1,3,9);
  addEdge(g,1,6,10);
  addEdge(g,2,4,11);
  addEdge(g,2,5,12);
  addEdge(g,3,4,16);
  addEdge(g,4,5,13);
  addEdge(g,4,5,17);
  addEdge(g,5,6,18);
  int Path[10],i=0;
  shortestPath(g,2,6,Path,&i);
  for(int j=i-1;j>=0;j--)
    printf("%d\n",Path[j]);
  return 0;
}
