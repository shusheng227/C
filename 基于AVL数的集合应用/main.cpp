#include "Link.h"
void Menu();
void choice(int op,int &a,int &b);
BSTree T=NULL,T1=NULL,T2=NULL,T3=NULL,T4=NULL,T5=NULL;
//T用于二叉树操作，T1,T2用于集合交、并、补，T3用于多集合操作 
//T4用于应用层操作 
BSTree H=NULL,N=NULL;    // H为爱好集，N为姓名集 
LinkList L=NULL,buff=NULL;    //用于多集合操作的链表
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	int op=1;
	int b=0;    //喜好集数量 
	int a=0;    //姓名集数量 
	while(op){
			Menu();
			scanf("%d",&op);getchar();
			if(op==0) break;
			choice(op,a,b);	
	}
	system("cls");
    printf("\n-----------------------------\n\n");
    printf("欢迎下次再使用本系统！\n");
    printf("\n-----------------------------\n");
}

void Menu(){
	system("cls");
	printf("\n                Menu                \n");
	printf("---------------------------------------------\n");
	printf("  1.InitAVL                2.DestroyAVL\n");
	printf("  3.SearchAVL              4.InsertAVL\n");
	printf("  5.DeleteAVL              6.PTraverseAVL(先序)\n");
	printf("  7.TraverseAVL（图形化）\n");
	printf("  8.Load(加载)             9.Save(保存)\n");
	printf("\n--------------------------------------------\n");
	printf(" 10.set_intersection(交)  11.set_union（并）\n");
	printf(" 12.set_diffrence(差)     13.set_subset(子集)\n");
	printf(" 14.set_equal             15.set_operate\n");
	printf(" 16.set_save              17.set_load\n");
	printf("\n--------------------------------------------\n");
	printf(" 19.共同关注              20.共同喜好\n");
	printf(" 21.二度好友              22.信息查询系统（全）\n");
	printf(" 23.随机生成大数据        24.信息查询系统（独）\n");
	printf(" 25.输出爱好集            26.输出所有成员\n");
	printf("\n--------------------------------------------\n");
	printf("  0.Exit(退出)\n");
	printf("-----------------------------------------------\n");
	printf("请输入您的操作[0~26]");
}

void choice(int op,int &a,int &b){
	//实现对各函数的准备工作，输入各个参数，完善输入输出 
	int id=0;
	BSTree Ta=NULL;   //辅助二叉树
	ElemType e; InitElem(e);
	char c='y';
	char filename[20];
	FILE *fp;        //指向文件的指针，用于保存与加载
	LinkList L1=NULL; 
	switch(op){
		case 1:
			if(T) printf("该树已存在，请先进行摧毁！\n");
			else{
				if(InitAVL(T)) printf("初始化成功！\n");
			    else printf("初始化失败！\n");
			}
			system("pause"); break;
		case 2:
			if(!T) printf("二叉树不存在，摧毁失败！\n");
			else{
				if(DestroyAVL(T)) printf("摧毁成功！\n"); 
		    	else printf("摧毁失败！\n");
			}	
			system("pause"); break;
		case 3:
			if(!T) printf("二叉树不存在，请先进行初始化！\n");
			else if(!T->lchild) printf("该二叉树为空，请先插入数据！\n");
			else{
				printf("请输入id：");
			    scanf("%d",&id);getchar();
			    if(SearchAVL(T->lchild,id,Ta)){
			    	printf("查找成功！\n");
			        printf("id为%d的是%s\n",id,Ta->data.name);
			    }
			    else printf("查找失败!\n");
			} 
			system("pause"); break;
		case 4:printf("");
			if(!T) printf("二叉树不存在，请先进行初始化！\n");
			else{
				while(c=='y'){
					printf("请输入id："); scanf("%d",&e.id); getchar(); 
			        if(InsertAVL(T->lchild,e)){ 
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
		case 5:
		    if(!T) printf("二叉树不存在，请先进行初始化！\n");
			else if(!T->lchild) printf("该二叉树为空，请先插入数据！\n");
			else{
				printf("请输入id："); scanf("%d",&id);
			    if(DeleteAVL(T->lchild,id)) printf("删除成功！\n");
			    else printf("删除失败！");
			}
			system("pause"); break;
		case 6:
		    if(!T) printf("二叉树不存在，请先进行初始化！\n");
			else if(!T->lchild) printf("该二叉树为空，请先插入数据！\n");
			else{
			    printf("该二叉树的先序序列为: \n");
			    PTraverseAVL(T->lchild);
			    printf("\n------------------------------------\n");  
			}
			system("pause"); break;
		case 7:
		 	if(!T) printf("二叉树不存在，请先进行初始化！\n");
			else if(!T->lchild) printf("该二叉树为空，请先插入数据！\n");
			else{
				system("cls");  
				printf("图形化表示：\n");
				TraverseAVL(50,2,T->lchild);	
			}
			system("pause"); break;
		case 8:
			//先将T置为空树 
			if(T==NULL) InitAVL(T);
			else {	DestroyAVL(T);   InitAVL(T);}
			//进行加载 
			printf("请输入文件名：");
			scanf("%s",filename);
            if(Load(T->lchild,filename)) printf("文件%s已加载成功！\n",filename);
            else{
            	printf("文件加载失败！\n");
            	DestroyAVL(T);
			}
			system("pause"); break;
		case 9:
			if(!T) printf("二叉树不存在，保存失败！\n");
			else{
				printf("请输入文件名：");
				scanf("%s",filename);
				if ((fp=fopen(filename,"wb"))==NULL){   //文件打开失败 
	                printf("文件打开失败！\n ");
            	}
            	else{
            		if(Save(T->lchild,fp)) printf("已保存至文件%s\n",filename);
            		else printf("文件保存失败！\n");
				} 
			}
			fclose(fp); 
			system("pause"); break;
			
			
		case 10:
			if(!T1||!T2){
				if(!T1) printf("集合1不存在，请先进行加载！\n");
				if(!T2) printf("集合2不存在，请先进行加载！\n");
			}
			else if(!T1->lchild||!T2->lchild){
				if(!T1->lchild) printf("集合1为空集，交集为空集！\n");
				if(!T2->lchild) printf("集合2为空集，交集为空集！\n");
			}
			else{
				system("cls");
				set_destroy(T3); set_init(T3);
				if(set_intersection(T1->lchild,T2->lchild,T3->lchild)){
					printf("集合1："); set_traverse(T1);
				    TraverseAVL(50,2,T1->lchild); 
				    gotoxy(0,19);
			    	printf("集合2："); set_traverse(T2);
			    	TraverseAVL(50,20,T2->lchild); 
					gotoxy(0,34); 
			    	if(!T3->lchild){
			    		printf("集合1与集合2的交集为空集！"); 
			    	}
			    	else{
			    		printf("集合1与集合2的交集为：");  set_traverse(T3);
			    	    TraverseAVL(50,35,T3->lchild);
			    	    printf("\n");
			    	}
			    	c='0';
			    	while(c!='y'&&c!='n'){
				    	printf("是否保存交集？(y/n)：");
				    	scanf("%c",&c);getchar();
			   	    }
				    if(c=='y')  tree_to_link(L,T3->lchild);		
				}
				else printf("求取交集出错！\n");
			}
			system("pause"); break;
		case 11:
			if(!T1||!T2){
				if(!T1) printf("集合1不存在，请先进行加载！\n");
				if(!T2) printf("集合2不存在，请先进行加载！\n");
			}
			else{
				set_destroy(T3); set_init(T3); 
				if(!set_union(T3->lchild,T1->lchild)) printf("求取并集出错!\n"); //分别将T1，T2与Ta合并 
				else if(!set_union(T3->lchild,T2->lchild)) printf("求取并集出错！\n");  
				else{
					system("cls");
					printf("集合1："); set_traverse(T1); 
				    TraverseAVL(50,2,T1->lchild);
				    gotoxy(0,19);
			    	printf("集合2："); set_traverse(T2);
			    	TraverseAVL(50,20,T2->lchild);
					gotoxy(0,34);
				    if(!T3->lchild){
				    	printf("集合1与集合2的并集为空集！\n");
					}
					else{
						printf("集合1与集合2的并集为："); set_traverse(T3); 
			    	    TraverseAVL(50,35,T3->lchild);
			    	    printf("\n");
					}
					c='0';
				    while(c!='y'&&c!='n'){
					    printf("是否保存并集？(y/n)：");
					    scanf("%c",&c);getchar();
				    }
				    if(c=='y')  tree_to_link(L,T3->lchild);	
				}
			}
			system("pause"); break;
		case 12: 
			set_destroy(T3); set_init(T3);
			if(!T1||!T2){
				if(!T1) printf("集合1不存在，请先进行加载！\n");
				if(!T2) printf("集合2不存在，请先进行加载！\n");
			}
			else if(!T1->lchild) printf("集合1为空集，差集为空集！\n");
			else if(!set_union(T3->lchild,T1->lchild)) printf("求取差集出错！\n");
			else{
				if(!set_diffrence(T3->lchild,T2->lchild)) printf("求取差集出错！\n");  //分别将T1，T2与Ta合并 
				else{
					system("cls");
					printf("集合1："); set_traverse(T1);
			    	TraverseAVL(50,2,T1->lchild);
			    	gotoxy(0,19);
			    	printf("集合2："); set_traverse(T2);
			    	TraverseAVL(50,20,T2->lchild);
					gotoxy(0,34);
					if(!T3->lchild){
						printf("\n集合1与集合2的差集为空集！\n");
					}
					else{ 
			    	    printf("\n集合1与集合2的差集为："); set_traverse(T3);
			        	TraverseAVL(50,35,T3->lchild);
			        	printf("\n");
					}
				    c='0';
				    while(c!='y'&&c!='n'){
					    printf("是否保存差集？(y/n)：");
					    scanf("%c",&c);getchar();
				    }
				    if(c=='y')  tree_to_link(L,T3->lchild);
				}
			}
			system("pause"); break;
		case 13:
			if(!T1||!T2){
				if(!T1) printf("集合1不存在，请先进行加载！\n");
				if(!T2) printf("集合2不存在，请先进行加载！\n");
			}
			else if(!T1->lchild&&!T2->lchild) printf("集合1与集合2都为空集，集合2为集合1的子集！\n");
			else if(!T1->lchild) printf("集合1为空集，集合2不是集合1的子集！\n"); 
			else{
				if(set_subset(T1->lchild,T2->lchild)) printf("集合2为集合1的子集！\n");
				else printf("集合2不是集合1的子集！\n");
			}
			system("pause"); break;
		case 14:
			if(!T1||!T2){
				if(!T1) printf("集合1不存在，请先进行加载！\n");
				if(!T2) printf("集合2不存在，请先进行加载！\n");
			}
			else{
				if(set_equal(T1->lchild,T2->lchild)) printf("集合1与集合2成员相同！\n");
				else printf("集合1与集合2不等价！\n");
			}
			system("pause"); break;
		case 15:
			InitAVL(T5);
	        set_menu(L,T5,buff);
	        system("pause"); break;
		case 16:       //集合的保存
		    if(!L) printf("当前无集合！\n");
		    else{
		    	if(save_linklist(L)) printf("集合信息已保存入文件List.dat！\n");
		    	else{
		    		printf("集合保存失败！\n");
				}
			}
			system("pause"); break;
		case 17:       //集合的加载，用于交、并、补运算
	    	if(!L){
	    		printf("还未进入集合操作，请先加载！\n");
			}
			else{
		    	set_destroy(T1); set_init(T1);
		    	set_destroy(T2); set_init(T2);
			printf("当前所有集合id包括：");  TraverseLink(L);
		    printf("请输入要载入集合1的集合id：");
			scanf("%d",&id);
			if(!search_link(L,id,L1)){
				printf("不存在该集合！\n");
				set_destroy(T1); set_destroy(T2);
			}
			else{
				T1->lchild=L1->data.T;
				printf("请输入要载入集合2的集合id：");
				scanf("%d",&id);
			    if(!search_link(L,id,L1)){
				   printf("不存在该集合！\n");
				   set_destroy(T1); set_destroy(T2);
			    }
			    else {
			    	T2->lchild=L1->data.T;
				}
			}
			}
		    
			system("pause"); break;
	        
	        
		case 19:
			if(!T4)	printf("信息未导入,请先导入信息！\n");
	        else if(!T4->lchild)	printf("当前无数据，请先添加数据！\n");
        	else{
        		system("cls");
        		printf("\n---------------共同关注查询系统----------------------\n\n");
        		Common_attention(T4->lchild); 
			}
			system("pause"); break;
		case 20:
			if(!T4)	printf("信息未导入,请先导入信息！\n");
	        else if(!T4->lchild)	printf("当前无数据，请先添加数据！\n");
        	else{
        		system("cls");
        		printf("\n-----------------共同喜好查询系统----------------------\n\n");
        		Common_hobby(T4->lchild); 
			}
			system("pause"); break;
		case 21:
    		if(!T4)	printf("信息未导入,请先导入信息！\n");
	        else if(!T4->lchild)	printf("当前无数据，请先添加数据！\n");
	        else{
	        	system("cls");
	        	printf("\n-----------------二度好友查询系统----------------------\n\n");
	        	printf("请输入id：");
				scanf("%d",&id); getchar();
				if(!second_friend(T4->lchild,id)){
					printf("二度好友求取失败！\n");
				}
			}
			system("pause"); break;
		case 22:
			if(!T4)	printf("信息未导入,请先导入信息！\n");
	        else if(!T4->lchild)	printf("当前无数据，请先添加数据！\n");
	        else{
	        	system("cls");
	            printf("\n-----------------信息查询系统------------------------\n\n");
				operator_tree(T4->lchild,H,a,b);
			}
			system("pause"); break;
		case 23:                         //随机生成数据 
		    if(!T4){
		    	set_destroy(T4);  set_init(T4);
			}
			system("cls");
	        printf("\n-----------------信息随机生成系统------------------------\n\n");
	        if(!H||!N){
	        	set_destroy(H);  H=NULL;
	            set_destroy(N);  N=NULL;
		        printf("信息格式化成功！\n");
			}
	        if(!name_set_input(N,a)){
	        	printf("文件name.txt导入失败！\n");
			}
			else{
				printf("文件name.txt已导入！\n");
	            if(!hobby_set_input(H,b)){
	            	printf("文件hobby.txt导入失败！\n");
			    }
    			else{
    				printf("文件hobby.txt已导入！\n");
    				printf("请输入生成成员数[1-%d]：",a);
			        scanf("%d",&id); getchar();
			        while(id<1||id>a){
				    printf("请重新输入：");
				    scanf("%d",&id); getchar();
			        }
			        if(!Tree_input(T4,N,id)){
				        printf("成员数据生成失败！\n");
				        set_destroy(T4); set_destroy(H); set_destroy(N); 
			        }
			        else{
			        	printf("成员数据成功！\n");
			        	if(!relation_input(T4->lchild,N,H,id,b)){
			        		printf("关系生成失败！\n");
			        		set_destroy(T4); set_destroy(H); set_destroy(N); 
			            }
			        		else{
			        			printf("关系生成成功！\n");
			        			if(!improve_relation(T4->lchild,T4->lchild)){
			        				printf("关系完善失败！\n");
			        				set_destroy(T4); set_destroy(H); set_destroy(N); 
								}
								else{
									printf("关系完善成功！\n");
									printf("大数据随机生成成功！\n");
								}	
							} 
						}
					}
    			} 
		    system("pause"); break;
	    case 24:
	    	if(!T4)	printf("信息未导入,请先导入信息！\n");
	        else if(!T4->lchild)	printf("当前无数据，请先添加数据！\n");
	        else{
	        	system("cls");
	            printf("\n-----------------信息查询系统------------------------\n\n");
				operator_tree2(T4->lchild,H,a,b); 
			}
			system("pause"); break;
		case 25:
			if(!H) printf("爱好集还未加载！\n");
			else{
				printf("hobby：\n");
				PTraverseAVL(H); printf("\n");
			}
			system("pause"); break;
		case 26:
		    if(!T4)	printf("信息未导入,请先导入信息！\n");
	        else if(!T4->lchild)	printf("当前无数据，请先添加数据！\n");
			else{
				printf("成员：\n");
				PTraverseAVL(T4->lchild);
				printf("\n-----------------END------------------------\n");
			}
			system("pause"); break; 
	}
}
