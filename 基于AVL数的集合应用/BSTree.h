#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <math.h>

/*---------------常量----------------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1

const int middle=32;    //用于图形化显示二叉树 

//数据类型 
struct BSTNode; 
typedef int status;
typedef struct ElemType{
	int id;
	char name[10];    //姓名
	//这四个二叉树集无头结点 
	BSTNode* friends;   //好友集
	BSTNode* fans;      //粉丝集
	BSTNode* attention; //关注人集 
	BSTNode* hobby;     //喜好 
}ElemType;

//平衡二叉树结点类型定义 
typedef struct BSTNode{
	ElemType         data;
	int              h;                //树的高度 
	struct BSTNode   *lchild,*rchild;  //左右孩子指针 
}BSTNode,*BSTree;

void R_Rotate(BSTree &p){
	//对以*p为根的二叉排序树进行右旋处理，处理后p指向新的树根结点，
	//即旋转之前的左子树的根结点
	BSTree lc=p->lchild;
	p->lchild=lc->rchild;
	lc->rchild=p;
	p=lc;
}

void L_Rotate(BSTree &p){
	//对以*p为根的二叉排序树进行左旋处理，处理后p指向新的树根结点，
	//即旋转之前的右子树的根结点
	BSTree lc=p->rchild;
	p->rchild=lc->lchild;
	lc->lchild=p;
	p=lc;
}

status depth(BSTree T){
	//计算并返回T的深度 
	if(!T) return ERROR;
	int a=depth(T->lchild), b=depth(T->rchild);
	return (a>b)? a+1 : b+1;
}

void LeftBalance(BSTree &T){
	//对以指针T所指结点为根的二叉树作左平衡旋转处理，
	//本算法结束时，指针T指向新的根结点
	BSTree lc=T->lchild;
	//新结点插在*T的左孩子的左子树上，要作单右旋处理
	if(depth(lc->lchild)>depth(lc->rchild)) R_Rotate(T);
	//新结点插在*T的左孩子的右子树上，要作双旋处理 
	else{
		L_Rotate(T->lchild);
		R_Rotate(T);
	}
}

void RightBalance(BSTree &T){
	//对以指针T所指结点为根的二叉树作右平衡旋转处理，
	//本算法结束时，指针T指向新的根结点
	BSTree rc=T->rchild;
	//新结点插在*T的右孩子的右子树上，要作单左旋处理
	if(depth(rc->rchild)>depth(rc->lchild)) L_Rotate(T);
	else{
		R_Rotate(T->rchild);
		L_Rotate(T);
	}
}

status InsertAVL(BSTree &T,ElemType e){
	//若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个数据元素

	if(!T){//插入新结点
	   T=(BSTree)malloc(sizeof(BSTNode)); T->data=e;
	   T->lchild=NULL; T->rchild=NULL;T->h=0;
	}
	else{
		if(e.id==T->data.id)  return ERROR; //结点T的关键字与e相同 
		else if(e.id<T->data.id){
			if(!InsertAVL(T->lchild,e)) return ERROR;   //未插入
			if(depth(T->lchild)-depth(T->rchild)==2) LeftBalance(T); 
		}
		else{
			if(!InsertAVL(T->rchild,e)) return ERROR;   //未插入
			if(depth(T->lchild)-depth(T->rchild)==-2) RightBalance(T); 
		}
	}
	return OK; 
}

status DeleteAVL(BSTree &T,int e){
	//删除二叉树T中结点id为e的结点
	if(!T)  return ERROR;            //二叉树不变 
	BSTree pre=NULL;
	if(T->data.id==e){                             //找到结点 
		if(T->lchild==NULL&&T->rchild==NULL){   //该结点无子节点 
			free(T); T=NULL;
		}
		else if(T->lchild!=NULL&&T->rchild==NULL){
			pre=T; T=T->lchild;	
			free(pre); pre=NULL;
		}
		
		else if(T->lchild==NULL&&T->rchild!=NULL){
			pre=T; T=T->rchild;
			free(pre); pre=NULL;
		}
		else{
			if(depth(T->lchild)>depth(T->rchild)){ //左子树比右子树高 
				pre=T->lchild;
				while(pre->rchild) pre=pre->rchild;       //寻找左子树的最右子树
				T->data=pre->data;
				DeleteAVL(T->lchild,pre->data.id);
			}
			else{                                 //左子树比右子树低 
				pre=T->rchild;
				while(pre->lchild) pre=pre->lchild;    //寻找右子树的最左子树
				T->data=pre->data;
				DeleteAVL(T->rchild,pre->data.id); 
			}
		}
		return OK; 
	}
	else if(T->data.id>e){
		if(!DeleteAVL(T->lchild,e)) return ERROR;
		if(depth(T->lchild)-depth(T->rchild)==-2) RightBalance(T);
	}
	else{
		if(!DeleteAVL(T->rchild,e)) return ERROR;
		if(depth(T->lchild)-depth(T->rchild)==2) LeftBalance(T);
	}
	return OK;
}

void InitElem(ElemType &e){
	e.id=0; e.name[0]='\0';
	e.attention=NULL; e.fans=NULL;
	e.friends=NULL;  e.hobby=NULL;
}

status InitAVL(BSTree &T){
	//初始条件：平衡二叉排序树不存在
	//操作结果：初始化创建一个新的平衡二叉排序树
	if(T) return ERROR;
	T=(BSTree)malloc(sizeof(BSTNode));
	if(!T) return ERROR;
	T->lchild=T->rchild=NULL; T->h=0;
	InitElem(T->data);
	return OK;
}

status DestroyAVL(BSTree &T){
	//初始条件：平衡二叉排序树T存在
	//操作结果：摧毁平衡二叉排序树T 
	if(!T) return ERROR;
	DestroyAVL(T->lchild); DestroyAVL(T->rchild);
	free(T); T=NULL;
	return OK;
}

status PTraverseAVL(BSTree T){
	//将二叉树T以先序序列输出
	if(!T) return ERROR;
	printf("%3d ",T->data.id);
	printf("%s  ",T->data.name);
	PTraverseAVL(T->lchild);  PTraverseAVL(T->rchild);
	return OK; 
}

void gotoxy(int x,int y){ 
	//移动光标，将光标移至坐标（x，y) 
	COORD coord={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int power(int x){
	//计算并返回2的x次幂，用于二叉树图形化输出 
	int y=1;
	for(int i=0;i<x;i++){
		y*=2;
	}
	return y;
}

status height(BSTree &T,int i){
	//计算二叉树T各结点的深度并赋值
	if(!T) return ERROR;
	T->h=i;
	height(T->lchild,i+1);  height(T->rchild,i+1);
	return OK;
}

status TraversAVL(int x,int y,BSTree T){
	//图形化输出二叉树 
	if(!T) return ERROR;
	gotoxy(x,y);               //根结点存在，输出根结点id 
	printf("%d",T->data.id);
	int j=middle/power(T->h);
	if((!T->lchild)&&(!T->rchild)) return OK; //该结点无左右子树，结束函数 
	gotoxy(x,y+1);   printf("|");
	if(T->lchild){          //输出左子树id
		gotoxy(x-j,y+3);  printf("|");
		gotoxy(x-j,y+2);
		for(int i=0;i<j;i++)	printf("-");
		TraversAVL(x-j,y+4,T->lchild);
	}
	if(T->rchild){          //输出右子树
		gotoxy(x+j,y+3);  printf("|");
		gotoxy(x,y+2);
		for(int i=0;i<j;i++)	printf("-");
		TraversAVL(x+j,y+4,T->rchild);
	}
	return OK;	 
}

status TraverseAVL(int x,int y,BSTree T){
	height(T,1);
	TraversAVL(x,y,T);
	printf("\n");
}

status SearchAVL(BSTree T,int e,BSTree &Ta){
	//在二叉树T中查找关键字为e的结点，若存在该结点，返回TRUE,
	//并使Ta指向该结点,否则返回FALSE
	if(!T) return FALSE;
	if(e==T->data.id){
		Ta=T;
		return TRUE;
	}
	else if(e<T->data.id){	
		if(SearchAVL(T->lchild,e,Ta)) return TRUE;
	}	
	else {
		if(SearchAVL(T->rchild,e,Ta)) return TRUE;
	}    
	return FALSE;
}

status Save(BSTree T,FILE *fp){
	//将二叉树T保存入fp指向的文件中 
	if(!T) return OK;
	else{
		if(!fwrite(&(T->data),sizeof(ElemType),1,fp)) 
		return ERROR; 
	}
	if(!Save(T->lchild,fp)) return ERROR;
	if(!Save(T->rchild,fp)) return ERROR;
	return OK;
}

status Load(BSTree &T,char *filename){
	//将fp文件名为filename的文件中的内容加载入二叉树T中
	FILE *fp;
	if ((fp=fopen(filename,"rb"))==NULL){   //文件打开失败 
	    printf("文件打开失败！\n ");
	    return ERROR;        
    }
	ElemType e; InitElem(e);
	while(fread(&e,sizeof(ElemType),1,fp)){
		if(!InsertAVL(T,e)) return ERROR;
	}
	//检查无法读取时是否到文件尾 
	if(!feof(fp))  return ERROR;
	height(T,1);
	fclose(fp);
	return OK;
}
