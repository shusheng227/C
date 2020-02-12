#include "Ӧ�ò�.h"

typedef struct Node{
	int    id;
	char   name[10];    //��������
	BSTree T;           //����ͷָ��
}Node;

typedef struct List{ 
    Node   data;
	struct List *prior;
	struct List *next; 
}List,*LinkList;


status TraverseLink(LinkList L){
	//�������L�����м��ϵ�id 
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
	//������L���в�ѯ��������L�д��ڼ���idΪid�Ľ�㣬���ý�㸳ֵ��L1��
	//������TRUE�����򷵻�FALSE
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
	//������e��������L�� 
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
	//��������Ϣ�������ļ�List.dat�� 
	if(!L) return ERROR;
	FILE *fp;
	LinkList q=L;
	if((fp=fopen("List.dat","wb"))==NULL){   //�ļ���ʧ�� 
	    printf("�ļ�List.dat��ʧ�ܣ�\n ");
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
	//������L�ļ��ϱ����뼯�����ļ��� 
	if(!L) return ERROR;
	FILE *fp;
	LinkList q=L;
	if(!save_list(L)) return ERROR;
	while(q){	
		if ((fp=fopen(q->data.name,"wb"))==NULL){   //�ļ���ʧ�� 
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
	//���ļ�List.dat����Ϣ��������L�� 
	L=NULL; 
	FILE *fp;
	LinkList q=NULL;
	if((fp=fopen("List.dat","rb"))==NULL){   //�ļ���ʧ�� 
	    printf("�ļ�List.dat��ʧ�ܣ�\n ");
	    return ERROR;        
    }
    while(!feof(fp)){
    	q=(LinkList)malloc(sizeof(List));
    	if(!q){
    		printf("����ռ����\n");  return ERROR; 
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
	//��������T��������L
	LinkList L1=NULL;
	Node q;
	int a=0;
	char setname[10];
	if(!L) printf("��ǰ�����ļ����޼��ϣ�\n");
	else{
		printf("��ǰ���м���id������");
	    TraverseLink(L);
	}
	printf("�����뼯�ϵ�id��");
	scanf("%d",&a);
	while(search_link(L,a,L1)){
		printf("��id�Ѵ��ڣ����������룺");
		scanf("%d",&a);
	}
	printf("�����뼯������");
	scanf("%s",setname);
	q.id=a; strcpy(q.name,setname);
	q.T=T;
	if(List_insert(L,q)){
		printf("�ü����ѱ����뼯���ļ���\n"); return OK;
	}
	else{
		printf("����ʧ�ܣ�\n"); return ERROR;
	}
}

void set_menu(LinkList &L,BSTree &T,LinkList &buff){
	int i=1;
	int id=0;
	BSTree Ta=NULL;   //����������
	char c='y';
	Node e;
	ElemType a;
	while(i){
		system("cls");
		printf("\n-----------------���ϲ���ϵͳ------------------------\n\n");
		printf("  1.���뼯�ϲ���        2.��һ����         3.��һ����\n");
    	printf("  4.set_init            5.set_destroy      6.set_member\n");
      	printf("  7.set_size            8.set_insert       9.set_remove\n");
    	printf(" 10.set_traverse       11.set_save         0.����\n");
    	printf("\n-----------------------------------------------------\n");
    	printf("��������Ĳ���[0-10]��");
    	scanf("%d",&i); getchar();
        switch(i){
		case 0: break;
		case 1:
			if(L){
				printf("�ѽ��뼯�ϲ�����\n");
				system("pause"); break;
			}
			if(!load_linklist(L)){
				printf("���ؼ���ʧ�ܣ�\n");
			}
			else{
				printf("���ϼ��سɹ���\n");
				buff=L;
			    T->lchild=L->data.T;
			    printf("��ʼ���ϲ�������ǰΪ����%d\n",L->data.id);
			}
			system("pause"); break;
		case 2:
			if(buff->prior==NULL){
				printf("������һ�����ϣ�\n");
			}
			else{
				buff=buff->prior;
				T->lchild=buff->data.T;
				printf("���ɼ���%d�л�������%d��\n",buff->next->data.id,buff->data.id);
			}
			system("pause"); break;
		case 3:
			if(buff->next==NULL){
				printf("�������һ�����ϣ�\n");
			}
			else{
				buff=buff->next;
				T->lchild=buff->data.T;
				printf("���ɼ���%d�л�������%d��\n",buff->prior->data.id,buff->data.id);
			}
			system("pause"); break;
		case 4:
			if(T) printf("�ü����Ѵ��ڣ����Ƚ��дݻ٣�\n");
			else{
				if(set_init(T)) printf("��ʼ���ɹ���\n");
			    else printf("��ʼ��ʧ�ܣ�\n");
			}
			system("pause"); break;
		case 5:
			if(!T) printf("���ϲ����ڣ��ݻ�ʧ�ܣ�\n");
			else{
				if(set_destroy(T)) printf("�ݻٳɹ���\n"); 
		    	else printf("�ݻ�ʧ�ܣ�\n");
			}	
			system("pause"); break;
		case 6:
			if(!T) printf("���ϲ����ڣ����Ƚ��г�ʼ����\n");
			else if(!T->lchild) printf("�ü���Ϊ�գ����Ȳ������ݣ�\n");
			else{
				printf("������id��");
			    scanf("%d",&id);getchar();
			    if(set_member(T->lchild,id,Ta)){
			    	printf("���ҳɹ���\n");
			        printf("idΪ%d����%s\n",id,Ta->data.name);
			    }
			    else printf("����ʧ��!\n");
			} 
			system("pause"); break;
		case 7:
			if(!T) printf("���ϲ����ڣ����Ƚ��г�ʼ����\n");
			else if(!T->lchild) printf("�ü���Ϊ�գ����Ȳ������ݣ�\n");
			else{
				printf("��ǰ����Ϊ%d�����Ա����Ϊ%d!\n",buff->data.id,set_size(T->lchild));
			}
			system("pause"); break;
		case 8:
			c='y';
			if(!T) printf("���ϲ����ڣ����Ƚ��г�ʼ����\n");
			else{
				while(c=='y'){
					printf("������id��"); scanf("%d",&a.id); getchar(); 
			        printf("������������"); scanf("%s",&a.name); getchar();
			        if(set_insert(T->lchild,a)){ 
			    	    printf("����ɹ���\n");
			    	    height(T->lchild,1);
				    }
			        else printf("����ʧ�ܣ�\n");
			        printf("�Ƿ����('y'or'n')����");
					scanf("%c",&c); getchar();
					if(c!='y'&&c!='n'){
						printf("���������룺");
						scanf("%c",&c); getchar();
					}
				}	
			}
			system("pause"); break;
		case 9:
		    if(!T) printf("���ϲ����ڣ����Ƚ��г�ʼ����\n");
			else if(!T->lchild) printf("�ü���Ϊ�գ����Ȳ������ݣ�\n");
			else{
				printf("������id��"); scanf("%d",&id);
			    if(set_remove(T->lchild,id)) printf("ɾ���ɹ���\n");
			    else printf("ɾ��ʧ�ܣ�");
			}
			system("pause"); break;
		case 10:
		    if(!T) printf("���ϲ����ڣ����Ƚ��г�ʼ����\n");
			else if(!T->lchild) printf("�ü���Ϊ�գ����Ȳ������ݣ�\n");
			else{
				printf("�ü���Ϊ��\n");
			    set_traverse(T->lchild);
			}
			system("pause"); break;
		case 11:
			if(!T) printf("���ϲ����ڣ�����ʧ�ܣ�\n");
			tree_to_link(L,T);
			system("pause"); break;
	    }	
	}	
} 
