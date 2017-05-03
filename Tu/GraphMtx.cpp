#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define Default_Vertex_Size 10  //给出默认顶点个数

#define T char   //元素类型

typedef struct GraphMtx   //建立图形结构
{ 
	int MaxVertices;   //最大顶点数
	int NumVertices;   //实际顶点数
	int NumEdges;     //实际边数

	T *VerticesList;   //存储点的结构  一块连续的存储空间
	int **Edge;       //存储边的结构  边的值 0 或1
}GraphMtx; 

void InitGraph(GraphMtx *g);
void ShowGraph(GraphMtx *g);
void InsertVertex(GraphMtx *g, T v);

void Push(GraphMtx *g);

//获取该顶点在存储顶点空间中位置,方便向二维数组中插入两个顶点之间边的关系  
int GetGraphPos(GraphMtx *g,T v); 
void InsertEdge(GraphMtx *g,T v1,T v2);
void RemoveEdge(GraphMtx *g,T v1,T v2);
void RemoveVertex(GraphMtx *g,T v1);
void DestroyGraph(GraphMtx *g);
int GetFirstNeighbor(GraphMtx *g,T v);
int GetNextNeighbor(GraphMtx *g,T v,T w);


void InitGraph(GraphMtx *g)
{
	g->MaxVertices = Default_Vertex_Size;
	g->NumVertices = g->NumEdges = 0;   //实际顶点数


     //专门申请一个空间来存放顶点
	g->VerticesList = (T *)malloc(sizeof(T)*(g->MaxVertices));//申请顶点的指针,该指针指向存储顶点空间的头部
	assert(g->VerticesList != NULL);
 
     //申请了一个数组矩阵  //对边(Edge)申请空间,存储边的为一个动态二维数组 //edge边指向二维数组
	g->Edge = (int **)malloc(sizeof(int *)* g->MaxVertices);  //先建立每一行的指针空间,
	assert(g->Edge != NULL);
	for(int i=0;i<g->MaxVertices;i++)   //在建立每一列的空间
	{
		g->Edge[i] = (int *)malloc(sizeof(int)* g->MaxVertices);
	}
	//初始化二维数组
	for(int i=0;i<g->MaxVertices;i++)
	{
		for(int j=0;j<g->MaxVertices;j++)
		{
			g->Edge[i][j] = 0;
		}
	}
}

void ShowGraph(GraphMtx *g)
{
	printf(" ");  //将相应的顶点的信息输出来
	for(int i=0;i<g->NumVertices;i++)
	{
		printf("%2c", g->VerticesList[i]);
	}
	printf("\n");

	for(int i=0;i<g->NumVertices;i++)
	{
		printf("%c", g->VerticesList[i]);

		for(int j=0;j<g->NumVertices;j++)
		{
			printf("%2d",g->Edge[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void InsertVertex(GraphMtx *g, T v)
{
	//判断顶点空间是否已满
	if(g->NumVertices >= g->MaxVertices)
		return ;
	//g所指的顶点列表
	g->VerticesList[g->NumVertices++] = v;
}

int GetGraphPos(GraphMtx *g,T v)
{
	for(int i=0;i<g->NumVertices;i++)
	{
		if(g->VerticesList[i] == v)
			return i;
	}
	return -1;
}

void InsertEdge(GraphMtx *g,T v1,T v2)
{
	int p1 = GetGraphPos(g,v1);
	int p2 = GetGraphPos(g,v2);
	if(p1 == -1 || p2 == -1)
		return ;

    if(g->Edge[p1][p2] != 0)
    	return ;
	g->Edge[p1][p2] = g->Edge[p2][p1] = 1;//由于属于无向图,所以其二位数组是对称的
	g->NumEdges++;     //边的条数增加一条
}

void RemoveEdge(GraphMtx *g,T v1,T v2)
{
	int p1 = GetGraphPos(g,v1);
	int p2 = GetGraphPos(g,v2);
	if(p1 == -1 || p2 == -1)
		return ;

	if(g->Edge[p1][p2] == 0 || g->Edge[p2][p1] == 0)
		return ;

	g->Edge[p1][p2] = g->Edge[p2][p1] = 0;
	g->NumEdges--;
}

void RemoveVertex(GraphMtx *g,T v1)   //删除顶点
{
	int p = GetGraphPos(g,v1);
	if(p == -1)
		return ;

    /*
在存储顶点的的空间中删除顶点(相当于在数组中删除一个元素),具体的实现方法一般有两个
1.将要删除的元素的后面的元素的依次向前移动一位,借此覆盖掉前面的元素,达到删除的效果,效率低下
2.将数组的最后一位元素覆盖掉要删除的元素,这样效率最高,但是破坏了原有数组顺序
    */
  
  //删除释放相应的顶点
	for(int i=p;i<g->NumVertices-1;i++)
	{
		//将存储在VerticesList中对应的顶点删除(覆盖)
		g->VerticesList[i] = g->VerticesList[i+1];
	}
	//删除与该顶点相关的边
    int numedges = 0;
	for(int i=0;i<g->NumVertices;i++)
	{
	    if(g->Edge[p][i]!=0)   //统计与该顶点相连接的边
		{ 
			numedges++;  //由于是无向的图,其边的数目对称,但是效果是相同的
		}
	}
    
    //将Edge这个二维数组中的行删除(覆盖)
    for(int i=p;i<g->NumVertices-1;i++)
    {
    	for(int j=0;j<g->NumVertices;j++)
        {    //将i+1行覆盖第i行的值
    		g->Edge[i][j] = g->Edge[i+1][j];
    	}			
    }

    for(int i=p;i<g->NumVertices;i++)
    {
    	for(int j=0;j<g->NumVertices;j++)
    	{
    		//将i+1列覆盖掉i列
    		g->Edge[j][i] = g->Edge[j][i+1];
    	}
    }
    g->NumVertices--;   //边数减小1
    g->NumEdges -= numedges;
}

void DestroyGraph(GraphMtx *g)
{
	free(g->VerticesList);   //释放顶点
	g->VerticesList = NULL;

	for(int i=0;i<g->NumVertices;i++)
	{
		free(g->Edge[i]);
	}
	free(g->Edge);
	g->Edge = NULL;
	g->MaxVertices = g->NumEdges  = g->NumVertices = 0;
}

int GetFirstNeighbor(GraphMtx *g,T v)   //获取与该顶点附近的第一个邻点
{
	int p = GetGraphPos(g,v);
	if(p == -1)
		return -1;

	for(int i=0;i<g->NumVertices;i++)
	{
		if(g->Edge[p][i] == 1)
			return i;
	}
	return -1;
} 
           //该函数的功能是求v的邻接点w的邻接点
int GetNextNeighbor(GraphMtx *g,T v,T w)   //w代表第一个邻接点
{
	int pv = GetGraphPos(g,v);
	int pw = GetGraphPos(g,w);
	if(pv == -1 || pw == -1)
		return -1;

	for(int i = pw +1;i<g->NumVertices;i++)
	{
		if(g->Edge[pv][i] == 1)
			return i;
	}
	return -1;
}

void Push(GraphMtx *g)
{
	printf("%d\n", g->NumEdges);
	printf("%d\n", g->NumVertices);
}



	int main()
{
	GraphMtx gm;
	InitGraph(&gm);
   
    InsertVertex(&gm,'A');
    InsertVertex(&gm,'B');
    InsertVertex(&gm,'C');
    InsertVertex(&gm,'D');
    InsertVertex(&gm,'E');

    InsertEdge(&gm,'A','B');
    InsertEdge(&gm,'A','D');
    InsertEdge(&gm,'C','B');
    InsertEdge(&gm,'E','B');
    InsertEdge(&gm,'E','C');
    InsertEdge(&gm,'C','D');
	ShowGraph(&gm);   //五个顶点会输出5行5列的二维数组矩阵

//	RemoveEdge(&gm,'A','D');
//	ShowGraph(&gm);
//    Push(&gm);

//	RemoveVertex(&gm,'B');
//	ShowGraph(&gm);
 //   Push(&gm);
 
 	int a = GetFirstNeighbor(&gm,'A');
 	printf("%d\n", a);

 	int p = GetNextNeighbor(&gm,'E','B');
 	printf("%d\n", p);
	return 0;
}