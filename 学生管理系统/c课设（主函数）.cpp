#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void change_grade(struct Grade *ph1,struct Grade *ph2);
void change_class(struct Class *ph1,struct Class *ph2);
void change_student(struct Student *ph1,struct Student *ph2);//����ѧ����Ϣ

//ѧ����Ϣ�ṹ 
struct Student{
	char SNo[10];//ѧ�� 
	char name[10];//ѧ������ 
	char sex;//�Ա� ��1���У�2��Ů�� 
	char native_place[10];//���� 
	char year[10];//�������� 
	char telephone[20];//��ϵ�绰 
	float score;//��ѧ�ɼ� 
	int graduate;//�Ƿ��ҵ��0��û��ҵ�� 1����ҵ�� 
	char graduate_place[10];//��ҵȥ�� 
	
	struct Student *next;
};

//�༶��Ϣ�ṹ 
struct Class{
	char CNo[8];//�༶��� 
	char major[15];//רҵ���� 
	int num_enter;//��ѧ���� 
	float ave_of_age;//��ѧƽ������ 
	int num_graduate;//��ҵ���� 
	char monitor[10];//�೤���� 
	char telephone[20];//�೤�绰 
	char teacher[10];//���������� 
	char telephone_teacher[20];//�����ε绰 
	struct Student *student;//ѧ����Ϣ 
	
	struct Class *next;
};

//�꼶��Ϣ�ṹ 
struct Grade{
	char CSNo[10];//�꼶��� 
	int time;//��ѧʱ�� 
	int num_enter;//��ѧ���� 
	int num_graduate;//��ҵ���� 
	char name[10];//�꼶����Ա���� 
	char telephone[20];//����Ա�绰 
	char name_chairman[10];//ѧ������ϯ 
	struct Class *classes; //�༶��Ϣ 
	
	struct Grade *next;
};

struct Count{
	char CNO[8];//�༶��� 
	int num; //δ��ҵ����
	  
	struct Count *next;
};//��������༶��δ��ҵ�����Ľṹ 

struct Count2{
	char graduate_place[10];//��ҵ�� 
	int num;//ѧ���� 
	
	struct Count2 *next;
};//����ѧ����ҵȥ��Ľṹ 

int char_to_int(char s[])//��ȡ��������ǰ��λ��ת��Ϊint�� 
{
	int m=0;
	for(int i=0;i<4;i++)
	{
		m=m*10+(s[i]-'0'); 	
	}
	return m;
}

int char_to_int2(char s[])//������ת��Ϊ���� 
{
	int sum=0;
	for(int n=0;s[n]!='\0';n++)
	sum=sum*10+(s[n]-'0');
	return sum;
 }

/************************************************************
�������ƣ�freetext
�������ܣ�ģ����ѯ 
��������������s2Ϊ��ѯ���ݣ�����s1Ϊ����s2�Ƚϵ����� 
����ֵ���� s2Ϊs1�Ӵ�������1�����򷵻�0 
************************************************************/ 
int freetext(char s1[],char s2[])
{
	int flag=0;
	int m=strlen(s1),n=strlen(s2);
	for(int i=0;i<m;i++)
	{
		if(s1[i]==s2[0])
		for(int j=1;j<n;j++)
		    if(s1[i+j]=='\0'||s1[i+j]!=s2[j]) break;
		    else flag=1;
	}
	if(flag==0) return 0;
	else return 1;
}

/************************************************************
�������ƣ�sort1
�������ܣ��༶ͳ���и���δ��ҵ�����԰༶����
����������Cout�ṹָ�� 
����ֵ���� 
*************************************************************/ 
void sort1(struct Count *head)
{
	int count=0,i,j,t;
	char s[8];
	struct Count *p1=head,*p2;
	for(;p1!=NULL;p1=p1->next) count++;//��������Ԫ������ 
    for(i=0,p1=head;i<count-1;i++,p1=p1->next);
    {
    	for(j=i+1,p2=p1->next;j<count-1;j++,p2=p2->next)
    	if(p1->num<p2->num){
    		t=p1->num;p1->num=p2->num;p2->num=t;
    		strcpy(s,p1->CNO);strcpy(p1->CNO,p2->CNO);strcpy(p2->CNO,s);
		}
	}
}

/************************************************************
�������ƣ�sort2 
�������ܣ�ѧ��ͳ���и���ĳ��ҵ�������������� 
����������Count2�ṹָ�� 
����ֵ���� 
*************************************************************/
void sort2(struct Count2 *head)
{
	int count=0,i,j,t;
	char s[10];
	struct Count2 *p1=head,*p2;
	for(;p1!=NULL;p1=p1->next) count++;//��������Ԫ������ 
    for(i=0,p1=head;i<count-1;i++,p1=p1->next);
    {
    	for(j=i+1,p2=p1->next;j<count-1;j++,p2=p2->next)
    	if(p1->num<p2->num){
    		t=p1->num;p1->num=p2->num;p2->num=t;
    		strcpy(s,p1->graduate_place);strcpy(p1->graduate_place,p2->graduate_place);strcpy(p2->graduate_place,s);
		}
	}
}

/************************************************************
�������ƣ�sort_grade 
�������ܣ������꼶��Ŷ��꼶��Ϣ������ 
�����������꼶��ͷָ��head 
����ֵ���� 
*************************************************************/
void sort_grade(struct Grade *head)
{
	int count=0,i,j;
	struct Grade *p1=head,*p2;
	
	for(;p1!=NULL;p1=p1->next) count++;//��������Ԫ������ 
    for(i=0,p1=head;i<count-1;i++,p1=p1->next)
    {
    	for(j=i+1,p2=p1->next;j<count-1;j++,p2=p2->next)
    	{	
    	if(char_to_int2(p1->CSNo)>char_to_int2(p2->CSNo))
    	change_grade(p1,p2);
		}
    	
    }
}

/************************************************************
�������ƣ�sort_class 
�������ܣ����ݰ༶��Ŷ�ĳ�꼶�༶��Ϣ������ 
�����������༶��ͷָ��head 
����ֵ���� 
*************************************************************/
void sort_class(struct Class *head)
{
	int count=0,i,j;
	struct Class *p1=head,*p2;
	for(;p1!=NULL;p1=p1->next) count++;//��������Ԫ������ 
    for(i=0,p1=head;i<count-1;i++,p1=p1->next);
    {
    	for(j=i+1,p2=p1->next;j<count-1;j++,p2=p2->next)
    	if(char_to_int2(p1->CNo)>char_to_int2(p2->CNo))
    	change_class(p1,p2);
    }
}

/************************************************************
�������ƣ�sort_student
�������ܣ�����ѧ����Ŷ�ĳ�༶ѧ����Ϣ������ 
����������ѧ����Ϣ��ͷָ��head 
����ֵ���� 
*************************************************************/
void sort_student(struct Student *head)
{
	int count=0,i,j;
	struct Student *p1=head,*p2;
	for(;p1!=NULL;p1=p1->next) count++;//��������Ԫ������ 
    for(i=0,p1=head;i<count-1;i++,p1=p1->next);
    {
    	for(j=i+1,p2=p1->next;j<count-1;j++,p2=p2->next)
    	if(char_to_int2(p1->SNo)>char_to_int2(p2->SNo))
    	change_student(p1,p2);
    }
}

/************************************************************
�������ƣ�sort3
�������ܣ������꼶��ѧ�������꼶������ 
�����������꼶��Ϣ��ͷָ��head 
����ֵ���� 
*************************************************************/
void sort3(struct Grade *head)
{
	int count=0,i,j;
	struct Grade *p1=head,*p2;
	for(;p1!=NULL;p1=p1->next) count++;//��������Ԫ������ 
    for(i=0,p1=head;i<count-1;i++,p1=p1->next);
    {
    	for(j=i+1,p2=p1->next;j<count-1;j++,p2=p2->next)
    	if(p1->num_enter<p2->num_enter)
    	change_grade(p1,p2);
    }
 }

/************************************************************
�������ƣ�sort4
�������ܣ������꼶δ��ҵ�������꼶���� 
�����������꼶��Ϣ��ͷָ��head 
����ֵ���� 
*************************************************************/
void sort4(struct Grade *head)
{
	int count=0,i,j;
	struct Grade *p1=head,*p2;
	for(;p1!=NULL;p1=p1->next) count++;//��������Ԫ������ 
    for(i=0,p1=head;i<count-1;i++,p1=p1->next);
    {
    	for(j=i+1,p2=p1->next;j<count-1;j++,p2=p2->next)
    	if((p1->num_enter-p1->num_graduate)<(p2->num_enter-p2->num_graduate))
    	change_grade(p1,p2);
    }
 }
 
 /************************************************************
�������ƣ�revise_grade
�������ܣ��޸�ĳ���꼶��Ϣ��¼
����������ָ�����޸ĵ��꼶��¼��ָ�� 
����ֵ���� 
*************************************************************/
void revise_grade(struct Grade *head)
{
	struct Grade *p=head;
	printf("�������꼶��ţ���ѧʱ�䣬��ѧ��������ҵ�������꼶����Ա����������Ա�绰���꼶ѧ������ϯ\n");
	scanf("%s %d %d %d %s %s %s",p->CSNo,&p->time,&p->num_enter,\
	&p->num_graduate,p->name,p->telephone,p->name_chairman);
	getchar();
}

/************************************************************
�������ƣ�revise_class
�������ܣ���ĳ���༶��Ϣ��¼�����޸� 
����������ָ�����޸ĵİ༶��¼��ָ�� 
����ֵ���� 
*************************************************************/
void revise_class(struct Class *head)
{
		struct Class *q=head;
			printf("������༶��ţ�רҵ���ƣ���ѧ����,��ѧƽ�����䣬��ҵ����,�೤�������೤��ϵ�绰����������������������ϵ�绰\n");
		    scanf("%s %s %d %f %d %s %s %s %s",q->CNo,q->major,&q->num_enter,&q->ave_of_age,\
			&q->num_graduate,q->monitor,q->telephone,q->teacher,q->telephone_teacher);
		    getchar();
}

/************************************************************
�������ƣ�revise_student
�������ܣ���ĳ��ѧ����Ϣ��¼�����޸� 
����������ָ�����޸ĵ�ѧ����ָ�� 
����ֵ���� 
*************************************************************/
void revise_student(struct Student *head)//ѧ���޸� 
{
	struct Student *t=head;
	printf("������ѧ�ţ��������Ա𣬼��ᣬ�������£���ϵ�绰����ѧ�������Ƿ��ҵ����ҵȥ��\n");
	scanf("%s %s %c %s %s %s %f %d %s",t->SNo,t->name,&t->sex,t->native_place,\
		t->year,t->telephone,&t->score,&t->graduate,t->graduate_place);
	getchar();
}

/************************************************************
�������ƣ�delete_grade
�������ܣ�ɾ��ĳ���꼶��Ϣ 
�����������꼶��Ϣ��ͷָ��head��ָ����ɾ�����꼶��Ϣ��¼��ָ�� 
����ֵ���� 
*************************************************************/
void delete_grade(struct Grade *head,Grade *ph)//ɾ���꼶��Ϣ 
{
	struct Grade *p=head,*p2;
	if(strcmp(head->CSNo,ph->CSNo)==0) head=p->next;
	else{
		for(;p->next!=NULL;p=p->next){
		   p2=p->next;
		   if(strcmp(p2->CSNo,ph->CSNo)==0) p->next=ph->next;
	   }
	}	
 }

/************************************************************
�������ƣ�delete_class
�������ܣ�ɾ��ĳ���༶��Ϣ 
�����������꼶��Ϣ��ͷָ���ָ����ɾ���İ༶��Ϣ��¼��ָ�� 
����ֵ���� 
*************************************************************/  
void delete_class(struct Grade *head,Class *ph)//ɾ���༶��Ϣ 
{
	struct Grade *p=head;	
	for(;p->classes!=NULL;p=p->next)
	{
		Class *q=p->classes,*qh;	
		if(strcmp(q->CNo,ph->CNo)==0) p->classes=q->next;
		else{
			for(;q->next!=NULL;q=q->next)
			{
				qh=q->next;
				if(strcmp(qh->CNo,ph->CNo)==0) q->next=qh->next;
			 } 	
	   }	
	}
}

/************************************************************
�������ƣ�delete_student
�������ܣ�ɾ��ĳ��ѧ����Ϣ 
�����������꼶��Ϣ��ͷָ���ָ����ɾ����ѧ����Ϣ��¼��ָ�� 
����ֵ���� 
*************************************************************/
void delete_student(struct Grade *head,Student *ph)//ɾ��ѧ����Ϣ 
{
	struct Grade *p=head;
	for(;p->classes!=NULL;p=p->next)
	{
		Class *q=p->classes;
		for(;q->student!=NULL;q=q->next){
			Student *t=q->student,*th;
			if(strcmp(t->SNo,ph->SNo)==0) q->student=t->next;
			else{
				for(;t->next!=NULL;t=t->next){
					th=t->next;
					if(strcmp(th->SNo,ph->SNo)==0) t->next=th->next;
				}
			}
		}	
	}
}

/************************************************************
�������ƣ�seek_grade1 
�������ܣ������꼶��Ų�ѯ�꼶��Ϣ������ѯ�������ѯ���������������޸��꼶��Ϣ�� 
           �ɽ���ģ����ѯ 
��������������sΪ���ѯ�ı�����ݣ�headΪ�꼶����ͷָ�� 
����ֵ���� 
*************************************************************/
void seek_grade1(char s[],struct Grade *head)//�꼶��Ų�ѯ 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	if(strstr(p->CSNo,s)!=0)
	{
		printf("%-11s %-10d %-4d %-4d %-11s %-21s %-11s\n",p->CSNo,p->time,p->num_enter,p->num_graduate,p->name,p->telephone,p->name_chairman);
		printf("1.�޸�  2.ɾ��  0.ȡ��\n");
		int n;scanf("%d",&n);
		switch(n){
			case 1:
				revise_grade(p);
				break;
			case 2:
				delete_grade(head,p);
				break;
			case 0:
				break;
			}  
		flag=1;
	}
	if(flag==0) printf("�޸��꼶��Ϣ\n");
 }

/************************************************************
�������ƣ�seek_grade2
�������ܣ�����ʱ�����ޣ�����ڸ������ڵ��꼶��Ϣ �������ڼ�
          ���꼶��Ϣ������޸��꼶��Ϣ�� 
����������s1Ϊ��ǰ��ʱ�䣬s2Ϊ�����ʱ�䣬headΪ�꼶����ͷָ�� 
����ֵ���� 
*************************************************************/
void seek_grade2(int s1,int s2,struct Grade *head)//��ѧʱ���ѯ 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	if(s1<=p->time&&s2>=p->time)
	{
		printf("%11s %10d %4d %4d %11s %21s %11s\n",p->CSNo,p->time,p->num_enter,p->num_graduate,p->name,p->telephone,p->name_chairman);
		printf("1.�޸�  2.ɾ��  0.ȡ��\n");
		int n;scanf("%d",&n);
		switch(n){
			case 1:
				revise_grade(p);
				break;
			case 2:
				delete_grade(head,p);
				break;
			case 0:
				break;
			}  
		flag=1;
	}
	if(flag==0) printf("�޸��꼶��Ϣ\n");
}

/************************************************************
�������ƣ�seek_grade3
�������ܣ������������䣬�����ѧ�����ڸ�������꼶��Ϣ ��
          �����������꼶��Ϣ������޸��꼶��Ϣ�� 
����������s1Ϊ��С��������s2Ϊ�ϴ��������headΪ�꼶����ͷָ�� 
����ֵ���� 
*************************************************************/
void seek_grade3(int s1,int s2,struct Grade *head)//��ѧ������ѯ 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	if(s1<=p->num_enter&&s2>=p->num_enter)
	{
		printf("%11s %10d %4d %4d %11s %21s %11s\n",p->CSNo,p->time,p->num_enter,p->num_graduate,p->name,p->telephone,p->name_chairman);
		printf("1.�޸�  2.ɾ��  0.ȡ��\n");
		int n;scanf("%d",&n);
		switch(n){
			case 1:
				revise_grade(p);
				break;
			case 2:
				delete_grade(head,p);
				break;
			case 0:
				break;
			}  
		flag=1;
	}
	if(flag==0) printf("�޸��꼶��Ϣ\n");
}

/************************************************************
�������ƣ�seek_grade 
�������ܣ��꼶��ѯ����ϲ�ѯ����������������������������꼶
          ��Ϣ�������꼶��Ϣ������޸��꼶��Ϣ�� 
��������������sΪ�꼶��ţ�y1��y2Ϊʱ�����ޣ�s1��s2Ϊ�������� 
����ֵ���� 
*************************************************************/
void seek_grade4(char s[],int y1,int y2,int s1,int s2,struct Grade *head)//��ϲ�ѯ 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	if(freetext(p->CSNo,s)==1&&y1<=p->num_enter&&y2>=p->num_enter&&s1<=p->num_enter&&s2>=p->num_enter)
	{
		printf("%11s %10d %4d %4d %11s %21s %11s\n",p->CSNo,p->time,p->num_enter,p->num_graduate,p->name,p->telephone,p->name_chairman);
		printf("1.�޸�  2.ɾ��  0.ȡ��\n");
		int n;scanf("%d",&n);
		switch(n){
			case 1:
				revise_grade(p);
				break;
			case 2:
				delete_grade(head,p);
				break;
			case 0:
				break;
			}  
		flag=1;
	}
	if(flag==0) printf("�޸��꼶��Ϣ\n");
}

/************************************************************
�������ƣ�seek_class1
�������ܣ����ݰ༶��Ų�ѯ�༶��Ϣ������ѯ�������ѯ�����
          ����������޸ð༶��Ϣ�����ɽ���ģ����ѯ 
����������sΪ �༶������ݣ�headΪ�꼶����ͷָ�� 
����ֵ���� 
*************************************************************/
void seek_class1(char s[],struct Grade *head)//�༶��Ų�ѯ 
{
	struct Grade *p=head;
	int flag;
	for(;p!=NULL;p=p->next)
	{
		struct Class *q=p->classes;
		for(;q!=NULL;q=q->next)
		{
			if(strstr(q->CNo,s)!=0)
			{
				printf("%-9s %-16s %-4d %-3f %-4d %-11s %-21s %-10s %-20s\n",q->CNo,q->major,q->num_enter,q->ave_of_age,\
				q->num_graduate,q->monitor,q->telephone,q->teacher,q->telephone_teacher);
				printf("1.�޸�  2.ɾ��  0.ȡ��\n");
				int n;scanf("%d",&n);
				switch(n){
					case 1:
						revise_class(q);
						break;
					case 2:
						delete_class(head,q);
						break;
					case 0:
						break;
				}  
				flag=1;
			}
		}
	}
	if(flag==0) printf("�޸ð༶��Ϣ\n");
}

/************************************************************
�������ƣ�seek_class2
�������ܣ�����רҵ���Ʋ�ѯ�꼶��Ϣ������ѯ������꼶��Ϣ��
          ����������޸ð༶��Ϣ�����ɽ���ģ����ѯ 
����������sΪרҵ���ݣ�headΪ�꼶����ͷָ�� 
����ֵ���� 
*************************************************************/
void seek_class2(char s[],struct Grade *head)//�༶רҵ��ѯ��ѯ 
{
	struct Grade *p=head;
	int flag;
	for(;p!=NULL;p=p->next)
	{
		struct Class *q=p->classes;
		for(;q!=NULL;q=q->next)
		{
			if(freetext(q->major,s)==1)
			{
				printf("%-9s %-16s %-4d %-3f %-4d %-11s %-21s %-10s %-20s\n",q->CNo,q->major,q->num_enter,q->ave_of_age,\
				q->num_graduate,q->monitor,q->telephone,q->teacher,q->telephone_teacher);
				printf("1.�޸�  2.ɾ��  0.ȡ��\n");
				int n;scanf("%d",&n);
				switch(n){
					case 1:
						revise_class(q);
						break;
					case 2:
						delete_class(head,q);
						break;
					case 0:
						break;
				}  
				flag=1;
			}
		}
	}
	if(flag==0) printf("�޸ð༶��Ϣ\n");
}

/************************************************************
�������ƣ�seek_class3
�������ܣ����ݰ�����������ѯ�༶��Ϣ������ѯ������༶��Ϣ��
          ����������޸ð༶��Ϣ�����ɽ���ģ����ѯ 
����������sΪ������������headΪ�꼶����ͷָ�� 
����ֵ���� 
*************************************************************/
void seek_class3(char s[],struct Grade *head)//�����β�ѯ 
{
	struct Grade *p=head;
	int flag;
	for(;p!=NULL;p=p->next)
	{
		struct Class *q=p->classes;
		for(;q!=NULL;q=q->next)
		{
			if(freetext(q->teacher,s)==1)
			{
				printf("%-9s %-16s %-4d %-3f %-4d %-11s %-21s %-10s %-20s\n",q->CNo,q->major,q->num_enter,q->ave_of_age,\
				q->num_graduate,q->monitor,q->telephone,q->teacher,q->telephone_teacher);
				printf("1.�޸�  2.ɾ��  0.ȡ��\n");
				int n;scanf("%d",&n);
				switch(n){
					case 1:
						revise_class(q);
						break;
					case 2:
						delete_class(head,q);
						break;
					case 0:
						break;
				}  
				flag=1;
			}
		}
	}
	if(flag==0) printf("�޸ð༶��Ϣ\n");
}

/************************************************************
�������ƣ�seek_class4 
�������ܣ�����һ���������䣬����༶�����ڸ������ڵİ༶��Ϣ��
          ���ް༶��Ϣ��������޸ð༶��Ϣ�����ɽ���ģ����ѯ 
����������s1Ϊǰ���ʱ�䣬s2Ϊ�����ʱ�䣬headΪ�꼶�����ͷָ�� 
����ֵ���� 
*************************************************************/
void seek_class4(int s1,int s2,struct Grade *head)//�༶������ѯ 
{
	struct Grade *p=head;
	int flag;
	for(;p!=NULL;p=p->next)
	{
		struct Class *q=p->classes;
		for(;q!=NULL;q=q->next)
		{
			if(s1<=q->num_enter&&s2>=q->num_enter)
			{
				printf("%-9s %-16s %-4d %-3f %-4d %-11s %-21s %-10s %-20s\n",q->CNo,q->major,q->num_enter,q->ave_of_age,\
				q->num_graduate,q->monitor,q->telephone,q->teacher,q->telephone_teacher);
				printf("1.�޸�  2.ɾ��  0.ȡ��\n");
				int n;scanf("%d",&n);
				switch(n){
					case 1:
						revise_class(q);
						break;
					case 2:
						delete_class(head,q);
						break;
					case 0:
						break;
				}  
				flag=1;
			}
		}
	}
	if(flag==0) printf("�޸ð༶��Ϣ\n");
}

/************************************************************
�������ƣ�seek_class5
�������ܣ��༶��ѯ����ϲ�ѯ�������������4�����������İ༶��Ϣ��
          ��δ��ѯ���༶��Ϣ��������޸ð༶��Ϣ���� 
����������sΪ�༶��ţ�tΪרҵ���ƣ�rΪ������������
          s1��s2Ϊ�������� ��headΪ�꼶����ͷ���� 
����ֵ���� 
*************************************************************/
void seek_class5(char s[],char t[],char r[],int s1,int s2,struct Grade *head)//��ϲ�ѯ 
{
	struct Grade *p=head;
	int flag;
	for(;p!=NULL;p=p->next)
	{
		struct Class *q=p->classes;
		for(;q!=NULL;q=q->next)
		{
			if(freetext(q->CNo,s)==1&&freetext(q->major,t)==1&&freetext(q->teacher,r)==1&&s1<=q->num_enter&&s2>=q->num_enter)
			{
				printf("%-9s %-16s %-4d %-3f %-4d %-11s %-21s %-10s %-20s\n",q->CNo,q->major,q->num_enter,q->ave_of_age,\
				q->num_graduate,q->monitor,q->telephone,q->teacher,q->telephone_teacher);
				printf("1.�޸�  2.ɾ��  0.ȡ��\n");
				int n;scanf("%d",&n);
				switch(n){
					case 1:
						revise_class(q);
						break;
					case 2:
						delete_class(head,q);
						break;
					case 0:
						break;
				}  
				flag=1;
			}
		}
	}
	if(flag==0) printf("�޸ð༶��Ϣ\n");
}

/************************************************************
�������ƣ�seek_student1
�������ܣ�����ѧ��������ѯѧ����Ϣ������ѯ�������ѧ����Ϣ��
          ����������޸�ѧ����Ϣ�� ���ɽ���ģ����ѯ 
����������sΪѧ��������headΪ�༶����ͷ���� 
����ֵ���� 
*************************************************************/
void seek_student1(char s[],struct Grade *head)//ѧ��������ѯ 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	{
		struct Class *q=p->classes;
		for(;q!=NULL;q=q->next)
		{
			struct Student *t=q->student;
			for(;t!=NULL;t=t->next)
			{
				if(strstr(t->name,s)!=0)
				{
					printf("%-11s %-11s %-1c %-11s %-11s %-21s %-4.1f %-2d %-11s\n",t->SNo,t->name,t->sex,t->native_place,t->year,t->telephone,t->score,t->graduate,t->graduate_place);
					printf("1.�޸�  2.ɾ��  0.ȡ��\n");
					int n;scanf("%d",&n);
					switch(n){
						case 1:
							revise_student(t);
							break;
						case 2:
							delete_student(head,t);
							break;
						case 0:
							break;
					} 
					flag=1;
				}
			}
		}
	}
	if(flag==0) printf("�޸�ѧ����Ϣ");
}
 
/************************************************************
�������ƣ�seek_student2
�������ܣ����ݱ�ҵ��˾��ѯѧ����Ϣ������ѯ�����ѧ����Ϣ��
          ����������޸�ѧ����Ϣ������ģ����ѯ 
����������sΪ��ҵ��˾���ƣ�headΪ�꼶����ͷָ��
����ֵ���� 
*************************************************************/
void seek_student2(char s[],struct Grade *head)//ѧ����ҵȥ���ѯ 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	{
		struct Class *q=p->classes;
		for(;q!=NULL;q=q->next)
		{
			struct Student *t=q->student;
			for(;t!=NULL;t=t->next)
			{
				if(freetext(t->graduate_place,s)==1)
				{
					printf("%-11s %-11s %-1c %-11s %-11s %-21s %-4.1f %-2d %-11s\n",t->SNo,t->name,t->sex,t->native_place,t->year,t->telephone,t->score,t->graduate,t->graduate_place);
					printf("1.�޸�  2.ɾ��  0.ȡ��\n");
					int n;scanf("%d",&n);
					switch(n){
						case 1:
							revise_student(t);
							break;
						case 2:
							delete_student(head,t);
							break;
						case 0:
							break;
					} 
					flag=1;
				}
			}
		}
	}
	if(flag==0) printf("�޸�ѧ����Ϣ");
}

/************************************************************
�������ƣ�seek_student3
�������ܣ������Ƿ��ѯѧ����Ϣ������ѯ�����ѧ����Ϣ��
          ����������޸�ѧ����Ϣ��
����������nΪ�Ƿ��ҵ��ʶ��0��δ��ҵ��1����ҵ����headΪ�꼶����ͷָ��
����ֵ���� 
*************************************************************/
void seek_student3(int n,struct Grade *head)//ѧ���Ƿ��ҵ��ѯ 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	{
		struct Class *q=p->classes;
		for(;q!=NULL;q=q->next)
		{
			struct Student *t=q->student;
			for(;t!=NULL;t=t->next)
			{
				if(t->graduate==n)
				{
					printf("%-11s %-11s %-1c %-11s %-11s %-21s %-4.1f %-2d %-11s\n",t->SNo,t->name,t->sex,t->native_place,t->year,t->telephone,t->score,t->graduate,t->graduate_place);
					printf("1.�޸�  2.ɾ��  0.ȡ��\n");
					int n;scanf("%d",&n);
					switch(n){
						case 1:
							revise_student(t);
							break;
						case 2:
							delete_student(head,t);
							break;
						case 0:
							break;
					} 
					flag=1;
				}
			}
		}
	}
	if(flag==0) printf("�޸�ѧ����Ϣ");
}

/************************************************************
�������ƣ�seek_student4
�������ܣ�������ѧʱ���ѯѧ����Ϣ������ѯ�����ѧ����Ϣ��
          ����������޸�ѧ����Ϣ�� 
����������s1Ϊǰ���ʱ�䣬s2Ϊ�����ʱ�䣬headΪ�꼶����ͷָ��
����ֵ���� 
*************************************************************/
void seek_student4(int s1,int s2,struct Grade *head)//ѧ����ѧʱ���ѯ 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	{
		if(p->time<s1||p->time>s2) continue;
		struct Class *q=p->classes;
		for(;q!=NULL;q=q->next)
		{
			struct Student *t=q->student;
			for(;t!=NULL;t=t->next)
			{
				printf("%-11s %-11s %-1c %-11s %-11s %-21s %-4.1f %-2d %-11s\n",t->SNo,t->name,t->sex,t->native_place,t->year,t->telephone,t->score,t->graduate,t->graduate_place);
				printf("1.�޸�  2.ɾ��  0.ȡ��\n");
					int n;scanf("%d",&n);
					switch(n){
						case 1:
							revise_student(t);
							break;
						case 2:
							delete_student(head,t);
							break;
						case 0:
							break;
					} 
				flag=1;
			}
		}
	}
	if(flag==0) printf("�޸�ѧ����Ϣ");
}

/************************************************************
�������ƣ�seek_student5
�������ܣ�����ѧ��רҵ��ѯѧ����Ϣ������ѯ�����ѧ����Ϣ��
          ����������޸�ѧ����Ϣ������ģ����ѯ 
����������sΪרҵ���ƣ�headΪ�꼶����ͷָ�� 
����ֵ���� 
*************************************************************/
void seek_student5(char s[],struct Grade *head)//ѧ��רҵ��ѯ 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	{
		struct Class *q=p->classes;
		for(;q!=NULL;q=q->next)
		{
			if(freetext(q->major,s)==0) continue; 
			struct Student *t=q->student;
			for(;t!=NULL;t=t->next)
			{
				printf("%-11s %-11s %-1c %-11s %-11s %-21s %-4.1f %-2d %-11s\n",t->SNo,t->name,t->sex,t->native_place,t->year,t->telephone,t->score,t->graduate,t->graduate_place);
				printf("1.�޸�  2.ɾ��  0.ȡ��\n");
					int n;scanf("%d",&n);
					switch(n){
						case 1:
							revise_student(t);
							break;
						case 2:
							delete_student(head,t);
							break;
						case 0:
							break;
					} 
				flag=1;
			}
		}
	}
	if(flag==0) printf("�޸�ѧ����Ϣ");
}

/************************************************************
�������ƣ�seek_student6
�������ܣ�����ѧ�������ѯѧ����Ϣ������ѯ�����ѧ����Ϣ��
          ����������޸�ѧ����Ϣ������ģ����ѯ 
����������s1Ϊ�����������ޣ�s2Ϊ�����������ޣ�headΪ�꼶����ͷָ�� 
����ֵ���� 
*************************************************************/
void seek_student6(int s1,int s2,struct Grade *head)//ѧ�������ѯ 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	{
		struct Class *q=p->classes;
		for(;q!=NULL;q=q->next)
		{
			struct Student *t=q->student;
			for(;t!=NULL;t=t->next)
			{
				int n=p->time-char_to_int(t->year);
				if(s1<=n&&s2>=n)
				{
					printf("%-11s %-11s %-1c %-11s %-11s %-21s %-4.1f %-2d %-11s\n",t->SNo,t->name,t->sex,t->native_place,t->year,t->telephone,t->score,t->graduate,t->graduate_place);
				    printf("1.�޸�  2.ɾ��  0.ȡ��\n");
					int n;scanf("%d",&n);
					switch(n){
						case 1:
							revise_student(t);
							break;
						case 2:
							delete_student(head,t);
							break;
						case 0:
							break;
					} 
					flag=1;
				 } 
			}
		}
	}
	if(flag==0) printf("�޸�ѧ����Ϣ");
}

/************************************************************
�������ƣ�seek_student2
�������ܣ�ѧ����ѯ��ϲ�ѯ����������6�������������ѧ����Ϣ��
          ����������޸�ѧ����Ϣ�� 
����������s2��ѧ��������y1,y2:����;s1:רҵ��t1,t2:��ѧʱ�䣻
          n:�Ƿ��ҵ�� s3:��ҵȥ�� head���꼶����ͷָ�� 
����ֵ���� 
*************************************************************/
// 
void seek_student7(char s2[],int y1,int y2,char s1[],int t1,int t2,int n,char s3[],struct Grade *head)//ѧ����ϲ�ѯ 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	{
		if(p->time<t1||p->time>t2) continue;
		struct Class *q=p->classes;
		for(;q!=NULL;q=q->next)
		{
			if(freetext(q->major,s1)==0) continue; 
			struct Student *t=q->student;
			for(;t!=NULL;t=t->next)
			{
				int m=p->time-char_to_int(t->year);
				if(t->graduate==n&&y1<=m&&y2>=m&&freetext(t->graduate_place,s3)==1&&freetext(t->name,s2)==1)
				{
					printf("%-11s %-11s %-1c %-11s %-11s %-21s %-4.1f %-2d %-11s\n",t->SNo,t->name,t->sex,t->native_place,t->year,t->telephone,t->score,t->graduate,t->graduate_place);
					printf("1.�޸�  2.ɾ��  0.ȡ��\n");
					int n;scanf("%d",&n);
					switch(n){
						case 1:
							revise_student(t);
							break;
						case 2:
							delete_student(head,t);
							break;
						case 0:
							break;
					} 
					flag=1;
				}
			}
		}
	}
	if(flag==0) printf("�޸�ѧ����Ϣ");
}

/************************************************************
�������ƣ�change_grade 
�������ܣ����������꼶��������Ϣ���������� 
����������p1��p2Ϊָ���轻���꼶��Ϣ�������༶��ָ�� 
����ֵ���� 
*************************************************************/
void change_grade(struct Grade *ph1,struct Grade *ph2)//�����꼶��Ϣ 
{
	struct Grade *p1=ph1,*p2=ph2;
	struct Class *q;
	char s[10],t[20];
	int n;
	strcpy(s,p1->CSNo);strcpy(p1->CSNo,p2->CSNo);strcpy(p2->CSNo,s);
	strcpy(s,p1->name);strcpy(p1->name,p2->name);strcpy(p2->name,s);
	strcpy(s,p1->name_chairman);strcpy(p1->name_chairman,p2->name_chairman);strcpy(p2->name_chairman,s);
	strcpy(t,p1->telephone);strcpy(p1->telephone,p2->telephone);strcpy(p2->telephone,t);
	n=p1->time;p1->time=p2->time;p2->time=n;
	n=p1->num_enter;p1->num_enter=p2->num_enter;p2->num_enter=n;
	n=p1->num_graduate;p1->num_graduate=p2->num_graduate;p2->num_graduate=n;
	q=p1->classes;p1->classes=p2->classes;p2->classes=q;
 }

/************************************************************
�������ƣ�change_class
�������ܣ����������༶����Ϣ���������� 
����������ph1��ph2Ϊָ���轻����Ϣ�İ༶��ָ�� 
����ֵ���� 
*************************************************************/
void change_class(struct Class *ph1,struct Class *ph2)//�����༶��Ϣ 
{
	struct Class *p1=ph1,*p2=ph2;
	struct Student *q;
	char s[8],t[15],r[20],u[10];
	int n;
	float m;
	strcpy(s,p1->CNo);strcpy(p1->CNo,p2->CNo);strcpy(p2->CNo,s);
	strcpy(t,p1->major);strcpy(p1->major,p2->major);strcpy(p2->major,t);
	strcpy(r,p1->telephone_teacher);strcpy(p1->telephone_teacher,p2->telephone_teacher);strcpy(p2->telephone_teacher,r);
	strcpy(r,p1->telephone);strcpy(p1->telephone,p2->telephone);strcpy(p2->telephone,r);
	strcpy(u,p1->monitor);strcpy(p1->monitor,p2->monitor);strcpy(p2->monitor,u);
	strcpy(u,p1->teacher);strcpy(p1->teacher,p2->teacher);strcpy(p2->teacher,u);
	n=p1->num_enter;p1->num_enter=p2->num_enter;p2->num_enter=n;
	n=p1->num_graduate;p1->num_graduate=p2->num_graduate;p2->num_graduate=n;
	m=p1->ave_of_age;p1->ave_of_age=p2->ave_of_age;p2->ave_of_age=m;
	q=p1->student;p1->student=p2->student;p2->student=q;
 }

/************************************************************
�������ƣ�change_student
�������ܣ���������ѧ������Ϣ���������� 
����������ph1��ph2Ϊָ���轻����Ϣ������ѧ����ָ�� 
����ֵ���� 
*************************************************************/
void change_student(struct Student *ph1,struct Student *ph2)//����ѧ����Ϣ
{
	struct Student *p1=ph1,*p2=ph2;
	char s,t[10],r[20];
	int n;
	float m;
	s=p1->sex;p1->sex=p2->sex;p2->sex=s;
	strcpy(t,p1->SNo);strcpy(p1->SNo,p2->SNo);strcpy(p2->SNo,t);
	strcpy(t,p1->name);strcpy(p1->name,p2->name);strcpy(p2->name,t);
	strcpy(t,p1->native_place);strcpy(p1->native_place,p2->native_place);strcpy(p2->native_place,t);
	strcpy(t,p1->year);strcpy(p1->year,p2->year);strcpy(p2->year,t);
	strcpy(t,p1->graduate_place);strcpy(p1->graduate_place,p2->graduate_place);strcpy(p2->graduate_place,t); 
	strcpy(r,p1->telephone);strcpy(p1->telephone,p2->telephone);strcpy(p1->telephone,r);
	n=p1->graduate;p1->graduate=p2->graduate;p2->graduate=n;
	m=p1->score;p1->score=p2->score;p2->score=m; 
}


/************************************************************
�������ƣ�insert_grade
�������ܣ�����һ���꼶��Ϣ���꼶������ 
�����������꼶����ͷָ��head 
����ֵ���µ��꼶����ͷָ�� 
*************************************************************/
Grade * insert_grade(Grade * head)  //�꼶���� 
{
	Grade *p;
	p= (Grade *)malloc(sizeof(Grade));
	printf("�������꼶��ţ���ѧʱ�䣬��ѧ��������ҵ�������꼶����Ա����������Ա�绰���꼶ѧ������ϯ\n");
	scanf("%s%d%d%d%s%s%s",p->CSNo,&p->time,&p->num_enter,&p->num_graduate,p->name,p->telephone,p->name_chairman);
	p->next=head;
	return p;
}

/************************************************************
�������ƣ�insert_class
�������ܣ�����һ���༶��Ϣ��ָ���꼶�� 
����������ָ��ָ�����꼶��ָ��head 
����ֵ�����꼶�µİ༶�����ͷָ�� 
*************************************************************/
Class * insert_class(struct Grade *head)//�༶����
{
	struct Class *p;
	p=(Class *)malloc(sizeof(Class));
	printf("������༶��ţ�רҵ���ƣ���ѧ����,��ѧƽ�����䣬��ҵ����,�೤�������೤��ϵ�绰����������������������ϵ�绰\n");
	scanf("%s %s %d %f %d %s %s %s %s",p->CNo,p->major,&p->num_enter,&p->ave_of_age,&p->num_graduate,p->monitor,p->telephone,p->teacher,p->telephone_teacher);
    p->next=head->classes;
    head->classes=p;
	return p;
}

/************************************************************
�������ƣ�insert_student 
�������ܣ�����һ��ѧ����Ϣ��ָ���༶�� 
����������ָ��ָ���༶�ĵ�ָ�� 
����ֵ���ð༶�µ�ѧ������ͷָ�� 
*************************************************************/
Student * insert_student(struct Class *head)//ѧ������ 
{
	struct Student *tail;
	tail=(struct Student *)malloc(sizeof(struct Student));
	printf("������ѧ�ţ��������Ա𣬼��ᣬ�������£���ϵ�绰����ѧ�������Ƿ��ҵ����ҵȥ��\n");
	scanf("%s %s %c %s %s %s %f %d %s",tail->SNo,tail->name,&tail->sex,tail->native_place,tail->year,tail->telephone,&tail->score,&tail->graduate,tail->graduate_place);
	tail->next=head->student;
	head->student=tail;
	return tail;
}

//�꼶ͳ�� 
/************************************************************
�������ƣ�count1
�������ܣ�ָ�����޵��꼶ͳ��
��������������xΪǰ���ʱ�䣬yΪ�����ʱ�䣬headΪ�꼶����ͷָ�� 
����ֵ���� 
*************************************************************/
void count1(int x,int y,struct Grade *head)
{
	int count=0;
	int flag=0;
	struct Grade *p=head;
	for(;p!=NULL;p=p->next)
	{
		if(p->time>=x&&p->time<=y)
		{
			flag=1;
			struct Class *q=p->classes;
			for(;q!=NULL;q=q->next) count++;
			printf("�꼶���\t����\t��ѧ����\t��ҵ����\tδ��ҵ����\n");
			printf("%s\t\t%d\t%d\t\t%d\t\t%d\n",p->CSNo,count,p->num_enter,\
			p->num_graduate,p->num_enter-p->num_graduate);
			count=0;
		}	
	}
	if(flag==0) printf("���ڼ����꼶��Ϣ��");
}

/************************************************************
�������ƣ�count1
�������ܣ���ָ�����޵��꼶ͳ��
����������headΪ�꼶����ͷָ�� 
����ֵ���� 
*************************************************************/
void count1(struct Grade *head)
{
	int count=0;
	int flag=0;
	struct Grade *p=head;
	for(;p!=NULL;p=p->next)
	{
		flag=1;
		struct Class *q=p->classes;
		for(;q!=NULL;q=q->next) count++;
		printf("�꼶���\t����\t��ѧ����\t��ҵ����\tδ��ҵ����\n");
		printf("%s\t\t%d\t%d\t\t%d\t\t%d\n",p->CSNo,count,p->num_enter,\
		p->num_graduate,p->num_enter-p->num_graduate);
		count=0;	
	}
	if(flag==0) printf("���ڼ����꼶��Ϣ��");
}

/************************************************************
�������ƣ�count_class1
�������ܣ�ͳ��ָ�����޸��༶δ��ҵ����
��������������xΪǰ���ʱ�䣬yΪ�����ʱ��
����ֵ���� 
************************************************************/ 
void count_class1(int x,int y,struct Grade *head)
{
	struct Grade *p=head;
	struct Count *headp=NULL,*tail=NULL; 
	for(;p!=NULL;p=p->next)//����һ���꼶�������� 
	{
		if(p->time>=x&&p->time<=y&&p->classes!=NULL)//��ָ���������Ҹ��꼶���а༶��Ϣʱ 
		{
			struct Class *q;
			q=p->classes;
			headp=(struct Count*)malloc(sizeof(struct Count));
		    headp->num=q->num_enter-q->num_graduate;strcpy(headp->CNO,q->CNo);//���༶�����δ��ҵ�����洢���µ������� 
		    tail=headp;//tailָ��ͷָ�� 
			for(q=q->next;q!=NULL;q=q->next)//������������ 
			{ 
				tail->next=(struct Count*)malloc(sizeof(struct Count));
				tail=tail->next;
				tail->num=q->num_enter-q->num_graduate;strcpy(tail->CNO,q->CNo);
			}
			tail->next=NULL;
			p=p->next;
			break; 
		 } 		
	}
	
	for(;p!=NULL;p=p->next)//������������ 
	{
		if(p->time>=x&&p->time<=y&&p->classes!=NULL)//��ָ���������Ҹ��꼶���а༶��Ϣʱ 
		{
			struct Class *q;
			q=p->classes;
			for(q=q->next;q!=NULL;q=q->next) 
			{ 
				tail->next=(struct Count*)malloc(sizeof(struct Count));
				tail=tail->next;
				tail->num=q->num_enter-q->num_graduate;strcpy(tail->CNO,q->CNo);
			}
			tail->next=NULL;
		 } 		
	}
	tail=headp;
	sort1(tail);
	tail=headp;
	for(;tail!=NULL;tail=tail->next)
	printf("�༶%s  δ��ҵ������%d\n",tail->CNO,tail->num);
}

/************************************************************
�������ƣ�count_class1
�������ܣ�ͳ����ָ�����޸��༶δ��ҵ����
������������ 
����ֵ���� 
************************************************************/ 
//ͳ�Ƹ��༶δ��ҵ����
void count_class2(struct Grade *head)
{
	struct Grade *p=head;
	struct Count *headp=NULL,*tail=NULL; 
	for(;p!=NULL;p=p->next)//����һ���꼶�������� 
	{
		if(p->classes!=NULL)//���꼶���а༶��Ϣʱ 
		{
			struct Class *q;
			q=p->classes;
			headp=(struct Count*)malloc(sizeof(struct Count));
		    headp->num=q->num_enter-q->num_graduate;strcpy(headp->CNO,q->CNo);//���༶�����δ��ҵ�����洢���µ������� 
		    tail=headp;//tailָ��ͷָ�� 
			for(q=q->next;q!=NULL;q=q->next)//������������ 
			{ 
				tail->next=(struct Count*)malloc(sizeof(struct Count));
				tail=tail->next;
				tail->num=q->num_enter-q->num_graduate;strcpy(tail->CNO,q->CNo);
			}
			tail->next=NULL;
			p=p->next;
			break; 
		 } 		
	}
	
	for(;p!=NULL;p=p->next)//������������ 
	{
		if(p->classes!=NULL)//���꼶���а༶��Ϣʱ 
		{
			struct Class *q;
			q=p->classes;
			for(q=q->next;q!=NULL;q=q->next) 
			{ 
				tail->next=(struct Count*)malloc(sizeof(struct Count));
				tail=tail->next;
				tail->num=q->num_enter-q->num_graduate;strcpy(tail->CNO,q->CNo);
			}
			tail->next=NULL;
		 } 		
	}
	tail=headp;
	sort1(tail);
	tail=headp;
	for(;tail!=NULL;tail=tail->next)
	printf("�༶%s  δ��ҵ������%d",tail->CNO,tail->num);
}

/************************************************************
�������ƣ�brith
�������ܣ�ͳ��ָ�������ڸ����������
����������s1Ϊǰ���ʱ�䣬s2Ϊ�����ʱ�� ��headΪ�꼶����ͷָ�� 
����ֵ���� 
************************************************************/ 
int brith(int s1,int s2,struct Grade *head)
{
	struct Grade *p=head;
	for(int n=s1;n<=s2;n++)
	{
		int count=0;
		for(;p!=NULL;p=p->next)
	    {
		if(p->classes!=NULL)
		{
			struct Class *q=p->classes;
			for(;q!=NULL;q=q->next)
			{
				struct Student *t=q->student;
		        for(;t!=NULL;t=t->next)
		        {	
		        	if(n==char_to_int(t->year)) count++;	
				}
			}
		}
    	}
	    printf("%d�������ѧ������%d\n",n,count);
	    p=head;
	}	
 }

/************************************************************
�������ƣ�arrange 
�������ܣ�����ѧ����ҵȥ������ ���ϲ�ͬһ��˾��Ա 
����������ѧ����ҵ����ͷָ�� 
����ֵ���� 
************************************************************/ 
void arrange(struct Count2 *head)
{
	struct Count2 *p1,*p2,*p3;
	for(p1=head;p1!=NULL;p1=p1->next)
	{
		for(p2=p1;p2->next!=NULL;p2=p2->next)
		{
			p3=p2->next;
			if(strcmp(p1->graduate_place,p3->graduate_place)==0)
			{
				p2->next=p3->next;
				p1->num++;
			}
		}
	}
}

/************************************************************
�������ƣ�count_student1 
�������ܣ�ͳ��ָ�����ޱ�ҵ��ĳ��ҵ�������������ҵ������
          ��Ӧ��������ҵ���ƿ�ģ����ѯ 
��������������xΪǰ���ʱ�䣬yΪ�����ʱ�䣬headΪ�꼶����ͷ
          ָ�룬sΪͳ�ƵĹ�˾ 
����ֵ���� 
************************************************************/  
void count_student1(int x,int y,struct Grade *head,char s[])
{	
	struct Grade *p=head;
	struct Count2 *headp=NULL,*tail;
	for(;p!=NULL;p=p->next)
	{
		if(p->time>=x&&p->time<=y&&p->classes!=NULL)//������һ���꼶������ 
		{
			struct Class *q=p->classes;
			
			headp=(struct Count2*)malloc(sizeof(struct Count2));//����ͷָ�� 
            strcpy(headp->graduate_place,q->student->graduate_place);
            headp->num=1;
            tail=headp;//tailָ��ͷָ��	
			for(;q!=NULL&&q->student!=NULL;q=q->next)//�����༶ 
			{
				struct Student *t=q->student;
				for(t=t->next;t!=NULL;t=t->next)//����ѧ�� 
				{
					tail->next=(struct Count2*)malloc(sizeof(struct Count2));
					tail=tail->next;
					strcpy(tail->graduate_place,t->graduate_place);
					tail->num=1;
				}
			}
			tail->next=NULL;
			p=p->next;
			break;
		}
	}
	
	for(;p!=NULL;p=p->next)
	{
		if(p->time>=x&&p->time<=y&&p->classes!=NULL)
		{
			struct Class *q=p->classes;
			for(;q!=NULL&&q->student!=NULL;q=q->next)
			{
				struct Student *t=q->student;
				for(;t!=NULL;t=t->next)
				{
					tail->next=(struct Count2*)malloc(sizeof(struct Count2));
					tail=tail->next;
					strcpy(tail->graduate_place,t->graduate_place);
					tail->num=1;
				}
			}	
		}
	tail->next=NULL;	
	}

	tail=headp;
	arrange(tail);
	tail=headp;
	sort2(tail);
	tail=headp;
	int flag=0;
	for(;tail!=NULL;tail=tail->next)
		if(strstr(tail->graduate_place,s)!=0)
		{
			printf("%s:  %d\n",tail->graduate_place,tail->num);flag=1;
		}
	if(flag==0) printf("���ڼ��ޱ�ҵѧ��ȥ���ù�˾\n"); 
}

/************************************************************
�������ƣ�count_student2
�������ܣ�ͳ����ָ�����ޱ�ҵ��ĳ��ҵ������
����������headΪ�꼶����ͷָ�룬sΪ��ҵ�� 
����ֵ���� 
************************************************************/ 
void count_student2(struct Grade *head,char s[])
{
	struct Grade *p=head;
	struct Count2 *headp=NULL,*tail;
	for(;p!=NULL;p=p->next)
	{
		if(p->classes!=NULL)//������һ���꼶������ 
		{
			struct Class *q=p->classes;
			for(;q->student==NULL;q=q->next);//ʹqָ���һ����ѧ����Ϣ�İ༶����	
			headp=(struct Count2*)malloc(sizeof(struct Count2));//����ͷָ�� 
            strcpy(headp->graduate_place,q->student->graduate_place);
            headp->num=1;
            tail=headp;//tailָ��ͷָ��
			for(;q!=NULL;q=q->next)//�����༶ 
			{
				struct Student *t=q->student;
				for(t=t->next;t!=NULL;t=t->next)//����ѧ�� 
				{
					tail->next=(struct Count2*)malloc(sizeof(struct Count2));
					tail=tail->next;
					strcpy(tail->graduate_place,t->graduate_place);
					tail->num=1;
				}
			}
			tail->next=NULL;
			p=p->next;
			break;
		}
	}
	
	for(;p!=NULL;p=p->next)
	{
		if(p->classes!=NULL)
		{
			struct Class *q=p->classes;
			for(;q!=NULL;q=q->next)
			{
				struct Student *t=q->student;
				for(;t!=NULL;t=t->next)
				{
					tail->next=(struct Count2*)malloc(sizeof(struct Count2));
					tail=tail->next;
					strcpy(tail->graduate_place,t->graduate_place);
					tail->num=1;
				}
			}	
		}
	tail->next=NULL;	
	}
	tail=headp;
	arrange(tail);
	tail=headp;
	sort2(tail);
	tail=headp;
	int flag=0;
	for(;tail!=NULL;tail=tail->next)
		if(freetext(tail->graduate_place,s)==1)
		{
			printf("%s:  %d\n",tail->graduate_place,tail->num);flag=1;
		}
	if(flag==0) printf("���ڼ��ޱ�ҵѧ��ȥ���ù�˾"); 
}

/************************************************************
�������ƣ�_add 
�������ܣ����빦���ܺ��� 
�����������꼶�������ͷָ��head���꼶ϵͳ�������˵��ı�ʶflag 
����ֵ���� 
************************************************************/ 
void _add(int *flag,struct Grade **head)
{
	add: 
		printf("\n\t\t\t------��������ϵͳ------\n\n");
		printf("1.�����꼶��Ϣ    2.����༶��Ϣ    3.����ѧ����Ϣ    0.ȡ��\n"); 
		int y;scanf("%d",&y);
		switch(y){
			case 1:
				(*head)=insert_grade(*head);
				sort_grade(*head);
				printf("�Ƿ����������Ϣ��(0:�� 1:��)��\n");
				int n1;scanf("%d",&n1);
				if(n1==0) goto add;
				else *flag=1;
				break; 
			case 2:
			    printf("������Ҫ����༶���꼶��ţ�");
			    char s1[10];scanf("%s",s1);
			    struct Grade *q;
			    q=*head;
			    for(;q!=NULL;q=q->next)
			    {
			    	if(strcmp(q->CSNo,s1)==0)
			    	{
			    		q->classes=insert_class(q);
			    		break;
					}
				}
				sort_class(q->classes);
			    printf("�Ƿ����������Ϣ��(0:�� 1:��)��\n");
				int n2;scanf("%d",&n2);
				if(n2==0) goto add; 
			    else *flag=1;
				break; 
			case 3:
			    printf("������Ҫ����ѧ���İ༶��ţ�");
			    char s2[8];scanf("%s",s2);
			    struct Grade *p;
			    p=*head;
			    for(;p!=NULL;p=p->next)
			    {
			    	struct Class *q=p->classes;
			    	for(;q!=NULL;q=q->next)
			    	{
			    		if(strcmp(q->CNo,s2)==0)
			    		{
			    			q->student=insert_student(q);
			    			sort_student(q->student);
			    			break;
						}
					}	
				}	
			    printf("�Ƿ����������Ϣ��(0:�� 1:��)��\n");
				int n3;scanf("%d",&n3);
				if(n3==0) goto add;
			    else *flag=1;
				break; 
			case 0:
			    *flag=1;break;
            }
}

/************************************************************
�������ƣ�_seek
�������ܣ���ѯ���������� 
����������headΪ�꼶����ͷָ�룬flagΪ�����������ı�ʶ 
����ֵ���� 
************************************************************/ 
void _seek(int *flag,Grade *head)
{
	seek:
		printf("\n\t\t\t------���ݲ�ѯϵͳ------\n\n"); 
		printf("1.�꼶��ѯ     2.�༶��ѯ    3.ѧ����ѯ   0.ȡ��\n");
		int x;scanf("%d",&x);
		switch(x){
			case 1:
				seek1:
				printf("��ѯ��ʽ��\n");
				printf("1.�꼶���    2.��ѧʱ��    3.��ѧ����   4.��ϲ�ѯ    0.����\n");
				int x;scanf("%d",&x);
				switch(x){
					case 1:
						printf("�������꼶��ţ�");
						char s[10];
						scanf("%s",s); 
						seek_grade1(s,head);
						printf("1.������ѯ    0.����\n");
						int i1;scanf("%d",&i1);
						switch(i1){
							case 1:goto seek1;
							case 0:goto seek;
						}
						break;
					case 2:
						printf("��������ѧʱ�����䣺"); 
						int n1,n2;
						scanf("%d %d",&n1,&n2);
						seek_grade2(n1,n2,head);
						printf("1.������ѯ    0.����\n");
						int i2;scanf("%d",&i2);
						switch(i1){
							case 1:goto seek1;
							case 0:goto seek;
						}
						break;
					case 3:
					    printf("��������ѧ�������䣺");
					    int n3,n4;
						scanf("%d %d",&n3,&n4);
						seek_grade3(n3,n4,head);
						printf("1.������ѯ    0.����\n");
						int i3;scanf("%d",&i3);
						switch(i3){
							case 1:goto seek1;
							case 0:goto seek;
						}
						break;
					case 4:
						printf("�밴˳�������꼶��š���ѧʱ�����䡢��ѧ�������䣺\n");
						char t[10];
						int m1,m2,m3,m4;
						scanf("%s %d %d %d %d",t,&m1,&m2,&m3,&m4);
						seek_grade4(t,m1,m2,m3,m4,head);
						printf("1.������ѯ    0.����\n");
						int i4;scanf("%d",&i4);
						switch(i4){
							case 1:goto seek1;
							case 0:goto seek;
						}
						break;
					case 0:
					    goto seek; 
				}
				break;
			case 2:
				seek2: 
			    printf("��ѯ��ʽ��\n");
				printf("1.�༶���      2.רҵ        3.����\
				      \n4.����������    5.��ϲ�ѯ    0.����\n");
				int y;scanf("%d",&y);
				switch(y){
					case 1:
					    printf("������༶��ţ�");
						char s[8];scanf("%s",s);
						seek_class1(s,head);
						printf("1.������ѯ    0.����\n");
						int i1;scanf("%d",&i1);
						switch(i1){
							case 1:goto seek2;
							case 0:goto seek;
						}
						break;
					case 2:
						printf("������רҵ���ƣ�");
						char t[15];scanf("%s",t);
						seek_class2(t,head);
						printf("1.������ѯ    0.����\n");
						int i2;scanf("%d",&i2);
						switch(i2){
							case 1:goto seek2;
							case 0:goto seek;
						}						
						break;
					case 3:
						printf("������༶������");
						int n1,n2;scanf("%d%d",&n1,&n2);
						seek_class4(n1,n2,head); 
						printf("1.������ѯ    0.����\n");
						int i3;scanf("%d",&i3);
						switch(i3){
							case 1:goto seek2;
							case 0:goto seek;
						}
						break;
					case 4:
						printf("�����������������");
						char r[10];scanf("%s",r);
						seek_class3(r,head);
						printf("1.������ѯ    0.����\n");
						int i4;scanf("%d",&i4);
						switch(i4){
							case 1:goto seek2;
							case 0:goto seek;
						}
						break;
					case 5:
						printf("�밴˳������༶��š�רҵ���ơ��༶����������������\n");
						char v1[8],v2[15],v3[20];
						int m1,m2;
						scanf("%s %s %d %d %s",v1,v2,&m1,&m2,v3);
						seek_class5(v1,v2,v3,m1,m2,head);
						printf("1.������ѯ    0.����\n");
						int i5;scanf("%d",&i5);
						switch(i5){
							case 1:goto seek2;
							case 0:goto seek;
						}
						break;
					case 0:
						goto seek;
				}
				break;
			case 3:
				seek3:
			    printf("��ѯ��ʽ��\n");
				printf("1.����      2.רҵ      3.��ѧʱ��   4.����\
				      \n5.�Ƿ��ҵ  6.��ҵȥ��  7.��ϲ�ѯ   0.����\n");
				int z;scanf("%d",&z);
				switch(z){
					case 1:
						printf("������ѧ��������");
						char s1[10];scanf("%s",s1);
						seek_student1(s1,head);
						printf("1.������ѯ    0.����\n");
						int i1;scanf("%d",&i1);
						switch(i1){
							case 1:goto seek3;
							case 0:goto seek;
						}
						break;
					case 2:
					    printf("������ѧ��רҵ��");
						char s2[15];scanf("%s",s2);
						seek_student5(s2,head);
						printf("1.������ѯ    0.����\n");
						int i2;scanf("%d",&i2);
						switch(i2){
							case 1:goto seek3;
							case 0:goto seek;
						}
						break;
					case 3:
					    printf("������ѧ����ѧʱ�䣺");
						int n1,n4;scanf("%d%d",&n1,&n4);
						seek_student4(n1,n4,head);
						printf("1.������ѯ    0.����\n");
						int i3;scanf("%d",&i3);
						switch(i3){
							case 1:goto seek3;
							case 0:goto seek;
						}
						break;
					case 4:
					    printf("������ѧ�����䣺");
						int n2,n5;scanf("%d%d",&n2,&n5);
						seek_student6(n2,n5,head);
						printf("1.������ѯ    0.����\n");
						int i4;scanf("%d",&i4);
						switch(i4){
							case 1:goto seek3;
							case 0:goto seek;
						}
						break;
					case 5:
					    printf("��ѡ�������ҵ\δ��ҵѧ����0��δ��ҵ�� 1����ҵ����"); 
						int n3;scanf("%d",&n3);
						seek_student3(n3,head);
						printf("1.������ѯ    0.����\n");
						int i5;scanf("%d",&i5);
						switch(i5){
							case 1:goto seek3;
							case 0:goto seek;
						}
						break;
					case 6:
					    printf("��������ҵ���ƣ�");
						char s3[10];scanf("%s",s3);
						seek_student2(s3,head);
						printf("1.������ѯ    0.����\n");
						int i6;scanf("%d",&i6);
						switch(i6){
							case 1:goto seek3;
							case 0:goto seek;
						}
						break;
					case 7:
					    printf("�밴˳������ѧ��������רҵ����ѧʱ�䡢���䡢�Ƿ��ҵ����ҵȥ��\n");
						char t1[10],t2[15],t3[10];
						int m1,m2,m3,m4,m5;
						scanf("%s %s %d %d %d %d %d %s",s1,s2,&m1,&m2,&m3,&m4,&m5,s3);
						seek_student7(s1,m3,m4,s2,m1,m2,m5,s3,head);
						printf("1.������ѯ    0.����\n");
						int i7;scanf("%d",&i7);
						switch(i7){
							case 1:goto seek3;
							case 0:goto seek;
						}
						break;
					case 0:
					    goto seek; 
				}
				break;
			case 0:
			    *flag=1;
				break;	
	} 
} 

/************************************************************
�������ƣ�_census
�������ܣ�ͳ�ƹ��������� 
����������headΪ�꼶����ͷָ�룬flagΪ�������˵��ı�ʶ 
����ֵ���� 
************************************************************/ 	
void _census(int *flag,struct Grade *head)
{
	census:
	    printf("\n\t\t\t------����ͳ��ϵͳ------\n\n");
	   	printf("1.�꼶ͳ��    2.�༶ͳ��    3.ѧ��ͳ��    0.ȡ��\n");
	   	int z;scanf("%d",&z);
		switch(z){
			case 1:
				census1:
				printf("������Ҫͳ�Ƶ����ݣ�\n");
				printf("�꼶ͳ�ư�����������ѧ��������ҵ������δ��ҵ����\n");
				printf("���������ޣ�"); 
				int y1,y2;scanf("%d%d",&y1,&y2);
				printf("��ѡ������ʽ��\n");
				printf("1.�꼶���   2.��ѧ����   3.δ��ҵ����\n");
				int j1;scanf("%d",&j1);
				switch(j1){
					case 1:
							sort_grade(head);break;
					case 2:
							sort3(head);break;
					case 3:
							sort4(head);break;
					} 
				count1(y1,y2,head);
				printf("�Ƿ����ͳ�ƣ�(0:�� 1����)\n");
				int m1;scanf("%d",&m1);
				if(m1==0) goto census1;
				else goto census;
				break;
			case 2:
				census2:
			    printf("�༶ͳ��ֻ֧��ͳ�Ƹ���δ��ҵ��������\n"); 
			    printf("���������ޣ�");
				int t1,t2;
				scanf("%d%d",&t1,&t2);
				count_class1(t1,t2,head);
				printf("�Ƿ����ͳ�ƣ�(0:�� 1����)\n");
				int m2;scanf("%d",&m2);
				if(m2==0) goto census2;
				else goto census; 
			    break;
			case 3:
				census3:
				printf("������Ҫͳ�Ƶ����ݣ�\n");
			    printf("1.��ҵȥ��    2.����ʱ��    0.����\n");
			    int n3;scanf("%d",&n3);
			    switch(n3){
			    	case 1:
			    		printf("���������޼�Ҫ��ѯ�Ĺ�˾��\n");
						int r1,r2;char s[10];
						scanf("%d%d%s",&r1,&r2,s);
						count_student1(r1,r2,head,s);
					    break;
			    	case 2:
			    		printf("���������ʱ�����䣺");
			    		int r3,r4;
			    		scanf("%d%d",&r3,&r4);
			    		brith(r3,r4,head);
					    break;
			    	case 0:
			    		goto census;
				}
			    printf("�Ƿ����ͳ�ƣ�(0:�� 1����)\n");
				int m3;scanf("%d",&m3);
				if(m3==0) goto census3;
				else goto census;
				break;
			case 0:			    
				*flag=1;	break; 
		}
}

/************************************************************
�������ƣ�creat_student
�������ܣ�����ѧ������ 
����������ѧ���������ͷָ��head 
����ֵ���� 
************************************************************/ 
void creat_student(struct Student **headp)
{
	struct Student *tail=NULL,*p;
	char ch;
	tail=(struct Student *)malloc(sizeof(struct Student));
	printf("������ѧ�ţ��������Ա𣬼��ᣬ�������£���ϵ�绰����ѧ�������Ƿ��ҵ����ҵȥ��\n");
	scanf("%s %s %c %s %s %s %f %d %s",tail->SNo,tail->name,&tail->sex,tail->native_place,tail->year,tail->telephone,&tail->score,&tail->graduate,tail->graduate_place);
	getchar();//��ȡ���з�	 
		printf("�Ƿ��������ѧ����Ϣ��\n");
		ch=getchar();getchar();
		p=tail;
		while(ch=='y'||ch=='Y')
		{
			p->next=(struct Student *)malloc(sizeof(struct Student));
		    p=p->next;
		    printf("������ѧ�ţ��������Ա𣬼��ᣬ�������£���ϵ�绰����ѧ�������Ƿ��ҵ����ҵȥ��\n");
		    scanf("%s %s %c %s %s %s %f %d %s",p->SNo,p->name,&p->sex,p->native_place,p->year,p->telephone,&p->score,&p->graduate,p->graduate_place);
		    getchar();
		    printf("�Ƿ��������ѧ����Ϣ��\n");
		    ch=getchar();getchar(); 
	}
	p->next=NULL;
	*headp=tail;
 }

/************************************************************
�������ƣ�creat_class
�������ܣ���������ʮ�ֽ�������༶���� 
�����������༶�������ͷָ�� 
����ֵ���� 
************************************************************/ 
void creat_class(struct Class **head)
{
	struct Class *hp=NULL,*p;
	char ch;
    loop:
    	p=(struct Class *)malloc(sizeof(struct Class));
    	printf("������༶��ţ�רҵ���ƣ���ѧ����,��ѧƽ�����䣬��ҵ����,�೤�������೤��ϵ�绰����������������������ϵ�绰\n");
		scanf("%s %s %d %f %d %s %s %s %s",p->CNo,p->major,&p->num_enter,&p->ave_of_age,&p->num_graduate,p->monitor,p->telephone,p->teacher,p->telephone_teacher);
		getchar();
		p->student=NULL;
		p->next=hp;
		hp=p;
		printf("�Ƿ���������༶��Ϣ��\n");
		ch=getchar();getchar();
		if(ch=='y'||ch=='Y') goto loop;//������һ���༶��Ϣ�� 
		(*head)=hp;//headָ���´����İ༶��Ϣ��
		printf("�Ƿ񴴽�ѧ����Ϣ��\n");
		ch=getchar();getchar();
		if(ch=='y'||ch=='Y')
		{	
			p=(*head); //pָ��༶��Ϣ������ͷ 
		    while(p!=NULL)
		   {
		   	   printf("�༶%s��ѧ����Ϣ��\n",p->CNo); 
			   struct Student * pcrs;
			   creat_student(&pcrs);//����ѧ����Ϣ�� 
			   p->student=pcrs;
			   p=p->next;
		   } 	
		}			
 } 

/************************************************************
�������ƣ�creat_grade
�������ܣ��������������꼶���� 
�����������꼶�������ͷָ��head 
����ֵ���� 
************************************************************/ 
void creat_grade(struct Grade **head)
{
	struct Grade *hp=NULL,*p;
	char ch;
    loop:
    	p=(struct Grade *)malloc(sizeof(struct Grade));
    	printf("�������꼶��ţ���ѧʱ�䣬��ѧ��������ҵ�������꼶����Ա����������Ա�绰���꼶ѧ������ϯ\n");
		scanf("%s %d %d %d %s %s %s",p->CSNo,&p->time,&p->num_enter,&p->num_graduate,p->name,p->telephone,p->name_chairman);
		getchar();
		p->classes=NULL;
		p->next=hp;
		hp=p;
		printf("�Ƿ���������꼶��Ϣ��\n");
		ch=getchar();getchar();
		if(ch=='y'||ch=='Y') goto loop;//������һ���༶��Ϣ�� 
		(*head)=hp;//headָ���´����İ༶��Ϣ��
		printf("�Ƿ񴴽��༶��Ϣ��\n");
		ch=getchar();getchar();
		if(ch=='y'||ch=='Y')
		{
			p=(*head); //pָ��༶��Ϣ������ͷ 
		    while(p!=NULL)
		   {
		   	   printf("%s��İ༶��Ϣ��:\n",p->CSNo);
			   struct Class * pcrs;
			   creat_class(&pcrs);//����ѧ����Ϣ�� 
			   p->classes=pcrs;
			   p=p->next;
		   } 	
		}			
}

/************************************************************
�������ƣ�load_list
�������ܣ�¼�빦�ܺ��������ļ������ݶ�������ʮ�ֽ������� 
������������ 
����ֵ���꼶����ͷָ�� 
************************************************************/ 
Grade * load_list(void)           //��ȡ���ܺ���
{
	FILE *in1, *in2, *in3;
	Grade *hp = NULL, *p1,*p2;
	Class *pc1,*pc2;
	Student *ps1,*ps2;
	if ((in1 = fopen("D://c����//grade.dat", "rb")) == NULL)
	{
		printf("�ļ�D://c����//grade.dat��ʧ�ܣ�\n");
		exit(1);
	}
	if ((in2 = fopen("D://c����//class.dat", "rb")) == NULL)
	{
		printf("�ļ�D://c����//class.dat��ʧ�ܣ�\n");
		exit(1);
	}
	if ((in3 = fopen("D://c����//student.dat", "rb")) == NULL)
	{
		printf("�ļ�D://c����//student��ʧ�ܣ�\n");
		exit(1);
	}
	while (!feof(in1))
	{
		p1 = (Grade *)malloc(sizeof(Grade));
		fread(p1, sizeof(Grade), 1, in1);
		p1->classes = NULL;
		if (hp == NULL)
		{
			hp = p1;
			p2 = p1;
		}
		else
		{
			p2->next = p1;
			p2 = p1;
		}
	}
	p2->next = NULL;
	while (!feof(in2))
	{
		pc1 = (Class *)malloc(sizeof(Class));
		fread(pc1, sizeof(Class), 1, in2);
		pc1->student = NULL;
		p2 = hp;
		while (p2 != NULL)
		{
			if (char_to_int(p2->CSNo)==char_to_int(pc1->CNo))
			{
				if (p2->classes == NULL)
				{
					p2->classes = pc1;
					pc2 = pc1;
				}
				else
				{
					pc2->next = pc1;
					pc2 = pc1;
				}
				break;
			}
			else
			p2 = p2->next;
		}
	}
	while (!feof(in3))
	{
		ps1 = (Student *)malloc(sizeof(Student));
		fread(ps1, sizeof(Student), 1, in3);
		p1 = hp;
		while (p1 != NULL)
		{
			pc1 = p1->classes;
			while (pc1)
			{
				if (char_to_int(pc1->CNo)==char_to_int(ps1->SNo))
				{
					if (pc1->student== NULL)
					{
						pc1->student= ps1;
						ps2 = ps1;
					}
					else
					{
						ps2->next = ps1;
						ps2 = ps1;
					}
					ps1 = (Student *)malloc(sizeof(Student));
					fread(ps1, sizeof(Student), 1, in3);
				}
				else
				    pc1 = pc1->next;
			}
			p1 = p1->next;
		}
	}
	fclose(in1);
	fclose(in2);
	fclose(in3);
	return hp;
}

/************************************************************
�������ƣ�save
�������ܣ��������Ļ��޸Ĺ��������ʮ�ֽ�������洢����Ӧ�������ļ� 
�����������꼶����ͷָ�� 
����ֵ���� 
************************************************************/ 
void save(struct Grade *head)
{
	FILE *out1,*out2,*out3;
	Grade *p=head;
	out1=fopen("D://c����//grade.dat","w+");
	out2=fopen("D://c����//class.dat","w+");
	out3=fopen("D://c����//student.dat","w+");
	while(p!=NULL){
		Class *pc=p->classes;
		fwrite(p,sizeof(Grade),1,out1);
		while(pc!=NULL){
			Student *ps=pc->student;
			fwrite(pc,sizeof(Class),1,out2);
			while(ps!=NULL){
				fwrite(ps,sizeof(Student),1,out3);
				ps=ps->next;
			}
			pc=pc->next;
		}
		p=p->next;
	}
	fclose(out1);
	fclose(out2);
	fclose(out3);
}

int main()
{
	struct Grade *head=NULL;
	//head=load_list();
	loop:
	printf("\t\t\t------ѧ������ϵͳ------\n");
	printf("\t\t\t------ 1 ���ݲ�ѯ ------\n");
	printf("\t\t\t------ 2 ����������-----\n");
	printf("\t\t\t------ 3 ����ͳ�� ------\n");
	printf("\t\t\t------ 0 ���� ----------\n"); 
	int n;
	int flag=0;
	scanf("%d",&n);
	switch(n){
		case 1:
	        _seek(&flag,head);//��ѯϵͳ���� 
	        if(flag==1){
	 	    flag=0;goto loop;//�������˵� 
	        }
			break;
		case 2:
			_add(&flag,&head);//����ϵͳ���� 
			if(flag==1){
	 	    flag=0;goto loop;//�������˵� 
	        }
			break;
	    case 3:
	       _census(&flag,head);//ͳ�ƺ������˵� 
	        if(flag==1){
	 	    flag=0;goto loop;//�������˵� 
	        }
			break;
		case 0:
			break;
    }
    save(head);//������浽�ļ��� 
    return 0;
}
