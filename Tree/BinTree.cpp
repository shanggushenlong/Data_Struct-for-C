/*
二叉树的二叉链表存储表示
*/
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define ElemType char


//定义二叉树的节点
//二叉树的节点由一个数据元素和分别指向其左右子树的两个分之组成,则表示二叉树的链表中的节点至少包含3个域
//:数据域(data)'左右指针域
typedef struct BinTreeNode
{
	ElemType data;
	struct BinTreeNode *leftChild;  //左右指针
	struct BinTreeNode *rightChild;
}BinTreeNode;

//创建二叉树的类型
typedef struct BinTree 
{
	BinTreeNode *root;
	ElemType     refValue;//指针为空的时候的停止值stop flag
}BinTree;

void InitBinTree(BinTree *bt,ElemType ref);

void CreateBinTree_1(BinTree *bt);   //通过二级指针
void CreateBinTree_1(BinTree *bt,BinTreeNode **t);

void CreateBinTree_2(BinTree *bt);    //通过引用
void CreateBinTree_2(BinTree *bt,BinTreeNode *&t);

void CreateBinTree_3(BinTree *bt);   //创建通过返回值接收
BinTreeNode* CreateBinTree_3_(BinTree *bt);

void CreateBinTree_4(BinTree *bt,char *str);
void CreateBinTree_4(BinTree *bt,BinTreeNode *&t,char *str);


void PreOrder(BinTree *bt);
void PreOrder(BinTreeNode *t);

void InoOrder(BinTree *bt);
void InoOrder(BinTreeNode *t);

void PostOrder(BinTree *bt);
void PostOrder(BinTreeNode *t);



int size(BinTree *bt);
int size(BinTreeNode *t);
int Height(BinTree *bt);
int Height(BinTreeNode *t);
BinTreeNode* Search(BinTree *bt,ElemType key);
BinTreeNode* Search(BinTreeNode *t,ElemType key);
BinTreeNode* Parent(BinTree *bt,BinTreeNode *p);
BinTreeNode* Parent(BinTreeNode *t,BinTreeNode *p);
BinTreeNode* LeftChild(BinTreeNode *bt);
BinTreeNode* RightChild(BinTreeNode *bt);
bool BinTreeIsEmpty(BinTree *bt);
void Copy(BinTree *t1,BinTree *t2);
void Copy(BinTreeNode *&t1,BinTreeNode *&t2);
void BinTreeClear(BinTree *bt);
void BinTreeClear(BinTreeNode *bt);

void InitBinTree(BinTree *bt,ElemType ref)
{
	bt->root = NULL;
	bt->refValue = ref;
}

void CreateBinTree_1(BinTree *bt)
{
	CreateBinTree_1(bt,&(bt->root));
}                                //第二个参数为树根
void CreateBinTree_1(BinTree *bt,BinTreeNode **t)//由于root本身为指针,则应该用二级指针
{
	ElemType Item;
	scanf("%c",&Item);
	if(Item == bt->refValue)
		(*t) = NULL;
	else
	{
		//申请节点Node,为二叉树节点类型
		(*t) = (BinTreeNode *)malloc(sizeof(BinTreeNode));
		assert(((*t)) != NULL);

		(*t)->data = Item;
		//以该节点为root根节点递归创建相应的左右节点
		CreateBinTree_1(bt,&((*t)->leftChild));
		CreateBinTree_1(bt,&((*t)->rightChild));
	}
}

void CreateBinTree_2(BinTree *bt)
{
	CreateBinTree_2(bt,bt->root);
}
void CreateBinTree_2(BinTree *bt,BinTreeNode *&t)
{
	ElemType Item;
	scanf("%c",&Item);
	if(Item == bt->refValue)
		t = NULL;
	else
	{
		t = (BinTreeNode *)malloc(sizeof(BinTreeNode));
		assert(t != NULL);

		t->data = Item;
		CreateBinTree_2(bt,t->leftChild);
		CreateBinTree_2(bt,t->rightChild);
	}
}

void CreateBinTree_3(BinTree *bt)
{
	bt->root = CreateBinTree_3_(bt);
}
BinTreeNode* CreateBinTree_3_(BinTree *bt)
{
	ElemType Item;
	scanf("%c",&Item);
	if(Item == bt->refValue)
		return NULL;
	else
	{
		BinTreeNode *t = (BinTreeNode *)malloc(sizeof(BinTreeNode));
		assert(t!=NULL);
		t->data = Item;
		t->leftChild = CreateBinTree_3_(bt);
		t->rightChild = CreateBinTree_3_(bt);
		return t;
	}
}

void CreateBinTree_4(BinTree *bt,char *str)
{
	CreateBinTree_4(bt,bt->root,str);
}
//str传递的时候是将字符串的首地址,相当于将此时有一个指针指向字符串的第一个字符
void CreateBinTree_4(BinTree *bt,BinTreeNode *&t,char *str)
{
	if(*str == bt->refValue)
		t = NULL;
	else
	{
		t = (BinTreeNode *)malloc(sizeof(BinTreeNode));
		assert(t !=NULL);
		t->data = *str;
		CreateBinTree_4(bt,t->leftChild,str++);
		CreateBinTree_4(bt,t->rightChild,str++);
	}
}


void PreOrder(BinTree *bt)
{
	PreOrder(bt->root);
}
void PreOrder(BinTreeNode *t)   //t是树根
{
	if(t!=NULL)
	{
		printf("%2c",t->data );
		PreOrder(t->leftChild);
		PreOrder(t->rightChild);
	}
}

void InoOrder(BinTree *bt)
{
	InoOrder(bt->root);
}
void InoOrder(BinTreeNode *t)
{
	if(t!=NULL)
	{
		InoOrder(t->leftChild);
		printf("%2c",t->data );
		InoOrder(t->rightChild);
	}
}

void PostOrder(BinTree *bt)
{
	PostOrder(bt->root);
}
void PostOrder(BinTreeNode *t)
{

	if(t!=NULL)
	{
		PostOrder(t->leftChild);
		PostOrder(t->rightChild);
		printf("%2c",t->data );
		
	}
}


int size(BinTree *bt)
{
	return size(bt->root);
}
int size(BinTreeNode *t)
{
	if(t == NULL)
		return 0;
	else
	{
		return size(t->leftChild)+size(t->rightChild)+1;
	}
}

int Height(BinTree *bt)
{
	return Height(bt->root);
}
int Height(BinTreeNode *t)
{
	if(t == NULL)
		return 0;
	else
	{
		int left_height = Height(t->leftChild);
		int right_height = Height(t->rightChild);
		if(left_height > right_height)
			return left_height + 1;
		else
			return right_height + 1;
	}
}

BinTreeNode* Search(BinTree *bt,ElemType key)
{
	return Search(bt->root,key);
}
BinTreeNode* Search(BinTreeNode *t,ElemType key)
{
	if(t == NULL)
	{
		printf("该节点不存在\n");
		return NULL;
	}

	if(t->data == key)
	{
		printf("该节点存在\n" );
		return t;
	}

	BinTreeNode *p = Search(t->leftChild,key);
	if(p != NULL)
	{
		printf("该节点存在\n" );
		return p;
	}
	else
	{
		printf("该节点不存在\n");
		return NULL;
	}
	return Search(t->rightChild,key);
}

BinTreeNode* Parent(BinTree *bt,BinTreeNode *p)
{
	return Parent(bt->root,p);
}
BinTreeNode* Parent(BinTreeNode *t,BinTreeNode *p)
{
	if(t == NULL || p == NULL)
	{
		printf("父节点不存在\n");
		return NULL;
	}

	if(t->leftChild == p || t->rightChild == p)
	{
		printf("父节点存在\n");
		return t;
	}

	BinTreeNode *q = Parent(t->leftChild,p);  //左节点不存在的情况下,在查找右节点
	if(q != NULL)
	{
		printf("父节点存在\n");
		return q;
	}
	return Parent(t->rightChild,p);
}

BinTreeNode* LeftChild(BinTreeNode *bt)
{
	if(bt != NULL)
		return bt->leftChild;
	return NULL;
}
BinTreeNode* RightChild(BinTreeNode *bt)
{
	if(bt != NULL)
		return bt->rightChild;
	return NULL;
}

bool BinTreeIsEmpty(BinTree *bt)
{
	return bt->root==NULL;
}

void Copy(BinTree *t1,BinTree *t2)
{
	Copy(t1->root,t2->root);
}
void Copy(BinTreeNode *&t1,BinTreeNode *&t2)
{
	if(t2 == NULL)
		t1 = NULL;
	else
	{
		t1 = (BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t1 != NULL);
		t1->data = t2->data;
		Copy(t1->leftChild,t2->leftChild);
		copy(t1->rightChild,t2->rightChild);
	}
}

void BinTreeClear(BinTree *bt)
{
	BinTreeClear(bt->root);
}
void BinTreeClear(BinTreeNode *bt)
{
	if(t != NULL)
	{
		BinTreeClear(t->leftChild);
		BinTreeClear(t->rightChild);
		free(t);
		t = NULL;
}


int main()
{
	char *str ="ABC##DE##F##G#H##";
	BinTree mytree;
	InitBinTree(&mytree,'#');

	CreateBinTree_2(&mytree);

	PreOrder(&mytree);
	printf("\n");

	InoOrder(&mytree);
	printf("\n");

	PostOrder(&mytree);
	printf("\n");

    printf("size = %d\n", size(&mytree));
    printf("Height = %d\n",Height(&mytree));
    BinTreeNode *p = Search(&mytree,'B');
    BinTreeNode *q =Parent(&mytree, p);
	
	return 0;
}