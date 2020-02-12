#include "Link.h"
void Menu();
void choice(int op,int &a,int &b);
BSTree T=NULL,T1=NULL,T2=NULL,T3=NULL,T4=NULL,T5=NULL;
//T���ڶ�����������T1,T2���ڼ��Ͻ�����������T3���ڶ༯�ϲ��� 
//T4����Ӧ�ò���� 
BSTree H=NULL,N=NULL;    // HΪ���ü���NΪ������ 
LinkList L=NULL,buff=NULL;    //���ڶ༯�ϲ���������
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	int op=1;
	int b=0;    //ϲ�ü����� 
	int a=0;    //���������� 
	while(op){
			Menu();
			scanf("%d",&op);getchar();
			if(op==0) break;
			choice(op,a,b);	
	}
	system("cls");
    printf("\n-----------------------------\n\n");
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    printf("\n-----------------------------\n");
}

void Menu(){
	system("cls");
	printf("\n                Menu                \n");
	printf("---------------------------------------------\n");
	printf("  1.InitAVL                2.DestroyAVL\n");
	printf("  3.SearchAVL              4.InsertAVL\n");
	printf("  5.DeleteAVL              6.PTraverseAVL(����)\n");
	printf("  7.TraverseAVL��ͼ�λ���\n");
	printf("  8.Load(����)             9.Save(����)\n");
	printf("\n--------------------------------------------\n");
	printf(" 10.set_intersection(��)  11.set_union������\n");
	printf(" 12.set_diffrence(��)     13.set_subset(�Ӽ�)\n");
	printf(" 14.set_equal             15.set_operate\n");
	printf(" 16.set_save              17.set_load\n");
	printf("\n--------------------------------------------\n");
	printf(" 19.��ͬ��ע              20.��ͬϲ��\n");
	printf(" 21.���Ⱥ���              22.��Ϣ��ѯϵͳ��ȫ��\n");
	printf(" 23.������ɴ�����        24.��Ϣ��ѯϵͳ������\n");
	printf(" 25.������ü�            26.������г�Ա\n");
	printf("\n--------------------------------------------\n");
	printf("  0.Exit(�˳�)\n");
	printf("-----------------------------------------------\n");
	printf("���������Ĳ���[0~26]");
}

void choice(int op,int &a,int &b){
	//ʵ�ֶԸ�������׼�������������������������������� 
	int id=0;
	BSTree Ta=NULL;   //����������
	ElemType e; InitElem(e);
	char c='y';
	char filename[20];
	FILE *fp;        //ָ���ļ���ָ�룬���ڱ��������
	LinkList L1=NULL; 
	switch(op){
		case 1:
			if(T) printf("�����Ѵ��ڣ����Ƚ��дݻ٣�\n");
			else{
				if(InitAVL(T)) printf("��ʼ���ɹ���\n");
			    else printf("��ʼ��ʧ�ܣ�\n");
			}
			system("pause"); break;
		case 2:
			if(!T) printf("�����������ڣ��ݻ�ʧ�ܣ�\n");
			else{
				if(DestroyAVL(T)) printf("�ݻٳɹ���\n"); 
		    	else printf("�ݻ�ʧ�ܣ�\n");
			}	
			system("pause"); break;
		case 3:
			if(!T) printf("�����������ڣ����Ƚ��г�ʼ����\n");
			else if(!T->lchild) printf("�ö�����Ϊ�գ����Ȳ������ݣ�\n");
			else{
				printf("������id��");
			    scanf("%d",&id);getchar();
			    if(SearchAVL(T->lchild,id,Ta)){
			    	printf("���ҳɹ���\n");
			        printf("idΪ%d����%s\n",id,Ta->data.name);
			    }
			    else printf("����ʧ��!\n");
			} 
			system("pause"); break;
		case 4:printf("");
			if(!T) printf("�����������ڣ����Ƚ��г�ʼ����\n");
			else{
				while(c=='y'){
					printf("������id��"); scanf("%d",&e.id); getchar(); 
			        if(InsertAVL(T->lchild,e)){ 
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
		case 5:
		    if(!T) printf("�����������ڣ����Ƚ��г�ʼ����\n");
			else if(!T->lchild) printf("�ö�����Ϊ�գ����Ȳ������ݣ�\n");
			else{
				printf("������id��"); scanf("%d",&id);
			    if(DeleteAVL(T->lchild,id)) printf("ɾ���ɹ���\n");
			    else printf("ɾ��ʧ�ܣ�");
			}
			system("pause"); break;
		case 6:
		    if(!T) printf("�����������ڣ����Ƚ��г�ʼ����\n");
			else if(!T->lchild) printf("�ö�����Ϊ�գ����Ȳ������ݣ�\n");
			else{
			    printf("�ö���������������Ϊ: \n");
			    PTraverseAVL(T->lchild);
			    printf("\n------------------------------------\n");  
			}
			system("pause"); break;
		case 7:
		 	if(!T) printf("�����������ڣ����Ƚ��г�ʼ����\n");
			else if(!T->lchild) printf("�ö�����Ϊ�գ����Ȳ������ݣ�\n");
			else{
				system("cls");  
				printf("ͼ�λ���ʾ��\n");
				TraverseAVL(50,2,T->lchild);	
			}
			system("pause"); break;
		case 8:
			//�Ƚ�T��Ϊ���� 
			if(T==NULL) InitAVL(T);
			else {	DestroyAVL(T);   InitAVL(T);}
			//���м��� 
			printf("�������ļ�����");
			scanf("%s",filename);
            if(Load(T->lchild,filename)) printf("�ļ�%s�Ѽ��سɹ���\n",filename);
            else{
            	printf("�ļ�����ʧ�ܣ�\n");
            	DestroyAVL(T);
			}
			system("pause"); break;
		case 9:
			if(!T) printf("�����������ڣ�����ʧ�ܣ�\n");
			else{
				printf("�������ļ�����");
				scanf("%s",filename);
				if ((fp=fopen(filename,"wb"))==NULL){   //�ļ���ʧ�� 
	                printf("�ļ���ʧ�ܣ�\n ");
            	}
            	else{
            		if(Save(T->lchild,fp)) printf("�ѱ������ļ�%s\n",filename);
            		else printf("�ļ�����ʧ�ܣ�\n");
				} 
			}
			fclose(fp); 
			system("pause"); break;
			
			
		case 10:
			if(!T1||!T2){
				if(!T1) printf("����1�����ڣ����Ƚ��м��أ�\n");
				if(!T2) printf("����2�����ڣ����Ƚ��м��أ�\n");
			}
			else if(!T1->lchild||!T2->lchild){
				if(!T1->lchild) printf("����1Ϊ�ռ�������Ϊ�ռ���\n");
				if(!T2->lchild) printf("����2Ϊ�ռ�������Ϊ�ռ���\n");
			}
			else{
				system("cls");
				set_destroy(T3); set_init(T3);
				if(set_intersection(T1->lchild,T2->lchild,T3->lchild)){
					printf("����1��"); set_traverse(T1);
				    TraverseAVL(50,2,T1->lchild); 
				    gotoxy(0,19);
			    	printf("����2��"); set_traverse(T2);
			    	TraverseAVL(50,20,T2->lchild); 
					gotoxy(0,34); 
			    	if(!T3->lchild){
			    		printf("����1�뼯��2�Ľ���Ϊ�ռ���"); 
			    	}
			    	else{
			    		printf("����1�뼯��2�Ľ���Ϊ��");  set_traverse(T3);
			    	    TraverseAVL(50,35,T3->lchild);
			    	    printf("\n");
			    	}
			    	c='0';
			    	while(c!='y'&&c!='n'){
				    	printf("�Ƿ񱣴潻����(y/n)��");
				    	scanf("%c",&c);getchar();
			   	    }
				    if(c=='y')  tree_to_link(L,T3->lchild);		
				}
				else printf("��ȡ��������\n");
			}
			system("pause"); break;
		case 11:
			if(!T1||!T2){
				if(!T1) printf("����1�����ڣ����Ƚ��м��أ�\n");
				if(!T2) printf("����2�����ڣ����Ƚ��м��أ�\n");
			}
			else{
				set_destroy(T3); set_init(T3); 
				if(!set_union(T3->lchild,T1->lchild)) printf("��ȡ��������!\n"); //�ֱ�T1��T2��Ta�ϲ� 
				else if(!set_union(T3->lchild,T2->lchild)) printf("��ȡ��������\n");  
				else{
					system("cls");
					printf("����1��"); set_traverse(T1); 
				    TraverseAVL(50,2,T1->lchild);
				    gotoxy(0,19);
			    	printf("����2��"); set_traverse(T2);
			    	TraverseAVL(50,20,T2->lchild);
					gotoxy(0,34);
				    if(!T3->lchild){
				    	printf("����1�뼯��2�Ĳ���Ϊ�ռ���\n");
					}
					else{
						printf("����1�뼯��2�Ĳ���Ϊ��"); set_traverse(T3); 
			    	    TraverseAVL(50,35,T3->lchild);
			    	    printf("\n");
					}
					c='0';
				    while(c!='y'&&c!='n'){
					    printf("�Ƿ񱣴沢����(y/n)��");
					    scanf("%c",&c);getchar();
				    }
				    if(c=='y')  tree_to_link(L,T3->lchild);	
				}
			}
			system("pause"); break;
		case 12: 
			set_destroy(T3); set_init(T3);
			if(!T1||!T2){
				if(!T1) printf("����1�����ڣ����Ƚ��м��أ�\n");
				if(!T2) printf("����2�����ڣ����Ƚ��м��أ�\n");
			}
			else if(!T1->lchild) printf("����1Ϊ�ռ����Ϊ�ռ���\n");
			else if(!set_union(T3->lchild,T1->lchild)) printf("��ȡ�����\n");
			else{
				if(!set_diffrence(T3->lchild,T2->lchild)) printf("��ȡ�����\n");  //�ֱ�T1��T2��Ta�ϲ� 
				else{
					system("cls");
					printf("����1��"); set_traverse(T1);
			    	TraverseAVL(50,2,T1->lchild);
			    	gotoxy(0,19);
			    	printf("����2��"); set_traverse(T2);
			    	TraverseAVL(50,20,T2->lchild);
					gotoxy(0,34);
					if(!T3->lchild){
						printf("\n����1�뼯��2�ĲΪ�ռ���\n");
					}
					else{ 
			    	    printf("\n����1�뼯��2�ĲΪ��"); set_traverse(T3);
			        	TraverseAVL(50,35,T3->lchild);
			        	printf("\n");
					}
				    c='0';
				    while(c!='y'&&c!='n'){
					    printf("�Ƿ񱣴���(y/n)��");
					    scanf("%c",&c);getchar();
				    }
				    if(c=='y')  tree_to_link(L,T3->lchild);
				}
			}
			system("pause"); break;
		case 13:
			if(!T1||!T2){
				if(!T1) printf("����1�����ڣ����Ƚ��м��أ�\n");
				if(!T2) printf("����2�����ڣ����Ƚ��м��أ�\n");
			}
			else if(!T1->lchild&&!T2->lchild) printf("����1�뼯��2��Ϊ�ռ�������2Ϊ����1���Ӽ���\n");
			else if(!T1->lchild) printf("����1Ϊ�ռ�������2���Ǽ���1���Ӽ���\n"); 
			else{
				if(set_subset(T1->lchild,T2->lchild)) printf("����2Ϊ����1���Ӽ���\n");
				else printf("����2���Ǽ���1���Ӽ���\n");
			}
			system("pause"); break;
		case 14:
			if(!T1||!T2){
				if(!T1) printf("����1�����ڣ����Ƚ��м��أ�\n");
				if(!T2) printf("����2�����ڣ����Ƚ��м��أ�\n");
			}
			else{
				if(set_equal(T1->lchild,T2->lchild)) printf("����1�뼯��2��Ա��ͬ��\n");
				else printf("����1�뼯��2���ȼۣ�\n");
			}
			system("pause"); break;
		case 15:
			InitAVL(T5);
	        set_menu(L,T5,buff);
	        system("pause"); break;
		case 16:       //���ϵı���
		    if(!L) printf("��ǰ�޼��ϣ�\n");
		    else{
		    	if(save_linklist(L)) printf("������Ϣ�ѱ������ļ�List.dat��\n");
		    	else{
		    		printf("���ϱ���ʧ�ܣ�\n");
				}
			}
			system("pause"); break;
		case 17:       //���ϵļ��أ����ڽ�������������
	    	if(!L){
	    		printf("��δ���뼯�ϲ��������ȼ��أ�\n");
			}
			else{
		    	set_destroy(T1); set_init(T1);
		    	set_destroy(T2); set_init(T2);
			printf("��ǰ���м���id������");  TraverseLink(L);
		    printf("������Ҫ���뼯��1�ļ���id��");
			scanf("%d",&id);
			if(!search_link(L,id,L1)){
				printf("�����ڸü��ϣ�\n");
				set_destroy(T1); set_destroy(T2);
			}
			else{
				T1->lchild=L1->data.T;
				printf("������Ҫ���뼯��2�ļ���id��");
				scanf("%d",&id);
			    if(!search_link(L,id,L1)){
				   printf("�����ڸü��ϣ�\n");
				   set_destroy(T1); set_destroy(T2);
			    }
			    else {
			    	T2->lchild=L1->data.T;
				}
			}
			}
		    
			system("pause"); break;
	        
	        
		case 19:
			if(!T4)	printf("��Ϣδ����,���ȵ�����Ϣ��\n");
	        else if(!T4->lchild)	printf("��ǰ�����ݣ�����������ݣ�\n");
        	else{
        		system("cls");
        		printf("\n---------------��ͬ��ע��ѯϵͳ----------------------\n\n");
        		Common_attention(T4->lchild); 
			}
			system("pause"); break;
		case 20:
			if(!T4)	printf("��Ϣδ����,���ȵ�����Ϣ��\n");
	        else if(!T4->lchild)	printf("��ǰ�����ݣ�����������ݣ�\n");
        	else{
        		system("cls");
        		printf("\n-----------------��ͬϲ�ò�ѯϵͳ----------------------\n\n");
        		Common_hobby(T4->lchild); 
			}
			system("pause"); break;
		case 21:
    		if(!T4)	printf("��Ϣδ����,���ȵ�����Ϣ��\n");
	        else if(!T4->lchild)	printf("��ǰ�����ݣ�����������ݣ�\n");
	        else{
	        	system("cls");
	        	printf("\n-----------------���Ⱥ��Ѳ�ѯϵͳ----------------------\n\n");
	        	printf("������id��");
				scanf("%d",&id); getchar();
				if(!second_friend(T4->lchild,id)){
					printf("���Ⱥ�����ȡʧ�ܣ�\n");
				}
			}
			system("pause"); break;
		case 22:
			if(!T4)	printf("��Ϣδ����,���ȵ�����Ϣ��\n");
	        else if(!T4->lchild)	printf("��ǰ�����ݣ�����������ݣ�\n");
	        else{
	        	system("cls");
	            printf("\n-----------------��Ϣ��ѯϵͳ------------------------\n\n");
				operator_tree(T4->lchild,H,a,b);
			}
			system("pause"); break;
		case 23:                         //����������� 
		    if(!T4){
		    	set_destroy(T4);  set_init(T4);
			}
			system("cls");
	        printf("\n-----------------��Ϣ�������ϵͳ------------------------\n\n");
	        if(!H||!N){
	        	set_destroy(H);  H=NULL;
	            set_destroy(N);  N=NULL;
		        printf("��Ϣ��ʽ���ɹ���\n");
			}
	        if(!name_set_input(N,a)){
	        	printf("�ļ�name.txt����ʧ�ܣ�\n");
			}
			else{
				printf("�ļ�name.txt�ѵ��룡\n");
	            if(!hobby_set_input(H,b)){
	            	printf("�ļ�hobby.txt����ʧ�ܣ�\n");
			    }
    			else{
    				printf("�ļ�hobby.txt�ѵ��룡\n");
    				printf("���������ɳ�Ա��[1-%d]��",a);
			        scanf("%d",&id); getchar();
			        while(id<1||id>a){
				    printf("���������룺");
				    scanf("%d",&id); getchar();
			        }
			        if(!Tree_input(T4,N,id)){
				        printf("��Ա��������ʧ�ܣ�\n");
				        set_destroy(T4); set_destroy(H); set_destroy(N); 
			        }
			        else{
			        	printf("��Ա���ݳɹ���\n");
			        	if(!relation_input(T4->lchild,N,H,id,b)){
			        		printf("��ϵ����ʧ�ܣ�\n");
			        		set_destroy(T4); set_destroy(H); set_destroy(N); 
			            }
			        		else{
			        			printf("��ϵ���ɳɹ���\n");
			        			if(!improve_relation(T4->lchild,T4->lchild)){
			        				printf("��ϵ����ʧ�ܣ�\n");
			        				set_destroy(T4); set_destroy(H); set_destroy(N); 
								}
								else{
									printf("��ϵ���Ƴɹ���\n");
									printf("������������ɳɹ���\n");
								}	
							} 
						}
					}
    			} 
		    system("pause"); break;
	    case 24:
	    	if(!T4)	printf("��Ϣδ����,���ȵ�����Ϣ��\n");
	        else if(!T4->lchild)	printf("��ǰ�����ݣ�����������ݣ�\n");
	        else{
	        	system("cls");
	            printf("\n-----------------��Ϣ��ѯϵͳ------------------------\n\n");
				operator_tree2(T4->lchild,H,a,b); 
			}
			system("pause"); break;
		case 25:
			if(!H) printf("���ü���δ���أ�\n");
			else{
				printf("hobby��\n");
				PTraverseAVL(H); printf("\n");
			}
			system("pause"); break;
		case 26:
		    if(!T4)	printf("��Ϣδ����,���ȵ�����Ϣ��\n");
	        else if(!T4->lchild)	printf("��ǰ�����ݣ�����������ݣ�\n");
			else{
				printf("��Ա��\n");
				PTraverseAVL(T4->lchild);
				printf("\n-----------------END------------------------\n");
			}
			system("pause"); break; 
	}
}
