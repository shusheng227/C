#include "ADT.h"


//共同关注、共同好友 
status common(BSTree T1,BSTree T2,BSTree &T){
	//求取数据项T1与T2的共同成员 
	if(!set_intersection(T1,T2,T)) return ERROR;
	return OK;
}

//二度好友 
status search_friend(BSTree T,BSTree Ta,BSTree &Tb){
	//二度好友的辅助函数，二叉树Ta为T中某成员的朋友集
	//将朋友集中成员的朋友信息存入集合Tb
	BSTree Tc=NULL;          //指向各朋友的指针
	if(!Ta) return OK;
	if(!set_member(T,Ta->data.id,Tc)) return ERROR;
	//通过并集操作将朋友的朋友集赋值入二叉树Tb
	if(!set_union(Tb,Tc->data.friends)) return ERROR;
	if(!search_friend(T,Ta->lchild,Tb)) return ERROR;
	return OK;
}

status second_friend(BSTree T,int id){
	//将二叉树中id为id的成员的二度好友 
	if(!T) return ERROR;
	BSTree Ta=NULL;     //一度朋友集 
	BSTree Tb=NULL;     //二度朋友集 
	if(!set_member(T,id,Ta)){
		printf("此人不存在！\n");
		return ERROR;
	}
	if(!(Ta->data.friends)){
		printf("id为%d的是%s,该成员无朋友！\n",Ta->data.id,Ta->data.name);
		return ERROR;
	}
	if(!search_friend(T,Ta->data.friends,Tb)) return ERROR;
	if(!Tb){
		printf("id为%d的是%s,该成员无二度好友！\n",Ta->data.id,Ta->data.name);	
	}
	else{
		printf("id为%d的是%s,%s的二度好友为：\n",Ta->data.id,Ta->data.name,Ta->data.name);
    	PTraverseAVL(Tb);   printf("\n"); 
	}
	return OK;
}


status Common_attention(BSTree &T){
	//共同关注查找系统
	int id=0;
	BSTree Ta=NULL,Tb=NULL,Tc=NULL;      //辅助函数 
	printf("请输入第一个人的id："); 
	scanf("%d",&id); getchar();
	if(!set_member(T,id,Ta)){
		printf("此人不存在！\n");
		return ERROR;
	}
	printf("请输入第二个人的id：");
	scanf("%d",&id); getchar();
	if(!set_member(T,id,Tb)){
		printf("此人不存在！\n");
		return ERROR;
	}
	if(!common(Ta->data.attention,Tb->data.attention,Tc)){
		printf("求取共同关注失败！\n"); return ERROR;
	}
	if(!(Ta->data.attention)){
		printf("id为%d的是%s,其无关注人！\n",Ta->data.id,Ta->data.name);
		return ERROR; 
	}
	if(!(Tb->data.attention)){
		printf("id为%d的是%s,其无关注人！\n",Tb->data.id,Tb->data.name);
		return ERROR;
	}
	printf("id为%d的是%s,其关注的人有：\n",Ta->data.id,Ta->data.name);
	PTraverseAVL(Ta->data.attention); printf("\n");
	printf("id为%d的是%s,其关注的人有：\n",Tb->data.id,Tb->data.name);
	PTraverseAVL(Tb->data.attention); printf("\n");
	if(!Tc){
		printf("%s与%s无共同关注！\n",Ta->data.name,Tb->data.name);
		return OK;
	}
	else{
		printf("共同关注有：\n");
	    PTraverseAVL(Tc); printf("\n");
	}
	return OK;
}

status Common_hobby(BSTree &T){
	//共同喜好查找系统
	int id=0;
	BSTree Ta=NULL,Tb=NULL,Tc=NULL;      //辅助函数 
	printf("请输入第一个人的id："); 
	scanf("%d",&id); getchar();
	if(!set_member(T,id,Ta)){
		printf("此人不存在！\n");
		return ERROR;
	}
	printf("请输入第二个人的id：");
	scanf("%d",&id); getchar();
	if(!set_member(T,id,Tb)){
		printf("此人不存在！\n");
		return ERROR;
	}
	if(!common(Ta->data.hobby,Tb->data.hobby,Tc)){
		printf("求取共同喜好失败！\n"); return ERROR;
	}
	if(!(Ta->data.hobby)){
		printf("id为%d的是%s,其无喜好！\n",Ta->data.id,Ta->data.name);
		return ERROR; 
	}
	if(!(Tb->data.hobby)){
		printf("id为%d的是%s,其无喜好！\n",Tb->data.id,Tb->data.name);
		return ERROR;
	}
	printf("id为%d的是%s,其喜好有：\n",Ta->data.id,Ta->data.name);
	PTraverseAVL(Ta->data.hobby); printf("\n");
	printf("id为%d的是%s,其喜好有：\n",Tb->data.id,Tb->data.name);
	PTraverseAVL(Tb->data.hobby); printf("\n");
	if(!Tc){
		printf("%s与%s无共同喜好！\n",Ta->data.name,Tb->data.name);
		return OK;
	}
	else{
		printf("共同喜好有：\n");
	    PTraverseAVL(Tc); printf("\n");
	}
	return OK;
}

status hobby_set_input(BSTree &H,int &n){
	//读取文件hobby.txt,将其加载入二叉树H,
	//n记录读取数量 
    FILE *fp;
    ElemType e; InitElem(e);
    int number=0;
    if(H){           //清空二叉树 
    	set_destroy(H); H=NULL;
	}
    if((fp=fopen("hobby.txt","r"))==NULL){
        printf("打开文件hobby.txt失败!\n");
        return ERROR;
    }
    while(fgets(e.name,5,fp)){
    	e.id=number++;
        e.attention=NULL;
        e.fans=NULL;
        e.friends=NULL;
        e.hobby=NULL;
        if(!set_insert(H,e)) return ERROR;
	}  
    if(!feof(fp)){
    	fclose(fp);   return ERROR;
	}
    n=number;
    fclose(fp);
    height(H,1);
    return OK;
}

status name_set_input(BSTree &N,int &n){
	//读取文件name.txt,将其加载入二叉树N 
    FILE *fp;
    ElemType e;
    int number=0;
    if(N){           //清空二叉树 
    	set_destroy(N); N=NULL;
	}
    if((fp=fopen("name.txt","r"))==NULL){
        printf("打开文件name.txt失败!\n");
        return ERROR;
    }
    while(fgets(e.name,7,fp)){
    	e.id=number++;
        e.attention=NULL;
        e.fans=NULL;
        e.friends=NULL;
        e.hobby=NULL;
        if(!set_insert(N,e)) return ERROR;
	}  
    if(!feof(fp)){
    	fclose(fp);   return ERROR;
	}
    n=number;
    fclose(fp);
    height(N,1);
    return OK;
}

status name_input(BSTree &T,int gross,int max,int min,BSTree N){
	//随机生成一棵二叉树，该二叉树结点id不超过gross，结点数为min-min+max 
    int j=0;
    BSTree Ta=NULL;
    for(int i=0;i<=rand()%max+min;){
        j=rand()%gross;
        if(!set_member(N,j,Ta))  return ERROR;
        if(set_insert(T,Ta->data)) i++;
    }
    return OK;
}

status relation_input(BSTree &T,BSTree N,BSTree H,int a,int b){
	//随机生成关系，N为姓名集，H为喜好集
	//a为姓名集的最大数,b为喜好集的最大数 
	if(!T) return OK;
    if(!name_input(T->data.friends,a,5,3,N)) return ERROR;
    if(!name_input(T->data.attention,a,5,1,N)) return ERROR;
    if(!name_input(T->data.hobby,b,3,1,H)) return ERROR;
    if(!name_input(T->data.fans,a,5,1,N)) return ERROR;
    if(!relation_input(T->lchild,N,H,a,b)) return ERROR;
    if(!relation_input(T->rchild,N,H,a,b)) return ERROR;
    return OK;
}

status Tree_input(BSTree &T,BSTree N,int b){
	//随机生成一个结点数量为b的成员信息 
	set_destroy(T); set_init(T);
    int j=0;
    BSTree Ta=NULL;
    for(int i=0;i<b;){
        j=rand()%b;
        if(!set_member(N,j,Ta))  return ERROR;
        if(set_insert(T->lchild,Ta->data)) i++;
    }
    return OK;
}

status improve_friend(BSTree &T,BSTree Ta,ElemType e){
	//完善成员的朋友集信息,Ta为某成员朋友集,e为该成员信息 
	BSTree Tb=NULL;
	if(!Ta) return OK;
	else if(set_member(T,Ta->data.id,Tb)){
		set_insert(Tb->data.friends,e);
	}
	else return ERROR;
	if(!improve_friend(T,Ta->lchild,e)) return ERROR;
	if(!improve_friend(T,Ta->lchild,e)) return ERROR;
	return OK;
}

status improve_attention(BSTree &T,BSTree Ta,ElemType e){
	//完善成员的关注集信息,Ta为某成员粉丝集,e为该成员信息 
	BSTree Tb=NULL;
	if(!Ta) return OK;
	else if(set_member(T,Ta->data.id,Tb)){
		set_insert(Tb->data.attention,e);
	}
	else return ERROR;
	if(!improve_attention(T,Ta->lchild,e)) return ERROR;
	if(!improve_attention(T,Ta->lchild,e)) return ERROR;
	return OK;
}

status improve_fans(BSTree &T,BSTree Ta,ElemType e){
	//完善成员的粉丝集信息,Ta为某成员关注集,e为该成员信息 
	BSTree Tb=NULL;
	if(!Ta) return OK;
	else if(set_member(T,Ta->data.id,Tb)){
		set_insert(Tb->data.fans,e);
	}
	else return ERROR;
	if(!improve_fans(T,Ta->lchild,e)) return ERROR;
	if(!improve_fans(T,Ta->lchild,e)) return ERROR;
	return OK;
}

status search_relation(BSTree &T){
	//检查T的关系集中是否有自己，如果有，删除
	BSTree Ta=NULL;
	if(!T) return OK;
	//检查朋友集 
	if(set_member(T->data.friends,T->data.id,Ta)){
		if(!set_remove(T->data.friends,T->data.id)) return ERROR;
	}
	//检查粉丝集
	if(set_member(T->data.fans,T->data.id,Ta)){
		if(!set_remove(T->data.fans,T->data.id)) return ERROR;
	}
	//检查关注集
	if(set_member(T->data.attention,T->data.id,Ta)){
		if(!set_remove(T->data.attention,T->data.id)) return ERROR;
	}
	return OK;
}

status improve_relation(BSTree &T,BSTree &T1){
	//完善成员关系集，使朋友互相存在，使成员的粉丝的关注中有该成员
	//防止成员的朋友集、粉丝集、关注集中有本人
	if(!T1) return OK;
	if(!improve_friend(T,T1->data.friends,T1->data)) return ERROR;
	if(!improve_attention(T,T1->data.fans,T1->data)) return ERROR;
	if(!improve_fans(T,T1->data.attention,T1->data)) return ERROR;
	if(!search_relation(T1)) return ERROR;
	if(!improve_relation(T,T1->lchild)) return ERROR;
	if(!improve_relation(T,T1->rchild)) return ERROR;
	return OK;
}

status operator_tree(BSTree &T,BSTree H,int a,int b){
	//对应用层中数据进行查找，随后进行删除、增加、修改等操作
	BSTree Ta=NULL,Tb=NULL;
	int id=0, i=0,j=0;
	printf("请输入要查找的id：");
	scanf("%d",&id); getchar();
	if(!set_member(T,id,Ta)){
		printf("查找失败！\n"); return ERROR;
	}
	else{
		printf("查找成功,具体信息如下：\n");
		printf("  id：");    printf("%d\n",Ta->data.id);
		printf("name：");    printf("%s\n",Ta->data.name);
		printf("friend：\n"); PTraverseAVL(Ta->data.friends);  printf("\n");
		printf("fans：\n");   PTraverseAVL(Ta->data.fans);   printf("\n");
		printf("attention：\n");  PTraverseAVL(Ta->data.attention);   printf("\n");
		printf("hobby：\n");  PTraverseAVL(Ta->data.hobby);    printf("\n");
		printf("-----------------------------------------------------\n");
		printf("1.name            2.friend       3.fans\n"); 
		printf("4.attention       5.hobby        0.返回\n");
		printf("-----------------------------------------------------\n");
		printf("请输入要进行操作的内容的序号[0-5]：");  scanf("%d",&j); getchar();
		while(j<0||j>5){
			printf("请重新输入：");
			scanf("%d",&j); getchar();
		}
		switch(j){
			case 0: break;
			case 1:
				printf("请输入新的姓名：");
				scanf("%s",&Ta->data.name);
				printf("修改成功！\n");
				break;
			case 2:             //好友集操作 
				printf("1.增加     2.删除     0.返回\n");
				printf("请输入要进行的操作[0-3]：");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("请重新输入：");
			        scanf("%d",&i); getchar();
		        }
		        
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("请输入要插入的好友的id：");
		            	scanf("%d",&id);
		            	if(set_member(T,id,Tb)){        //好友信息存在 
		            		if(set_insert(Ta->data.friends,Tb->data)){
		            			if(set_insert(Tb->data.friends,Ta->data)) 
		            			    printf("插入成功！\n"); break;
				    		}
				    		printf("插入失败！\n"); break;
				    	}
				    	else{              //好友信息不存在 
				    		printf("该好友不存在，插入失败！\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("请输入要删除的好友的id：");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.friends,id,Tb)){        //好友信息存在 
		            		if(set_remove(Ta->data.friends,id)){
		            			if(set_member(T,id,Tb)){
		            				if(set_remove(Tb->data.friends,Ta->data.id))
		            				printf("已删除好友%s！\n",Tb->data.name); break;
								}	
				    		}
				    		printf("删除失败！\n"); break;
				    	}
				    	else{              //好友信息不存在 
				    		printf("该好友不存在，删除失败！\n");
				    	}
				    	break;
				}
				break;
			case 3:             //粉丝集操作
			    printf("1.增加     2.删除     0.返回\n");
				printf("请输入要进行的操作[0-3]：");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("请重新输入：");
			        scanf("%d",&i); getchar();
		        }
		        
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("请输入要插入的粉丝的id：");
		            	scanf("%d",&id);
		            	if(set_member(T,id,Tb)){        //好友信息存在 
		            		if(set_insert(Ta->data.fans,Tb->data)){
		            			if(set_insert(Tb->data.attention,Ta->data))
		            			    printf("插入成功！\n"); break;
				    		}
				    		printf("插入失败！\n"); break;
				    	}
				    	else{              //好友信息不存在 
				    		printf("该粉丝不存在，插入失败！\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("请输入要删除的粉丝的id：");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.fans,id,Tb)){        //好友信息存在 
		            		if(set_remove(Ta->data.fans,id)){
		            			if(set_member(T,id,Tb)){
		            				if(set_remove(Tb->data.attention,Ta->data.id))
		            				printf("已删除粉丝%s！\n",Tb->data.name); break;
								}	
				    		}
				    		printf("删除失败！\n"); break;
				    	}
				    	else{              //好友信息不存在 
				    		printf("该粉丝不存在，删除失败！\n");
				    	}
				    	break;
				}
				break;
			case 4:             //关注集操作
			    printf("1.增加     2.删除     0.返回\n");
				printf("请输入要进行的操作[0-3]：");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("请重新输入：");
			        scanf("%d",&i); getchar();
		        }
		        
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("请输入要关注的人的id：");
		            	scanf("%d",&id);
		            	if(set_member(T,id,Tb)){        //好友信息存在 
		            		if(set_insert(Ta->data.attention,Tb->data)){
		            			if(set_insert(Tb->data.fans,Ta->data))
		            			    printf("关注成功！\n"); break;
				    		}
				    		printf("关注失败！\n"); break;
				    	}
				    	else{              //好友信息不存在 
				    		printf("此人不存在，关注失败！\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("请输入要取消关注的人的id：");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.attention,id,Tb)){        //好友信息存在 
		            		if(set_remove(Ta->data.attention,id)){
		            			if(set_member(T,id,Tb)){
		            				if(set_remove(Tb->data.fans,Ta->data.id))
		            				printf("已取消关注%s！\n",Tb->data.name); break;
								}	
				    		}
				    		printf("删除失败！\n"); break;
				    	}
				    	else{              //好友信息不存在 
				    		printf("该好友不存在，删除失败！\n");
				    	}
				    	break;
				}
				break;
			case 5:             //爱好集操作 
			    printf("1.增加     2.删除     0.返回\n");
				printf("请输入要进行的操作[0-3]：");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("请重新输入：");
			        scanf("%d",&i); getchar();
		        }
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("请输入要插入的喜好的id[0-%d]：",b);
		            	scanf("%d",&id); getchar();
		            	if(set_member(H,id,Tb)){      
						    printf("id为%d的喜好为%s!\n",id,Tb->data.name);  
		            		if(set_insert(Ta->data.hobby,Tb->data)){
		            			printf("插入成功！\n"); break;
				    		}
				    		else{
				    			printf("插入失败！\n"); break;
				    		}
				    	}
				    	else{             
				    		printf("该喜好不存在，插入失败！\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("请输入要删除的喜好的id：");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.hobby,id,Tb)){         
		            		if(set_remove(Ta->data.hobby,id)){
		            			printf("已删除喜好%s！\n",Tb->data.name);
				    		}
				    		else{
				    			printf("删除失败！\n");
				    		}
				    	}
				    	else{              
				    		printf("该成员无此喜好，删除失败！\n");
				    	}
				    	break;
				}
				break;
		}
	}
}

status operator_tree2(BSTree &T,BSTree H,int a,int b){
	//对应用层中数据进行查找，随后进行删除、增加、修改等操作
	BSTree Ta=NULL,Tb=NULL;
	int id=0, i=0,j=0;
	printf("请输入要查找的id：");
	scanf("%d",&id); getchar();
	if(!set_member(T,id,Ta)){
		printf("查找失败！\n"); return ERROR;
	}
	else{
		printf("查找成功,id为%d的是%s!：\n",id,Ta->data.name);
		printf("-----------------------------------------------------\n");
		printf("1.friend          2.fans         3.attention \n"); 
		printf("4.hobby           0.返回\n");
		printf("-----------------------------------------------------\n");
		printf("请输入要查询的内容的序号[0-4]：");  scanf("%d",&j); getchar();
		while(j<0||j>4){
			printf("请重新输入：");
			scanf("%d",&j); getchar();
		}
		switch(j){
			case 0: break;
			case 1:             //好友集操作 
			    PTraverseAVL(Ta->data.friends);
				printf("\n-----------------------------------------------------\n");
				printf("1.增加     2.删除     0.返回\n");
				printf("请输入要进行的操作[0-3]：");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("请重新输入：");
			        scanf("%d",&i); getchar();
		        }
		        
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("请输入要插入的好友的id：");
		            	scanf("%d",&id);
		            	if(set_member(T,id,Tb)){        //好友信息存在 
		            		if(set_insert(Ta->data.friends,Tb->data)){
		            			if(set_insert(Tb->data.friends,Ta->data)) 
		            			    printf("插入成功！\n"); break;
				    		}
				    		printf("插入失败！\n"); break;
				    	}
				    	else{              //好友信息不存在 
				    		printf("该好友不存在，插入失败！\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("请输入要删除的好友的id：");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.friends,id,Tb)){        //好友信息存在 
		            		if(set_remove(Ta->data.friends,id)){
		            			if(set_member(T,id,Tb)){
		            				if(set_remove(Tb->data.friends,Ta->data.id))
		            				printf("已删除好友%s！\n",Tb->data.name); break;
								}	
				    		}
				    		printf("删除失败！\n"); break;
				    	}
				    	else{              //好友信息不存在 
				    		printf("该好友不存在，删除失败！\n");
				    	}
				    	break;
			}
			break;
			case 2:             //粉丝集操作
			    PTraverseAVL(Ta->data.fans);
			    printf("\n-----------------------------------------------------\n");
			    printf("1.增加     2.删除     0.返回\n");
				printf("请输入要进行的操作[0-3]：");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("请重新输入：");
			        scanf("%d",&i); getchar();
		        }
		        
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("请输入要插入的粉丝的id：");
		            	scanf("%d",&id);
		            	if(set_member(T,id,Tb)){        //好友信息存在 
		            		if(set_insert(Ta->data.fans,Tb->data)){
		            			if(set_insert(Tb->data.attention,Ta->data))
		            			    printf("插入成功！\n"); break;
				    		}
				    		printf("插入失败！\n"); break;
				    	}
				    	else{              //好友信息不存在 
				    		printf("该粉丝不存在，插入失败！\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("请输入要删除的粉丝的id：");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.fans,id,Tb)){        //好友信息存在 
		            		if(set_remove(Ta->data.fans,id)){
		            			if(set_member(T,id,Tb)){
		            				if(set_remove(Tb->data.attention,Ta->data.id))
		            				printf("已删除粉丝%s！\n",Tb->data.name); break;
								}	
				    		}
				    		printf("删除失败！\n"); break;
				    	}
				    	else{              //好友信息不存在 
				    		printf("该粉丝不存在，删除失败！\n");
				    	}
				    	break;
				}
				break;
			case 3:             //关注集操作
			    PTraverseAVL(Ta->data.attention);
			    printf("\n-----------------------------------------------------\n");
			    printf("1.增加     2.删除     0.返回\n");
				printf("请输入要进行的操作[0-3]：");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("请重新输入：");
			        scanf("%d",&i); getchar();
		        }
		        
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("请输入要关注的人的id：");
		            	scanf("%d",&id);
		            	if(set_member(T,id,Tb)){        //好友信息存在 
		            		if(set_insert(Ta->data.attention,Tb->data)){
		            			if(set_insert(Tb->data.fans,Ta->data))
		            			    printf("关注成功！\n"); break;
				    		}
				    		printf("关注失败！\n"); break;
				    	}
				    	else{              //好友信息不存在 
				    		printf("此人不存在，关注失败！\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("请输入要取消关注的人的id：");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.attention,id,Tb)){        //好友信息存在 
		            		if(set_remove(Ta->data.attention,id)){
		            			if(set_member(T,id,Tb)){
		            				if(set_remove(Tb->data.fans,Ta->data.id))
		            				printf("已取消关注%s！\n",Tb->data.name); break;
								}	
				    		}
				    		printf("删除失败！\n"); break;
				    	}
				    	else{              //好友信息不存在 
				    		printf("该好友不存在，删除失败！\n");
				    	}
				    	break;
				}
				break;
			case 4:             //爱好集操作
	    		PTraverseAVL(Ta->data.hobby);
		    	printf("\n-----------------------------------------------------\n"); 
			    printf("1.增加     2.删除     0.结束\n");
				printf("请输入要进行的操作[0-3]：");  scanf("%d",&i); getchar();
				while(i<0||i>5){
			        printf("请重新输入：");
			        scanf("%d",&i); getchar();
		        }
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("请输入要插入的喜好的id[0-%d]：",b);
		            	scanf("%d",&id); getchar();
		            	if(set_member(H,id,Tb)){      
						    printf("id为%d的喜好为%s!\n",id,Tb->data.name);  
		            		if(set_insert(Ta->data.hobby,Tb->data)){
		            			printf("插入成功！\n"); break;
				    		}
				    		else{
				    			printf("插入失败！\n"); break;
				    		}
				    	}
				    	else{             
				    		printf("该喜好不存在，插入失败！\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("请输入要删除的喜好的id：");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.hobby,id,Tb)){         
		            		if(set_remove(Ta->data.hobby,id)){
		            			printf("已删除喜好%s！\n",Tb->data.name);
				    		}
				    		else{
				    			printf("删除失败！\n");
				    		}
				    	}
				    	else{              
				    		printf("该成员无此喜好，删除失败！\n");
				    	}
				    	break;
				}
				break;
		}
	}
}

