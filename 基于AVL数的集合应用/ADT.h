#include "BSTree.h"

//���¼�������ֱ�����ö��������� 
status set_init(BSTree &T){
	return InitAVL(T);
}

status set_destroy(BSTree &T){
	return DestroyAVL(T);
}

status set_member(BSTree T,int e,BSTree &Ta){
	return SearchAVL(T,e,Ta);
}

status set_insert(BSTree &T,ElemType e){
	return InsertAVL(T,e);
}

status set_remove(BSTree &T,int e){
	return DeleteAVL(T,e);
}

//���º���Ϊ������������������� 
status set_intersection(BSTree T1,BSTree T2,BSTree &T){
	//�󼯺�T1��T2�Ľ���������ֵ��T
	if(!T1) return OK;
	BSTree Ta=NULL;
	if(SearchAVL(T2,T1->data.id,Ta)==TRUE)    //������T1�ڶ�����T2�д��ڣ������T1���������T 
	    if(InsertAVL(T,T1->data)==ERROR) return ERROR;
	if(!set_intersection(T1->lchild,T2,T)) return ERROR;
	if(!set_intersection(T1->rchild,T2,T)) return ERROR;      //�ֱ����T1��������������
	return OK;
}

status set_union(BSTree &T,BSTree T1){
	//�󼯺�T1��T�Ĳ���������ֵ��T
	if(!T1) return OK;
	InsertAVL(T,T1->data); //��T1����T 
	if(!set_union(T,T1->lchild)) return ERROR;  
	if(!set_union(T,T1->rchild)) return ERROR;
	//��T1��������������T 
	return OK;
}

status set_diffrence(BSTree &T,BSTree T1){
	//�󼯺�T��T1�Ĳ������ֵ��T
	if(!T1) return OK;
	DeleteAVL(T,T1->data.id);     //��T1��T��ɾ�� 
	if(!set_diffrence(T,T1->lchild)) return ERROR;       //��T1������������T��ɾ�� 
	if(!set_diffrence(T,T1->rchild)) return ERROR;
	return OK; 
}

status set_size(BSTree T){
	//����������н����� 
	if(!T) return ERROR;
	int a=set_size(T->lchild),b=set_size(T->rchild);
	return a+b+1;
}

status set_subset(BSTree T1,BSTree T2){
	//�ж�T2�Ƿ�ΪT1���Ӽ��������Ӽ�����TRUE�����򷵻�FALSE
	if(T2==NULL) return TRUE;
	BSTree Ta=NULL;
	if(set_member(T1,T2->data.id,Ta)){
		if(!set_subset(T1,T2->lchild)) return FALSE;
		if(!set_subset(T1,T2->rchild)) return FALSE;
		return TRUE;
	}
	else return FALSE;
}

status set_equal(BSTree T1,BSTree T2){
	//�жϼ���T1��T2�Ƿ���ȣ�����ȷ���TRUE�����򷵻�FALSE 
	if(!set_subset(T1,T2)) return FALSE;
	if(!set_subset(T2,T1)) return FALSE;
	return TRUE;
}

void Traverse(BSTree T){
	//�������Լ�����ʽ�������
	if(T){
		printf("%d",T->data.id);
	    if(T->lchild){
		    printf(",");  Traverse(T->lchild);
	    }
	    if(T->rchild){
		    printf(",");  Traverse(T->rchild);
	    }
	} 
}

status set_traverse(BSTree T){
	if(!T) return ERROR;
	printf("{ ");
	Traverse(T);
	printf(" }\n");
	return OK;
} 
