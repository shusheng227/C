#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <math.h>

/*---------------����----------------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1

const int middle=32;    //����ͼ�λ���ʾ������ 

//�������� 
struct BSTNode; 
typedef int status;
typedef struct ElemType{
	int id;
	char name[10];    //����
	//���ĸ�����������ͷ��� 
	BSTNode* friends;   //���Ѽ�
	BSTNode* fans;      //��˿��
	BSTNode* attention; //��ע�˼� 
	BSTNode* hobby;     //ϲ�� 
}ElemType;

//ƽ�������������Ͷ��� 
typedef struct BSTNode{
	ElemType         data;
	int              h;                //���ĸ߶� 
	struct BSTNode   *lchild,*rchild;  //���Һ���ָ�� 
}BSTNode,*BSTree;

void R_Rotate(BSTree &p){
	//����*pΪ���Ķ��������������������������pָ���µ�������㣬
	//����ת֮ǰ���������ĸ����
	BSTree lc=p->lchild;
	p->lchild=lc->rchild;
	lc->rchild=p;
	p=lc;
}

void L_Rotate(BSTree &p){
	//����*pΪ���Ķ��������������������������pָ���µ�������㣬
	//����ת֮ǰ���������ĸ����
	BSTree lc=p->rchild;
	p->rchild=lc->lchild;
	lc->lchild=p;
	p=lc;
}

status depth(BSTree T){
	//���㲢����T����� 
	if(!T) return ERROR;
	int a=depth(T->lchild), b=depth(T->rchild);
	return (a>b)? a+1 : b+1;
}

void LeftBalance(BSTree &T){
	//����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת����
	//���㷨����ʱ��ָ��Tָ���µĸ����
	BSTree lc=T->lchild;
	//�½�����*T�����ӵ��������ϣ�Ҫ������������
	if(depth(lc->lchild)>depth(lc->rchild)) R_Rotate(T);
	//�½�����*T�����ӵ��������ϣ�Ҫ��˫������ 
	else{
		L_Rotate(T->lchild);
		R_Rotate(T);
	}
}

void RightBalance(BSTree &T){
	//����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת����
	//���㷨����ʱ��ָ��Tָ���µĸ����
	BSTree rc=T->rchild;
	//�½�����*T���Һ��ӵ��������ϣ�Ҫ������������
	if(depth(rc->rchild)>depth(rc->lchild)) L_Rotate(T);
	else{
		R_Rotate(T->rchild);
		L_Rotate(T);
	}
}

status InsertAVL(BSTree &T,ElemType e){
	//����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ������Ԫ��

	if(!T){//�����½��
	   T=(BSTree)malloc(sizeof(BSTNode)); T->data=e;
	   T->lchild=NULL; T->rchild=NULL;T->h=0;
	}
	else{
		if(e.id==T->data.id)  return ERROR; //���T�Ĺؼ�����e��ͬ 
		else if(e.id<T->data.id){
			if(!InsertAVL(T->lchild,e)) return ERROR;   //δ����
			if(depth(T->lchild)-depth(T->rchild)==2) LeftBalance(T); 
		}
		else{
			if(!InsertAVL(T->rchild,e)) return ERROR;   //δ����
			if(depth(T->lchild)-depth(T->rchild)==-2) RightBalance(T); 
		}
	}
	return OK; 
}

status DeleteAVL(BSTree &T,int e){
	//ɾ��������T�н��idΪe�Ľ��
	if(!T)  return ERROR;            //���������� 
	BSTree pre=NULL;
	if(T->data.id==e){                             //�ҵ���� 
		if(T->lchild==NULL&&T->rchild==NULL){   //�ý�����ӽڵ� 
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
			if(depth(T->lchild)>depth(T->rchild)){ //���������������� 
				pre=T->lchild;
				while(pre->rchild) pre=pre->rchild;       //Ѱ������������������
				T->data=pre->data;
				DeleteAVL(T->lchild,pre->data.id);
			}
			else{                                 //���������������� 
				pre=T->rchild;
				while(pre->lchild) pre=pre->lchild;    //Ѱ������������������
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
	//��ʼ������ƽ�����������������
	//�����������ʼ������һ���µ�ƽ�����������
	if(T) return ERROR;
	T=(BSTree)malloc(sizeof(BSTNode));
	if(!T) return ERROR;
	T->lchild=T->rchild=NULL; T->h=0;
	InitElem(T->data);
	return OK;
}

status DestroyAVL(BSTree &T){
	//��ʼ������ƽ�����������T����
	//����������ݻ�ƽ�����������T 
	if(!T) return ERROR;
	DestroyAVL(T->lchild); DestroyAVL(T->rchild);
	free(T); T=NULL;
	return OK;
}

status PTraverseAVL(BSTree T){
	//��������T�������������
	if(!T) return ERROR;
	printf("%3d ",T->data.id);
	printf("%s  ",T->data.name);
	PTraverseAVL(T->lchild);  PTraverseAVL(T->rchild);
	return OK; 
}

void gotoxy(int x,int y){ 
	//�ƶ���꣬������������꣨x��y) 
	COORD coord={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int power(int x){
	//���㲢����2��x���ݣ����ڶ�����ͼ�λ���� 
	int y=1;
	for(int i=0;i<x;i++){
		y*=2;
	}
	return y;
}

status height(BSTree &T,int i){
	//���������T��������Ȳ���ֵ
	if(!T) return ERROR;
	T->h=i;
	height(T->lchild,i+1);  height(T->rchild,i+1);
	return OK;
}

status TraversAVL(int x,int y,BSTree T){
	//ͼ�λ���������� 
	if(!T) return ERROR;
	gotoxy(x,y);               //�������ڣ���������id 
	printf("%d",T->data.id);
	int j=middle/power(T->h);
	if((!T->lchild)&&(!T->rchild)) return OK; //�ý���������������������� 
	gotoxy(x,y+1);   printf("|");
	if(T->lchild){          //���������id
		gotoxy(x-j,y+3);  printf("|");
		gotoxy(x-j,y+2);
		for(int i=0;i<j;i++)	printf("-");
		TraversAVL(x-j,y+4,T->lchild);
	}
	if(T->rchild){          //���������
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
	//�ڶ�����T�в��ҹؼ���Ϊe�Ľ�㣬�����ڸý�㣬����TRUE,
	//��ʹTaָ��ý��,���򷵻�FALSE
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
	//��������T������fpָ����ļ��� 
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
	//��fp�ļ���Ϊfilename���ļ��е����ݼ����������T��
	FILE *fp;
	if ((fp=fopen(filename,"rb"))==NULL){   //�ļ���ʧ�� 
	    printf("�ļ���ʧ�ܣ�\n ");
	    return ERROR;        
    }
	ElemType e; InitElem(e);
	while(fread(&e,sizeof(ElemType),1,fp)){
		if(!InsertAVL(T,e)) return ERROR;
	}
	//����޷���ȡʱ�Ƿ��ļ�β 
	if(!feof(fp))  return ERROR;
	height(T,1);
	fclose(fp);
	return OK;
}
