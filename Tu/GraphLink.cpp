#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define Default_Vertext_Size 10
#define T char

typedef struct Edge  //定义邻接表的边,实际上为一个链表 
{
	int dest;  //顶点的下标
	struct Edge *link;    //下一个边的指针
}Edge;

typedef struct Vertex   //存储顶点的结构,定义顶点结构
{
	T data;      //存储了顶点的信息,
	Edge *adj;   //表示顶点结构指向了边,指向边的指针
}Vertex;

typedef struct GraphLnk
{
	int MaxVertices;//最大顶点个数
	int NumVertices;//实际顶点个数
	int NumEdges;//实际边数


	Vertex *NodeTable;    //存储顶点的结构表
}GraphLnk;

void InitGraph(GraphLnk *g);
void ShowGraph(GraphLnk *g);
void InsertVertex(GraphLnk *g,T v);



void InitGraph(GraphLnk *g)
{
	g->MaxVertices = Default_Vertext_Size;
	g->NumVertices = g->NumEdges = 0;

	g->NodeTable = (Vertex *)malloc(sizeof(Vertex)* Default_Vertext_Size);
    for(int i=0;i<g->MaxVertices;i++)
    {
    	g->NodeTable[i].adj = NULL;
    }
}

void ShowGraph(GraphLnk *g)
{
	Edge *p;
	for (int i = 0; i < g->NumVertices; ++i)
	{ 
		printf("%c:>",g->NodeTable[i].data);
//		p = g->NodeTable[i].adj;
		while(p != NULL)
		{
			printf("%d-->",p->dest);
			p = p->link;
		}
		printf("\n");
	}
}

void InsertVertex(GraphLnk *g,T v)
{
	if(g->NumVertices >= g->MaxVertices)   //判断存储空间是否已满
		return ;

	g->NodeTable[g->NumVertices++].data = v;
}


int main()
{
	GraphLnk gl;
	InitGraph(&gl);

	InsertVertex(&gl,'A');
	InsertVertex(&gl,'B');
	InsertVertex(&gl,'C');
    InsertVertex(&gl,'D');
    InsertVertex(&gl,'E');
 	ShowGraph(&gl);

	return 0;
}