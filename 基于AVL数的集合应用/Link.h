#include "应用层.h"

typedef struct Node{
	int    id;
	char   name[10];    //集合名称
	BSTree T;           //集合头指针
}Node;

typedef struct List{ 
    Node   data;
	struct List *prior;
	struct List *next; 
}List,*LinkList;


status TraverseLink(LinkList L){
	//输出链表L中所有集合的id 
	if(!L) return ERROR;
	LinkList q=L;
	while(q){
		printf("%2d  ",q->data.id);
		q=q->next;
	}
	printf("\n");
	return OK;
}

status search_link(LinkList L,int id,LinkList &L1){
	//对链表L进行查询，若链表L中存在集合id为id的结点，将该结点赋值给L1，
	//并返回TRUE，否则返回FALSE
	if(!L) return ERROR;
	LinkList q=L;
	while(q){
		if(q->data.id==id){
			L1=q; return TRUE;
		}
		else q=q->next;
	}
	return FALSE;
}

status List_insert(LinkList &L,Node e){
	//将数据e插入链表L中 
	if(!L){
		L=(LinkList)malloc(sizeof(List));
	    if(!L) return ERROR;
	    L->data=e;
	    L->prior=NULL;
		L->next=NULL;
	}
	else{
		LinkList q=NULL;
		q=(LinkList)malloc(sizeof(List));
	    if(!q) return ERROR;
	    q->data=e;
	    q->prior=NULL;
	    q->next=L;
	    L->prior=q;
	    L=q;
	}
	return OK;
}

status save_list(LinkList L){
	//将链表信息保存入文件List.dat中 
	if(!L) return ERROR;
	FILE *fp;
	LinkList q=L;
	if((fp=fopen("List.dat","wb"))==NULL){   //文件打开失败 
	    printf("文件List.dat打开失败！\n ");
	    return ERROR;        
    }
    while(q){
    	if(!fwrite(&(q->data),sizeof(Node),1,fp)) {
    		fclose(fp);  return ERROR;
        }
		q=q->next;
	}
	fclose(fp);
	if(!L) return ERROR;
	return OK;
}

status save_linklist(LinkList L){
	//将链表L的集合保存入集合名文件中 
	if(!L) return ERROR;
	FILE *fp;
	LinkList q=L;
	if(!save_list(L)) return ERROR;
	while(q){	
		if ((fp=fopen(q->data.name,"wb"))==NULL){   //文件打开失败 
	        return ERROR;        
        }
    	if(!Save(q->data.T,fp)) {
    		fclose(fp);  return ERROR;
		}
		fclose(fp);
		q=q->next;
	}
	return OK;
}

status load_linklist(LinkList &L){
	//将文件List.dat的信息载入链表L中 
	L=NULL; 
	FILE *fp;
	LinkList q=NULL;
	if((fp=fopen("List.dat","rb"))==NULL){   //文件打开失败 
	    printf("文件List.dat打开失败！\n ");
	    return ERROR;        
    }
    while(!feof(fp)){
    	q=(LinkList)malloc(sizeof(List));
    	if(!q){
    		printf("分配空间出错！\n");  return ERROR; 
		}
    	if(!fread(&(q->data),sizeof(Node),1,fp)) break;
		if(!List_insert(L,q->data))	return ERROR;		
	}
	fclose(fp);
	q=L;
	while(q){
		q->data.T=NULL;
		if(!Load(q->data.T,q->data.name))return ERROR;
		q=q->next;
	}
	return OK;
}

status tree_to_link(LinkList &L,BSTree T){
	//将二叉树T存入链表L
	LinkList L1=NULL;
	Node q;
	int a=0;
	char setname[10];
	if(!L) printf("当前集合文件中无集合！\n");
	else{
		printf("当前所有集合id包括：");
	    TraverseLink(L);
	}
	printf("请输入集合的id：");
	scanf("%d",&a);
	while(search_link(L,a,L1)){
		printf("此id已存在，请重新输入：");
		scanf("%d",&a);
	}
	printf("请输入集合名：");
	scanf("%s",setname);
	q.id=a; strcpy(q.name,setname);
	q.T=T;
	if(List_insert(L,q)){
		printf("该集合已保存入集合文件！\n"); return OK;
	}
	else{
		printf("保存失败！\n"); return ERROR;
	}
}

void set_menu(LinkList &L,BSTree &T,LinkList &buff){
	int i=1;
	int id=0;
	BSTree Ta=NULL;   //辅助二叉树
	char c='y';
	Node e;
	ElemType a;
	while(i){
		system("cls");
		printf("\n-----------------集合操作系统------------------------\n\n");
		printf("  1.进入集合操作        2.上一集合         3.下一集合\n");
    	printf("  4.set_init            5.set_destroy      6.set_member\n");
      	printf("  7.set_size            8.set_insert       9.set_remove\n");
    	printf(" 10.set_traverse       11.set_save         0.返回\n");
    	printf("\n-----------------------------------------------------\n");
    	printf("请输入你的操作[0-10]：");
    	scanf("%d",&i); getchar();
        switch(i){
		case 0: break;
		case 1:
			if(L){
				printf("已进入集合操作！\n");
				system("pause"); break;
			}
			if(!load_linklist(L)){
				printf("加载集合失败！\n");
			}
			else{
				printf("集合加载成功！\n");
				buff=L;
			    T->lchild=L->data.T;
			    printf("开始集合操作，当前为集合%d\n",L->data.id);
			}
			system("pause"); break;
		case 2:
			if(buff->prior==NULL){
				printf("已至第一个集合！\n");
			}
			else{
				buff=buff->prior;
				T->lchild=buff->data.T;
				printf("已由集合%d切换至集合%d！\n",buff->next->data.id,buff->data.id);
			}
			system("pause"); break;
		case 3:
			if(buff->next==NULL){
				printf("已至最后一个集合！\n");
			}
			else{
				buff=buff->next;
				T->lchild=buff->data.T;
				printf("已由集合%d切换至集合%d！\n",buff->prior->data.id,buff->data.id);
			}
			system("pause"); break;
		case 4:
			if(T) printf("该集合已存在，请先进行摧毁！\n");
			else{
				if(set_init(T)) printf("初始化成功！\n");
			    else printf("初始化失败！\n");
			}
			system("pause"); break;
		case 5:
			if(!T) printf("集合不存在，摧毁失败！\n");
			else{
				if(set_destroy(T)) printf("摧毁成功！\n"); 
		    	else printf("摧毁失败！\n");
			}	
			system("pause"); break;
		case 6:
			if(!T) printf("集合不存在，请先进行初始化！\n");
			else if(!T->lchild) printf("该集合为空，请先插入数据！\n");
			else{
				printf("请输入id：");
			    scanf("%d",&id);getchar();
			    if(set_member(T->lchild,id,Ta)){
			    	printf("查找成功！\n");
			        printf("id为%d的是%s\n",id,Ta->data.name);
			    }
			    else printf("查找失败!\n");
			} 
			system("pause"); break;
		case 7:
			if(!T) printf("集合不存在，请先进行初始化！\n");
			else if(!T->lchild) printf("该集合为空，请先插入数据！\n");
			else{
				printf("当前集合为%d，其成员个数为%d!\n",buff->data.id,set_size(T->lchild));
			}
			system("pause"); break;
		case 8:
			c='y';
			if(!T) printf("集合不存在，请先进行初始化！\n");
			else{
				while(c=='y'){
					printf("请输入id："); scanf("%d",&a.id); getchar(); 
			        printf("请输入姓名："); scanf("%s",&a.name); getchar();
			        if(set_insert(T->lchild,a)){ 
			    	    printf("插入成功！\n");
			    	    height(T->lchild,1);
				    }
			        else printf("插入失败！\n");
			        printf("是否继续('y'or'n')？：");
					scanf("%c",&c); getchar();
					if(c!='y'&&c!='n'){
						printf("请重新输入：");
						scanf("%c",&c); getchar();
					}
				}	
			}
			system("pause"); break;
		case 9:
		    if(!T) printf("集合不存在，请先进行初始化！\n");
			else if(!T->lchild) printf("该集合为空，请先插入数据！\n");
			else{
				printf("请输入id："); scanf("%d",&id);
			    if(set_remove(T->lchild,id)) printf("删除成功！\n");
			    else printf("删除失败！");
			}
			system("pause"); break;
		case 10:
		    if(!T) printf("集合不存在，请先进行初始化！\n");
			else if(!T->lchild) printf("该集合为空，请先插入数据！\n");
			else{
				printf("该集合为：\n");
			    set_traverse(T->lchild);
			}
			system("pause"); break;
		case 11:
			if(!T) printf("集合不存在，保存失败！\n");
			tree_to_link(L,T);
			system("pause"); break;
	    }	
	}	
} 
