#include "BSTree.h"

//以下几个函数直接引用二叉树函数 
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

//以下函数为二叉树函数的组合引用 
status set_intersection(BSTree T1,BSTree T2,BSTree &T){
	//求集合T1与T2的交集，并赋值给T
	if(!T1) return OK;
	BSTree Ta=NULL;
	if(SearchAVL(T2,T1->data.id,Ta)==TRUE)    //如果结点T1在二叉树T2中存在，将结点T1插入二叉树T 
	    if(InsertAVL(T,T1->data)==ERROR) return ERROR;
	if(!set_intersection(T1->lchild,T2,T)) return ERROR;
	if(!set_intersection(T1->rchild,T2,T)) return ERROR;      //分别遍历T1左子树与右子树
	return OK;
}

status set_union(BSTree &T,BSTree T1){
	//求集合T1与T的并集，并赋值给T
	if(!T1) return OK;
	InsertAVL(T,T1->data); //将T1插入T 
	if(!set_union(T,T1->lchild)) return ERROR;  
	if(!set_union(T,T1->rchild)) return ERROR;
	//将T1的左右子树插入T 
	return OK;
}

status set_diffrence(BSTree &T,BSTree T1){
	//求集合T与T1的差集，并赋值给T
	if(!T1) return OK;
	DeleteAVL(T,T1->data.id);     //将T1从T中删除 
	if(!set_diffrence(T,T1->lchild)) return ERROR;       //将T1的左右子树从T中删除 
	if(!set_diffrence(T,T1->rchild)) return ERROR;
	return OK; 
}

status set_size(BSTree T){
	//计算二叉树中结点个数 
	if(!T) return ERROR;
	int a=set_size(T->lchild),b=set_size(T->rchild);
	return a+b+1;
}

status set_subset(BSTree T1,BSTree T2){
	//判断T2是否为T1的子集，若是子集返回TRUE，否则返回FALSE
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
	//判断集合T1与T2是否相等，若相等返回TRUE，否则返回FALSE 
	if(!set_subset(T1,T2)) return FALSE;
	if(!set_subset(T2,T1)) return FALSE;
	return TRUE;
}

void Traverse(BSTree T){
	//将集合以集合形式遍历输出
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
