#include "ADT.h"


//��ͬ��ע����ͬ���� 
status common(BSTree T1,BSTree T2,BSTree &T){
	//��ȡ������T1��T2�Ĺ�ͬ��Ա 
	if(!set_intersection(T1,T2,T)) return ERROR;
	return OK;
}

//���Ⱥ��� 
status search_friend(BSTree T,BSTree Ta,BSTree &Tb){
	//���Ⱥ��ѵĸ���������������TaΪT��ĳ��Ա�����Ѽ�
	//�����Ѽ��г�Ա��������Ϣ���뼯��Tb
	BSTree Tc=NULL;          //ָ������ѵ�ָ��
	if(!Ta) return OK;
	if(!set_member(T,Ta->data.id,Tc)) return ERROR;
	//ͨ���������������ѵ����Ѽ���ֵ�������Tb
	if(!set_union(Tb,Tc->data.friends)) return ERROR;
	if(!search_friend(T,Ta->lchild,Tb)) return ERROR;
	return OK;
}

status second_friend(BSTree T,int id){
	//����������idΪid�ĳ�Ա�Ķ��Ⱥ��� 
	if(!T) return ERROR;
	BSTree Ta=NULL;     //һ�����Ѽ� 
	BSTree Tb=NULL;     //�������Ѽ� 
	if(!set_member(T,id,Ta)){
		printf("���˲����ڣ�\n");
		return ERROR;
	}
	if(!(Ta->data.friends)){
		printf("idΪ%d����%s,�ó�Ա�����ѣ�\n",Ta->data.id,Ta->data.name);
		return ERROR;
	}
	if(!search_friend(T,Ta->data.friends,Tb)) return ERROR;
	if(!Tb){
		printf("idΪ%d����%s,�ó�Ա�޶��Ⱥ��ѣ�\n",Ta->data.id,Ta->data.name);	
	}
	else{
		printf("idΪ%d����%s,%s�Ķ��Ⱥ���Ϊ��\n",Ta->data.id,Ta->data.name,Ta->data.name);
    	PTraverseAVL(Tb);   printf("\n"); 
	}
	return OK;
}


status Common_attention(BSTree &T){
	//��ͬ��ע����ϵͳ
	int id=0;
	BSTree Ta=NULL,Tb=NULL,Tc=NULL;      //�������� 
	printf("�������һ���˵�id��"); 
	scanf("%d",&id); getchar();
	if(!set_member(T,id,Ta)){
		printf("���˲����ڣ�\n");
		return ERROR;
	}
	printf("������ڶ����˵�id��");
	scanf("%d",&id); getchar();
	if(!set_member(T,id,Tb)){
		printf("���˲����ڣ�\n");
		return ERROR;
	}
	if(!common(Ta->data.attention,Tb->data.attention,Tc)){
		printf("��ȡ��ͬ��עʧ�ܣ�\n"); return ERROR;
	}
	if(!(Ta->data.attention)){
		printf("idΪ%d����%s,���޹�ע�ˣ�\n",Ta->data.id,Ta->data.name);
		return ERROR; 
	}
	if(!(Tb->data.attention)){
		printf("idΪ%d����%s,���޹�ע�ˣ�\n",Tb->data.id,Tb->data.name);
		return ERROR;
	}
	printf("idΪ%d����%s,���ע�����У�\n",Ta->data.id,Ta->data.name);
	PTraverseAVL(Ta->data.attention); printf("\n");
	printf("idΪ%d����%s,���ע�����У�\n",Tb->data.id,Tb->data.name);
	PTraverseAVL(Tb->data.attention); printf("\n");
	if(!Tc){
		printf("%s��%s�޹�ͬ��ע��\n",Ta->data.name,Tb->data.name);
		return OK;
	}
	else{
		printf("��ͬ��ע�У�\n");
	    PTraverseAVL(Tc); printf("\n");
	}
	return OK;
}

status Common_hobby(BSTree &T){
	//��ͬϲ�ò���ϵͳ
	int id=0;
	BSTree Ta=NULL,Tb=NULL,Tc=NULL;      //�������� 
	printf("�������һ���˵�id��"); 
	scanf("%d",&id); getchar();
	if(!set_member(T,id,Ta)){
		printf("���˲����ڣ�\n");
		return ERROR;
	}
	printf("������ڶ����˵�id��");
	scanf("%d",&id); getchar();
	if(!set_member(T,id,Tb)){
		printf("���˲����ڣ�\n");
		return ERROR;
	}
	if(!common(Ta->data.hobby,Tb->data.hobby,Tc)){
		printf("��ȡ��ͬϲ��ʧ�ܣ�\n"); return ERROR;
	}
	if(!(Ta->data.hobby)){
		printf("idΪ%d����%s,����ϲ�ã�\n",Ta->data.id,Ta->data.name);
		return ERROR; 
	}
	if(!(Tb->data.hobby)){
		printf("idΪ%d����%s,����ϲ�ã�\n",Tb->data.id,Tb->data.name);
		return ERROR;
	}
	printf("idΪ%d����%s,��ϲ���У�\n",Ta->data.id,Ta->data.name);
	PTraverseAVL(Ta->data.hobby); printf("\n");
	printf("idΪ%d����%s,��ϲ���У�\n",Tb->data.id,Tb->data.name);
	PTraverseAVL(Tb->data.hobby); printf("\n");
	if(!Tc){
		printf("%s��%s�޹�ͬϲ�ã�\n",Ta->data.name,Tb->data.name);
		return OK;
	}
	else{
		printf("��ͬϲ���У�\n");
	    PTraverseAVL(Tc); printf("\n");
	}
	return OK;
}

status hobby_set_input(BSTree &H,int &n){
	//��ȡ�ļ�hobby.txt,��������������H,
	//n��¼��ȡ���� 
    FILE *fp;
    ElemType e; InitElem(e);
    int number=0;
    if(H){           //��ն����� 
    	set_destroy(H); H=NULL;
	}
    if((fp=fopen("hobby.txt","r"))==NULL){
        printf("���ļ�hobby.txtʧ��!\n");
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
	//��ȡ�ļ�name.txt,��������������N 
    FILE *fp;
    ElemType e;
    int number=0;
    if(N){           //��ն����� 
    	set_destroy(N); N=NULL;
	}
    if((fp=fopen("name.txt","r"))==NULL){
        printf("���ļ�name.txtʧ��!\n");
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
	//�������һ�ö��������ö��������id������gross�������Ϊmin-min+max 
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
	//������ɹ�ϵ��NΪ��������HΪϲ�ü�
	//aΪ�������������,bΪϲ�ü�������� 
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
	//�������һ���������Ϊb�ĳ�Ա��Ϣ 
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
	//���Ƴ�Ա�����Ѽ���Ϣ,TaΪĳ��Ա���Ѽ�,eΪ�ó�Ա��Ϣ 
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
	//���Ƴ�Ա�Ĺ�ע����Ϣ,TaΪĳ��Ա��˿��,eΪ�ó�Ա��Ϣ 
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
	//���Ƴ�Ա�ķ�˿����Ϣ,TaΪĳ��Ա��ע��,eΪ�ó�Ա��Ϣ 
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
	//���T�Ĺ�ϵ�����Ƿ����Լ�������У�ɾ��
	BSTree Ta=NULL;
	if(!T) return OK;
	//������Ѽ� 
	if(set_member(T->data.friends,T->data.id,Ta)){
		if(!set_remove(T->data.friends,T->data.id)) return ERROR;
	}
	//����˿��
	if(set_member(T->data.fans,T->data.id,Ta)){
		if(!set_remove(T->data.fans,T->data.id)) return ERROR;
	}
	//����ע��
	if(set_member(T->data.attention,T->data.id,Ta)){
		if(!set_remove(T->data.attention,T->data.id)) return ERROR;
	}
	return OK;
}

status improve_relation(BSTree &T,BSTree &T1){
	//���Ƴ�Ա��ϵ����ʹ���ѻ�����ڣ�ʹ��Ա�ķ�˿�Ĺ�ע���иó�Ա
	//��ֹ��Ա�����Ѽ�����˿������ע�����б���
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
	//��Ӧ�ò������ݽ��в��ң�������ɾ�������ӡ��޸ĵȲ���
	BSTree Ta=NULL,Tb=NULL;
	int id=0, i=0,j=0;
	printf("������Ҫ���ҵ�id��");
	scanf("%d",&id); getchar();
	if(!set_member(T,id,Ta)){
		printf("����ʧ�ܣ�\n"); return ERROR;
	}
	else{
		printf("���ҳɹ�,������Ϣ���£�\n");
		printf("  id��");    printf("%d\n",Ta->data.id);
		printf("name��");    printf("%s\n",Ta->data.name);
		printf("friend��\n"); PTraverseAVL(Ta->data.friends);  printf("\n");
		printf("fans��\n");   PTraverseAVL(Ta->data.fans);   printf("\n");
		printf("attention��\n");  PTraverseAVL(Ta->data.attention);   printf("\n");
		printf("hobby��\n");  PTraverseAVL(Ta->data.hobby);    printf("\n");
		printf("-----------------------------------------------------\n");
		printf("1.name            2.friend       3.fans\n"); 
		printf("4.attention       5.hobby        0.����\n");
		printf("-----------------------------------------------------\n");
		printf("������Ҫ���в��������ݵ����[0-5]��");  scanf("%d",&j); getchar();
		while(j<0||j>5){
			printf("���������룺");
			scanf("%d",&j); getchar();
		}
		switch(j){
			case 0: break;
			case 1:
				printf("�������µ�������");
				scanf("%s",&Ta->data.name);
				printf("�޸ĳɹ���\n");
				break;
			case 2:             //���Ѽ����� 
				printf("1.����     2.ɾ��     0.����\n");
				printf("������Ҫ���еĲ���[0-3]��");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("���������룺");
			        scanf("%d",&i); getchar();
		        }
		        
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("������Ҫ����ĺ��ѵ�id��");
		            	scanf("%d",&id);
		            	if(set_member(T,id,Tb)){        //������Ϣ���� 
		            		if(set_insert(Ta->data.friends,Tb->data)){
		            			if(set_insert(Tb->data.friends,Ta->data)) 
		            			    printf("����ɹ���\n"); break;
				    		}
				    		printf("����ʧ�ܣ�\n"); break;
				    	}
				    	else{              //������Ϣ������ 
				    		printf("�ú��Ѳ����ڣ�����ʧ�ܣ�\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("������Ҫɾ���ĺ��ѵ�id��");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.friends,id,Tb)){        //������Ϣ���� 
		            		if(set_remove(Ta->data.friends,id)){
		            			if(set_member(T,id,Tb)){
		            				if(set_remove(Tb->data.friends,Ta->data.id))
		            				printf("��ɾ������%s��\n",Tb->data.name); break;
								}	
				    		}
				    		printf("ɾ��ʧ�ܣ�\n"); break;
				    	}
				    	else{              //������Ϣ������ 
				    		printf("�ú��Ѳ����ڣ�ɾ��ʧ�ܣ�\n");
				    	}
				    	break;
				}
				break;
			case 3:             //��˿������
			    printf("1.����     2.ɾ��     0.����\n");
				printf("������Ҫ���еĲ���[0-3]��");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("���������룺");
			        scanf("%d",&i); getchar();
		        }
		        
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("������Ҫ����ķ�˿��id��");
		            	scanf("%d",&id);
		            	if(set_member(T,id,Tb)){        //������Ϣ���� 
		            		if(set_insert(Ta->data.fans,Tb->data)){
		            			if(set_insert(Tb->data.attention,Ta->data))
		            			    printf("����ɹ���\n"); break;
				    		}
				    		printf("����ʧ�ܣ�\n"); break;
				    	}
				    	else{              //������Ϣ������ 
				    		printf("�÷�˿�����ڣ�����ʧ�ܣ�\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("������Ҫɾ���ķ�˿��id��");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.fans,id,Tb)){        //������Ϣ���� 
		            		if(set_remove(Ta->data.fans,id)){
		            			if(set_member(T,id,Tb)){
		            				if(set_remove(Tb->data.attention,Ta->data.id))
		            				printf("��ɾ����˿%s��\n",Tb->data.name); break;
								}	
				    		}
				    		printf("ɾ��ʧ�ܣ�\n"); break;
				    	}
				    	else{              //������Ϣ������ 
				    		printf("�÷�˿�����ڣ�ɾ��ʧ�ܣ�\n");
				    	}
				    	break;
				}
				break;
			case 4:             //��ע������
			    printf("1.����     2.ɾ��     0.����\n");
				printf("������Ҫ���еĲ���[0-3]��");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("���������룺");
			        scanf("%d",&i); getchar();
		        }
		        
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("������Ҫ��ע���˵�id��");
		            	scanf("%d",&id);
		            	if(set_member(T,id,Tb)){        //������Ϣ���� 
		            		if(set_insert(Ta->data.attention,Tb->data)){
		            			if(set_insert(Tb->data.fans,Ta->data))
		            			    printf("��ע�ɹ���\n"); break;
				    		}
				    		printf("��עʧ�ܣ�\n"); break;
				    	}
				    	else{              //������Ϣ������ 
				    		printf("���˲����ڣ���עʧ�ܣ�\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("������Ҫȡ����ע���˵�id��");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.attention,id,Tb)){        //������Ϣ���� 
		            		if(set_remove(Ta->data.attention,id)){
		            			if(set_member(T,id,Tb)){
		            				if(set_remove(Tb->data.fans,Ta->data.id))
		            				printf("��ȡ����ע%s��\n",Tb->data.name); break;
								}	
				    		}
				    		printf("ɾ��ʧ�ܣ�\n"); break;
				    	}
				    	else{              //������Ϣ������ 
				    		printf("�ú��Ѳ����ڣ�ɾ��ʧ�ܣ�\n");
				    	}
				    	break;
				}
				break;
			case 5:             //���ü����� 
			    printf("1.����     2.ɾ��     0.����\n");
				printf("������Ҫ���еĲ���[0-3]��");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("���������룺");
			        scanf("%d",&i); getchar();
		        }
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("������Ҫ�����ϲ�õ�id[0-%d]��",b);
		            	scanf("%d",&id); getchar();
		            	if(set_member(H,id,Tb)){      
						    printf("idΪ%d��ϲ��Ϊ%s!\n",id,Tb->data.name);  
		            		if(set_insert(Ta->data.hobby,Tb->data)){
		            			printf("����ɹ���\n"); break;
				    		}
				    		else{
				    			printf("����ʧ�ܣ�\n"); break;
				    		}
				    	}
				    	else{             
				    		printf("��ϲ�ò����ڣ�����ʧ�ܣ�\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("������Ҫɾ����ϲ�õ�id��");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.hobby,id,Tb)){         
		            		if(set_remove(Ta->data.hobby,id)){
		            			printf("��ɾ��ϲ��%s��\n",Tb->data.name);
				    		}
				    		else{
				    			printf("ɾ��ʧ�ܣ�\n");
				    		}
				    	}
				    	else{              
				    		printf("�ó�Ա�޴�ϲ�ã�ɾ��ʧ�ܣ�\n");
				    	}
				    	break;
				}
				break;
		}
	}
}

status operator_tree2(BSTree &T,BSTree H,int a,int b){
	//��Ӧ�ò������ݽ��в��ң�������ɾ�������ӡ��޸ĵȲ���
	BSTree Ta=NULL,Tb=NULL;
	int id=0, i=0,j=0;
	printf("������Ҫ���ҵ�id��");
	scanf("%d",&id); getchar();
	if(!set_member(T,id,Ta)){
		printf("����ʧ�ܣ�\n"); return ERROR;
	}
	else{
		printf("���ҳɹ�,idΪ%d����%s!��\n",id,Ta->data.name);
		printf("-----------------------------------------------------\n");
		printf("1.friend          2.fans         3.attention \n"); 
		printf("4.hobby           0.����\n");
		printf("-----------------------------------------------------\n");
		printf("������Ҫ��ѯ�����ݵ����[0-4]��");  scanf("%d",&j); getchar();
		while(j<0||j>4){
			printf("���������룺");
			scanf("%d",&j); getchar();
		}
		switch(j){
			case 0: break;
			case 1:             //���Ѽ����� 
			    PTraverseAVL(Ta->data.friends);
				printf("\n-----------------------------------------------------\n");
				printf("1.����     2.ɾ��     0.����\n");
				printf("������Ҫ���еĲ���[0-3]��");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("���������룺");
			        scanf("%d",&i); getchar();
		        }
		        
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("������Ҫ����ĺ��ѵ�id��");
		            	scanf("%d",&id);
		            	if(set_member(T,id,Tb)){        //������Ϣ���� 
		            		if(set_insert(Ta->data.friends,Tb->data)){
		            			if(set_insert(Tb->data.friends,Ta->data)) 
		            			    printf("����ɹ���\n"); break;
				    		}
				    		printf("����ʧ�ܣ�\n"); break;
				    	}
				    	else{              //������Ϣ������ 
				    		printf("�ú��Ѳ����ڣ�����ʧ�ܣ�\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("������Ҫɾ���ĺ��ѵ�id��");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.friends,id,Tb)){        //������Ϣ���� 
		            		if(set_remove(Ta->data.friends,id)){
		            			if(set_member(T,id,Tb)){
		            				if(set_remove(Tb->data.friends,Ta->data.id))
		            				printf("��ɾ������%s��\n",Tb->data.name); break;
								}	
				    		}
				    		printf("ɾ��ʧ�ܣ�\n"); break;
				    	}
				    	else{              //������Ϣ������ 
				    		printf("�ú��Ѳ����ڣ�ɾ��ʧ�ܣ�\n");
				    	}
				    	break;
			}
			break;
			case 2:             //��˿������
			    PTraverseAVL(Ta->data.fans);
			    printf("\n-----------------------------------------------------\n");
			    printf("1.����     2.ɾ��     0.����\n");
				printf("������Ҫ���еĲ���[0-3]��");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("���������룺");
			        scanf("%d",&i); getchar();
		        }
		        
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("������Ҫ����ķ�˿��id��");
		            	scanf("%d",&id);
		            	if(set_member(T,id,Tb)){        //������Ϣ���� 
		            		if(set_insert(Ta->data.fans,Tb->data)){
		            			if(set_insert(Tb->data.attention,Ta->data))
		            			    printf("����ɹ���\n"); break;
				    		}
				    		printf("����ʧ�ܣ�\n"); break;
				    	}
				    	else{              //������Ϣ������ 
				    		printf("�÷�˿�����ڣ�����ʧ�ܣ�\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("������Ҫɾ���ķ�˿��id��");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.fans,id,Tb)){        //������Ϣ���� 
		            		if(set_remove(Ta->data.fans,id)){
		            			if(set_member(T,id,Tb)){
		            				if(set_remove(Tb->data.attention,Ta->data.id))
		            				printf("��ɾ����˿%s��\n",Tb->data.name); break;
								}	
				    		}
				    		printf("ɾ��ʧ�ܣ�\n"); break;
				    	}
				    	else{              //������Ϣ������ 
				    		printf("�÷�˿�����ڣ�ɾ��ʧ�ܣ�\n");
				    	}
				    	break;
				}
				break;
			case 3:             //��ע������
			    PTraverseAVL(Ta->data.attention);
			    printf("\n-----------------------------------------------------\n");
			    printf("1.����     2.ɾ��     0.����\n");
				printf("������Ҫ���еĲ���[0-3]��");  scanf("%d",&i); getchar();
				while(i<0||i>3){
			        printf("���������룺");
			        scanf("%d",&i); getchar();
		        }
		        
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("������Ҫ��ע���˵�id��");
		            	scanf("%d",&id);
		            	if(set_member(T,id,Tb)){        //������Ϣ���� 
		            		if(set_insert(Ta->data.attention,Tb->data)){
		            			if(set_insert(Tb->data.fans,Ta->data))
		            			    printf("��ע�ɹ���\n"); break;
				    		}
				    		printf("��עʧ�ܣ�\n"); break;
				    	}
				    	else{              //������Ϣ������ 
				    		printf("���˲����ڣ���עʧ�ܣ�\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("������Ҫȡ����ע���˵�id��");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.attention,id,Tb)){        //������Ϣ���� 
		            		if(set_remove(Ta->data.attention,id)){
		            			if(set_member(T,id,Tb)){
		            				if(set_remove(Tb->data.fans,Ta->data.id))
		            				printf("��ȡ����ע%s��\n",Tb->data.name); break;
								}	
				    		}
				    		printf("ɾ��ʧ�ܣ�\n"); break;
				    	}
				    	else{              //������Ϣ������ 
				    		printf("�ú��Ѳ����ڣ�ɾ��ʧ�ܣ�\n");
				    	}
				    	break;
				}
				break;
			case 4:             //���ü�����
	    		PTraverseAVL(Ta->data.hobby);
		    	printf("\n-----------------------------------------------------\n"); 
			    printf("1.����     2.ɾ��     0.����\n");
				printf("������Ҫ���еĲ���[0-3]��");  scanf("%d",&i); getchar();
				while(i<0||i>5){
			        printf("���������룺");
			        scanf("%d",&i); getchar();
		        }
		        switch(i){
		        	case 0: break;
		        	case 1:
		        		id=0;
		        	    printf("������Ҫ�����ϲ�õ�id[0-%d]��",b);
		            	scanf("%d",&id); getchar();
		            	if(set_member(H,id,Tb)){      
						    printf("idΪ%d��ϲ��Ϊ%s!\n",id,Tb->data.name);  
		            		if(set_insert(Ta->data.hobby,Tb->data)){
		            			printf("����ɹ���\n"); break;
				    		}
				    		else{
				    			printf("����ʧ�ܣ�\n"); break;
				    		}
				    	}
				    	else{             
				    		printf("��ϲ�ò����ڣ�����ʧ�ܣ�\n");
				    	}
				    	break;
				    case 2:
				    	id=0;
		        	    printf("������Ҫɾ����ϲ�õ�id��");
		            	scanf("%d",&id);
		            	if(set_member(Ta->data.hobby,id,Tb)){         
		            		if(set_remove(Ta->data.hobby,id)){
		            			printf("��ɾ��ϲ��%s��\n",Tb->data.name);
				    		}
				    		else{
				    			printf("ɾ��ʧ�ܣ�\n");
				    		}
				    	}
				    	else{              
				    		printf("�ó�Ա�޴�ϲ�ã�ɾ��ʧ�ܣ�\n");
				    	}
				    	break;
				}
				break;
		}
	}
}

