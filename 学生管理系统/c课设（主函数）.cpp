#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void change_grade(struct Grade *ph1,struct Grade *ph2);
void change_class(struct Class *ph1,struct Class *ph2);
void change_student(struct Student *ph1,struct Student *ph2);//交换学生信息

//学生信息结构 
struct Student{
	char SNo[10];//学号 
	char name[10];//学生姓名 
	char sex;//性别 （1：男；2：女） 
	char native_place[10];//籍贯 
	char year[10];//出生年月 
	char telephone[20];//联系电话 
	float score;//入学成绩 
	int graduate;//是否毕业（0：没毕业； 1：毕业） 
	char graduate_place[10];//毕业去向 
	
	struct Student *next;
};

//班级信息结构 
struct Class{
	char CNo[8];//班级编号 
	char major[15];//专业名称 
	int num_enter;//入学人数 
	float ave_of_age;//入学平均年龄 
	int num_graduate;//毕业人数 
	char monitor[10];//班长姓名 
	char telephone[20];//班长电话 
	char teacher[10];//班主任姓名 
	char telephone_teacher[20];//班主任电话 
	struct Student *student;//学生信息 
	
	struct Class *next;
};

//年级信息结构 
struct Grade{
	char CSNo[10];//年级编号 
	int time;//入学时间 
	int num_enter;//入学人数 
	int num_graduate;//毕业人数 
	char name[10];//年级辅导员姓名 
	char telephone[20];//辅导员电话 
	char name_chairman[10];//学生会主席 
	struct Class *classes; //班级信息 
	
	struct Grade *next;
};

struct Count{
	char CNO[8];//班级编号 
	int num; //未毕业人数
	  
	struct Count *next;
};//用来保存班级的未毕业人数的结构 

struct Count2{
	char graduate_place[10];//企业名 
	int num;//学生名 
	
	struct Count2 *next;
};//保存学生毕业去向的结构 

int char_to_int(char s[])//提取出生日期前四位并转化为int型 
{
	int m=0;
	for(int i=0;i<4;i++)
	{
		m=m*10+(s[i]-'0'); 	
	}
	return m;
}

int char_to_int2(char s[])//将数组转化为数字 
{
	int sum=0;
	for(int n=0;s[n]!='\0';n++)
	sum=sum*10+(s[n]-'0');
	return sum;
 }

/************************************************************
函数名称：freetext
函数功能：模糊查询 
函数参数：参数s2为查询内容，参数s1为需与s2比较的内容 
返回值：若 s2为s1子串，返回1，否则返回0 
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
函数名称：sort1
函数功能：班级统计中根据未毕业人数对班级排序
函数参数：Cout结构指针 
返回值：无 
*************************************************************/ 
void sort1(struct Count *head)
{
	int count=0,i,j,t;
	char s[8];
	struct Count *p1=head,*p2;
	for(;p1!=NULL;p1=p1->next) count++;//计算链表元素数量 
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
函数名称：sort2 
函数功能：学生统计中根据某企业的人数进行排序 
函数参数：Count2结构指针 
返回值：无 
*************************************************************/
void sort2(struct Count2 *head)
{
	int count=0,i,j,t;
	char s[10];
	struct Count2 *p1=head,*p2;
	for(;p1!=NULL;p1=p1->next) count++;//计算链表元素数量 
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
函数名称：sort_grade 
函数功能：根据年级编号对年级信息表排序 
函数参数：年级表头指针head 
返回值：无 
*************************************************************/
void sort_grade(struct Grade *head)
{
	int count=0,i,j;
	struct Grade *p1=head,*p2;
	
	for(;p1!=NULL;p1=p1->next) count++;//计算链表元素数量 
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
函数名称：sort_class 
函数功能：根据班级编号对某年级班级信息表排序 
函数参数：班级表头指针head 
返回值：无 
*************************************************************/
void sort_class(struct Class *head)
{
	int count=0,i,j;
	struct Class *p1=head,*p2;
	for(;p1!=NULL;p1=p1->next) count++;//计算链表元素数量 
    for(i=0,p1=head;i<count-1;i++,p1=p1->next);
    {
    	for(j=i+1,p2=p1->next;j<count-1;j++,p2=p2->next)
    	if(char_to_int2(p1->CNo)>char_to_int2(p2->CNo))
    	change_class(p1,p2);
    }
}

/************************************************************
函数名称：sort_student
函数功能：根据学生编号对某班级学生信息表排序 
函数参数：学生信息表头指针head 
返回值：无 
*************************************************************/
void sort_student(struct Student *head)
{
	int count=0,i,j;
	struct Student *p1=head,*p2;
	for(;p1!=NULL;p1=p1->next) count++;//计算链表元素数量 
    for(i=0,p1=head;i<count-1;i++,p1=p1->next);
    {
    	for(j=i+1,p2=p1->next;j<count-1;j++,p2=p2->next)
    	if(char_to_int2(p1->SNo)>char_to_int2(p2->SNo))
    	change_student(p1,p2);
    }
}

/************************************************************
函数名称：sort3
函数功能：根据年级入学人数对年级表排序 
函数参数：年级信息表头指针head 
返回值：无 
*************************************************************/
void sort3(struct Grade *head)
{
	int count=0,i,j;
	struct Grade *p1=head,*p2;
	for(;p1!=NULL;p1=p1->next) count++;//计算链表元素数量 
    for(i=0,p1=head;i<count-1;i++,p1=p1->next);
    {
    	for(j=i+1,p2=p1->next;j<count-1;j++,p2=p2->next)
    	if(p1->num_enter<p2->num_enter)
    	change_grade(p1,p2);
    }
 }

/************************************************************
函数名称：sort4
函数功能：根据年级未毕业人数对年级排序 
函数参数：年级信息表头指针head 
返回值：无 
*************************************************************/
void sort4(struct Grade *head)
{
	int count=0,i,j;
	struct Grade *p1=head,*p2;
	for(;p1!=NULL;p1=p1->next) count++;//计算链表元素数量 
    for(i=0,p1=head;i<count-1;i++,p1=p1->next);
    {
    	for(j=i+1,p2=p1->next;j<count-1;j++,p2=p2->next)
    	if((p1->num_enter-p1->num_graduate)<(p2->num_enter-p2->num_graduate))
    	change_grade(p1,p2);
    }
 }
 
 /************************************************************
函数名称：revise_grade
函数功能：修改某条年级信息记录
函数参数：指向需修改的年级记录的指针 
返回值：无 
*************************************************************/
void revise_grade(struct Grade *head)
{
	struct Grade *p=head;
	printf("请输入年级编号，入学时间，入学人数，毕业人数，年级辅导员姓名，辅导员电话，年级学生会主席\n");
	scanf("%s %d %d %d %s %s %s",p->CSNo,&p->time,&p->num_enter,\
	&p->num_graduate,p->name,p->telephone,p->name_chairman);
	getchar();
}

/************************************************************
函数名称：revise_class
函数功能：对某条班级信息记录进行修改 
函数参数：指向需修改的班级记录的指针 
返回值：无 
*************************************************************/
void revise_class(struct Class *head)
{
		struct Class *q=head;
			printf("请输入班级编号，专业名称，入学人数,入学平均年龄，毕业人数,班长姓名，班长联系电话，班主任姓名，班主任联系电话\n");
		    scanf("%s %s %d %f %d %s %s %s %s",q->CNo,q->major,&q->num_enter,&q->ave_of_age,\
			&q->num_graduate,q->monitor,q->telephone,q->teacher,q->telephone_teacher);
		    getchar();
}

/************************************************************
函数名称：revise_student
函数功能：对某条学生信息记录进行修改 
函数参数：指向需修改的学生的指针 
返回值：无 
*************************************************************/
void revise_student(struct Student *head)//学生修改 
{
	struct Student *t=head;
	printf("请输入学号，姓名，性别，籍贯，出生年月，联系电话，入学分数，是否毕业，毕业去向\n");
	scanf("%s %s %c %s %s %s %f %d %s",t->SNo,t->name,&t->sex,t->native_place,\
		t->year,t->telephone,&t->score,&t->graduate,t->graduate_place);
	getchar();
}

/************************************************************
函数名称：delete_grade
函数功能：删除某条年级信息 
函数参数：年级信息表头指针head和指向需删除的年级信息记录的指针 
返回值：无 
*************************************************************/
void delete_grade(struct Grade *head,Grade *ph)//删除年级信息 
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
函数名称：delete_class
函数功能：删除某条班级信息 
函数参数：年级信息表头指针和指向需删除的班级信息记录的指针 
返回值：无 
*************************************************************/  
void delete_class(struct Grade *head,Class *ph)//删除班级信息 
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
函数名称：delete_student
函数功能：删除某条学生信息 
函数参数：年级信息表头指针和指向需删除的学生信息记录的指针 
返回值：无 
*************************************************************/
void delete_student(struct Grade *head,Student *ph)//删除学生信息 
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
函数名称：seek_grade1 
函数功能：根据年级编号查询年级信息，若查询到输出查询结果，否则输出“无该年级信息” 
           可进行模糊查询 
函数参数：数组s为需查询的编号内容，head为年级链表头指针 
返回值：无 
*************************************************************/
void seek_grade1(char s[],struct Grade *head)//年级编号查询 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	if(strstr(p->CSNo,s)!=0)
	{
		printf("%-11s %-10d %-4d %-4d %-11s %-21s %-11s\n",p->CSNo,p->time,p->num_enter,p->num_graduate,p->name,p->telephone,p->name_chairman);
		printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该年级信息\n");
 }

/************************************************************
函数名称：seek_grade2
函数功能：输入时间期限，输出在该期限内的年级信息 ，若该期间
          无年级信息输出“无该年级信息” 
函数参数：s1为靠前的时间，s2为靠后的时间，head为年级链表头指针 
返回值：无 
*************************************************************/
void seek_grade2(int s1,int s2,struct Grade *head)//入学时间查询 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	if(s1<=p->time&&s2>=p->time)
	{
		printf("%11s %10d %4d %4d %11s %21s %11s\n",p->CSNo,p->time,p->num_enter,p->num_graduate,p->name,p->telephone,p->name_chairman);
		printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该年级信息\n");
}

/************************************************************
函数名称：seek_grade3
函数功能：输入人数区间，输出入学人数在该区间的年级信息 ，
          若该区间无年级信息输出“无该年级信息” 
函数参数：s1为较小的人数，s2为较大的人数，head为年级链表头指针 
返回值：无 
*************************************************************/
void seek_grade3(int s1,int s2,struct Grade *head)//入学人数查询 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	if(s1<=p->num_enter&&s2>=p->num_enter)
	{
		printf("%11s %10d %4d %4d %11s %21s %11s\n",p->CSNo,p->time,p->num_enter,p->num_graduate,p->name,p->telephone,p->name_chairman);
		printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该年级信息\n");
}

/************************************************************
函数名称：seek_grade 
函数功能：年级查询的组合查询，输出满足上面三个函数条件的年级
          信息，若无年级信息输出“无该年级信息” 
函数参数：数组s为年级编号，y1，y2为时间期限，s1，s2为人数区间 
返回值：无 
*************************************************************/
void seek_grade4(char s[],int y1,int y2,int s1,int s2,struct Grade *head)//组合查询 
{
	struct Grade *p=head;
	int flag=0;
	for(;p!=NULL;p=p->next)
	if(freetext(p->CSNo,s)==1&&y1<=p->num_enter&&y2>=p->num_enter&&s1<=p->num_enter&&s2>=p->num_enter)
	{
		printf("%11s %10d %4d %4d %11s %21s %11s\n",p->CSNo,p->time,p->num_enter,p->num_graduate,p->name,p->telephone,p->name_chairman);
		printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该年级信息\n");
}

/************************************************************
函数名称：seek_class1
函数功能：根据班级编号查询班级信息，若查询到输出查询结果，
          否则输出“无该班级信息”，可进行模糊查询 
函数参数：s为 班级编号内容，head为年级链表头指针 
返回值：无 
*************************************************************/
void seek_class1(char s[],struct Grade *head)//班级编号查询 
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
				printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该班级信息\n");
}

/************************************************************
函数名称：seek_class2
函数功能：根据专业名称查询年级信息，若查询到输出年级信息，
          否则输出“无该班级信息”，可进行模糊查询 
函数参数：s为专业内容，head为年级链表头指针 
返回值：无 
*************************************************************/
void seek_class2(char s[],struct Grade *head)//班级专业查询查询 
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
				printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该班级信息\n");
}

/************************************************************
函数名称：seek_class3
函数功能：根据班主任姓名查询班级信息，若查询到输出班级信息，
          否则输出“无该班级信息”，可进行模糊查询 
函数参数：s为班主任姓名，head为年级链表头指针 
返回值：无 
*************************************************************/
void seek_class3(char s[],struct Grade *head)//班主任查询 
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
				printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该班级信息\n");
}

/************************************************************
函数名称：seek_class4 
函数功能：输入一个人数区间，输出班级人数在该区间内的班级信息，
          若无班级信息，输出“无该班级信息”，可进行模糊查询 
函数参数：s1为前面的时间，s2为后面的时间，head为年级链表的头指针 
返回值：无 
*************************************************************/
void seek_class4(int s1,int s2,struct Grade *head)//班级人数查询 
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
				printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该班级信息\n");
}

/************************************************************
函数名称：seek_class5
函数功能：班级查询的组合查询，输出满足上面4个函数条件的班级信息，
          若未查询到班级信息，输出“无该班级信息”； 
函数参数：s为班级编号，t为专业名称，r为班主任姓名，
          s1，s2为人数区间 ，head为年级链表头链表 
返回值：无 
*************************************************************/
void seek_class5(char s[],char t[],char r[],int s1,int s2,struct Grade *head)//组合查询 
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
				printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该班级信息\n");
}

/************************************************************
函数名称：seek_student1
函数功能：根据学生姓名查询学生信息，若查询到输出该学生信息，
          否则输出“无该学生信息” ，可进行模糊查询 
函数参数：s为学生姓名，head为班级链表头链表 
返回值：无 
*************************************************************/
void seek_student1(char s[],struct Grade *head)//学生姓名查询 
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
					printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该学生信息");
}
 
/************************************************************
函数名称：seek_student2
函数功能：根据毕业公司查询学生信息，若查询到输出学生信息，
          否则输出“无该学生信息”，可模糊查询 
函数参数：s为毕业公司名称，head为年级链表头指针
返回值：无 
*************************************************************/
void seek_student2(char s[],struct Grade *head)//学生毕业去向查询 
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
					printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该学生信息");
}

/************************************************************
函数名称：seek_student3
函数功能：根据是否查询学生信息，若查询到输出学生信息，
          否则输出“无该学生信息”
函数参数：n为是否毕业标识（0：未毕业。1：毕业），head为年级链表头指针
返回值：无 
*************************************************************/
void seek_student3(int n,struct Grade *head)//学生是否毕业查询 
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
					printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该学生信息");
}

/************************************************************
函数名称：seek_student4
函数功能：根据入学时间查询学生信息，若查询到输出学生信息，
          否则输出“无该学生信息” 
函数参数：s1为前面的时间，s2为后面的时间，head为年级链表头指针
返回值：无 
*************************************************************/
void seek_student4(int s1,int s2,struct Grade *head)//学生入学时间查询 
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
				printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该学生信息");
}

/************************************************************
函数名称：seek_student5
函数功能：根据学生专业查询学生信息，若查询到输出学生信息，
          否则输出“无该学生信息”，可模糊查询 
函数参数：s为专业名称，head为年级链表头指针 
返回值：无 
*************************************************************/
void seek_student5(char s[],struct Grade *head)//学生专业查询 
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
				printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该学生信息");
}

/************************************************************
函数名称：seek_student6
函数功能：根据学生年龄查询学生信息，若查询到输出学生信息，
          否则输出“无该学生信息”，可模糊查询 
函数参数：s1为年龄区间下限，s2为年龄区间上限，head为年级链表头指针 
返回值：无 
*************************************************************/
void seek_student6(int s1,int s2,struct Grade *head)//学生年龄查询 
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
				    printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该学生信息");
}

/************************************************************
函数名称：seek_student2
函数功能：学生查询组合查询，满足上面6个函数条件输出学生信息，
          否则输出“无该学生信息” 
函数参数：s2：学生姓名；y1,y2:年龄;s1:专业：t1,t2:入学时间；
          n:是否毕业； s3:毕业去向； head：年级链表头指针 
返回值：无 
*************************************************************/
// 
void seek_student7(char s2[],int y1,int y2,char s1[],int t1,int t2,int n,char s3[],struct Grade *head)//学生组合查询 
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
					printf("1.修改  2.删除  0.取消\n");
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
	if(flag==0) printf("无该学生信息");
}

/************************************************************
函数名称：change_grade 
函数功能：交换两个年级的所有信息，用于排序 
函数参数：p1，p2为指向需交换年级信息的两个班级的指针 
返回值：无 
*************************************************************/
void change_grade(struct Grade *ph1,struct Grade *ph2)//交换年级信息 
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
函数名称：change_class
函数功能：交换两个班级的信息，用于排序 
函数参数：ph1，ph2为指向需交换信息的班级的指针 
返回值：无 
*************************************************************/
void change_class(struct Class *ph1,struct Class *ph2)//交换班级信息 
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
函数名称：change_student
函数功能：交换两个学生的信息，用于排序 
函数参数：ph1，ph2为指向需交换信息的两个学生的指针 
返回值：无 
*************************************************************/
void change_student(struct Student *ph1,struct Student *ph2)//交换学生信息
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
函数名称：insert_grade
函数功能：插入一条年级信息到年级链表里 
函数参数：年级链表头指针head 
返回值：新的年级链表头指针 
*************************************************************/
Grade * insert_grade(Grade * head)  //年级插入 
{
	Grade *p;
	p= (Grade *)malloc(sizeof(Grade));
	printf("请输入年级编号，入学时间，入学人数，毕业人数，年级辅导员姓名，辅导员电话，年级学生会主席\n");
	scanf("%s%d%d%d%s%s%s",p->CSNo,&p->time,&p->num_enter,&p->num_graduate,p->name,p->telephone,p->name_chairman);
	p->next=head;
	return p;
}

/************************************************************
函数名称：insert_class
函数功能：插入一条班级信息到指定年级中 
函数参数：指向指定的年级的指针head 
返回值：该年级下的班级链表的头指针 
*************************************************************/
Class * insert_class(struct Grade *head)//班级插入
{
	struct Class *p;
	p=(Class *)malloc(sizeof(Class));
	printf("请输入班级编号，专业名称，入学人数,入学平均年龄，毕业人数,班长姓名，班长联系电话，班主任姓名，班主任联系电话\n");
	scanf("%s %s %d %f %d %s %s %s %s",p->CNo,p->major,&p->num_enter,&p->ave_of_age,&p->num_graduate,p->monitor,p->telephone,p->teacher,p->telephone_teacher);
    p->next=head->classes;
    head->classes=p;
	return p;
}

/************************************************************
函数名称：insert_student 
函数功能：插入一条学生信息到指定班级中 
函数参数：指向指定班级的的指针 
返回值：该班级下的学生链表头指针 
*************************************************************/
Student * insert_student(struct Class *head)//学生插入 
{
	struct Student *tail;
	tail=(struct Student *)malloc(sizeof(struct Student));
	printf("请输入学号，姓名，性别，籍贯，出生年月，联系电话，入学分数，是否毕业，毕业去向\n");
	scanf("%s %s %c %s %s %s %f %d %s",tail->SNo,tail->name,&tail->sex,tail->native_place,tail->year,tail->telephone,&tail->score,&tail->graduate,tail->graduate_place);
	tail->next=head->student;
	head->student=tail;
	return tail;
}

//年级统计 
/************************************************************
函数名称：count1
函数功能：指定期限的年级统计
函数参数：参数x为前面的时间，y为后面的时间，head为年级链表头指针 
返回值：无 
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
			printf("年级编号\t班数\t入学人数\t毕业人数\t未毕业人数\n");
			printf("%s\t\t%d\t%d\t\t%d\t\t%d\n",p->CSNo,count,p->num_enter,\
			p->num_graduate,p->num_enter-p->num_graduate);
			count=0;
		}	
	}
	if(flag==0) printf("该期间无年级信息！");
}

/************************************************************
函数名称：count1
函数功能：无指定期限的年级统计
函数参数：head为年级链表头指针 
返回值：无 
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
		printf("年级编号\t班数\t入学人数\t毕业人数\t未毕业人数\n");
		printf("%s\t\t%d\t%d\t\t%d\t\t%d\n",p->CSNo,count,p->num_enter,\
		p->num_graduate,p->num_enter-p->num_graduate);
		count=0;	
	}
	if(flag==0) printf("该期间无年级信息！");
}

/************************************************************
函数名称：count_class1
函数功能：统计指定期限各班级未毕业人数
函数参数：参数x为前面的时间，y为后面的时间
返回值：无 
************************************************************/ 
void count_class1(int x,int y,struct Grade *head)
{
	struct Grade *p=head;
	struct Count *headp=NULL,*tail=NULL; 
	for(;p!=NULL;p=p->next)//将第一个年级存入链表 
	{
		if(p->time>=x&&p->time<=y&&p->classes!=NULL)//在指定期限内且该年级中有班级信息时 
		{
			struct Class *q;
			q=p->classes;
			headp=(struct Count*)malloc(sizeof(struct Count));
		    headp->num=q->num_enter-q->num_graduate;strcpy(headp->CNO,q->CNo);//将班级编号与未毕业人数存储在新的链表中 
		    tail=headp;//tail指向头指针 
			for(q=q->next;q!=NULL;q=q->next)//继续建立链表 
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
	
	for(;p!=NULL;p=p->next)//建立后续链表 
	{
		if(p->time>=x&&p->time<=y&&p->classes!=NULL)//在指定期限内且该年级中有班级信息时 
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
	printf("班级%s  未毕业人数：%d\n",tail->CNO,tail->num);
}

/************************************************************
函数名称：count_class1
函数功能：统计无指定期限各班级未毕业人数
函数参数：无 
返回值：无 
************************************************************/ 
//统计各班级未毕业人数
void count_class2(struct Grade *head)
{
	struct Grade *p=head;
	struct Count *headp=NULL,*tail=NULL; 
	for(;p!=NULL;p=p->next)//将第一个年级存入链表 
	{
		if(p->classes!=NULL)//该年级中有班级信息时 
		{
			struct Class *q;
			q=p->classes;
			headp=(struct Count*)malloc(sizeof(struct Count));
		    headp->num=q->num_enter-q->num_graduate;strcpy(headp->CNO,q->CNo);//将班级编号与未毕业人数存储在新的链表中 
		    tail=headp;//tail指向头指针 
			for(q=q->next;q!=NULL;q=q->next)//继续建立链表 
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
	
	for(;p!=NULL;p=p->next)//建立后续链表 
	{
		if(p->classes!=NULL)//该年级中有班级信息时 
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
	printf("班级%s  未毕业人数：%d",tail->CNO,tail->num);
}

/************************************************************
函数名称：brith
函数功能：统计指定期限内各年出生人数
函数参数：s1为前面的时间，s2为后面的时间 ，head为年级链表头指针 
返回值：无 
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
	    printf("%d年出生的学生数：%d\n",n,count);
	    p=head;
	}	
 }

/************************************************************
函数名称：arrange 
函数功能：整理学生毕业去向链表 ，合并同一公司人员 
函数参数：学生毕业链表头指针 
返回值：无 
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
函数名称：count_student1 
函数功能：统计指定期限毕业后到某企业的人数，输出企业名称与
          对应人数，企业名称可模糊查询 
函数参数：参数x为前面的时间，y为后面的时间，head为年级链表头
          指针，s为统计的公司 
返回值：无 
************************************************************/  
void count_student1(int x,int y,struct Grade *head,char s[])
{	
	struct Grade *p=head;
	struct Count2 *headp=NULL,*tail;
	for(;p!=NULL;p=p->next)
	{
		if(p->time>=x&&p->time<=y&&p->classes!=NULL)//建立第一个年级的链表 
		{
			struct Class *q=p->classes;
			
			headp=(struct Count2*)malloc(sizeof(struct Count2));//建立头指针 
            strcpy(headp->graduate_place,q->student->graduate_place);
            headp->num=1;
            tail=headp;//tail指向头指针	
			for(;q!=NULL&&q->student!=NULL;q=q->next)//遍历班级 
			{
				struct Student *t=q->student;
				for(t=t->next;t!=NULL;t=t->next)//遍历学生 
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
	if(flag==0) printf("该期间无毕业学生去往该公司\n"); 
}

/************************************************************
函数名称：count_student2
函数功能：统计无指定期限毕业后到某企业的人数
函数参数：head为年级链表头指针，s为企业名 
返回值：无 
************************************************************/ 
void count_student2(struct Grade *head,char s[])
{
	struct Grade *p=head;
	struct Count2 *headp=NULL,*tail;
	for(;p!=NULL;p=p->next)
	{
		if(p->classes!=NULL)//建立第一个年级的链表 
		{
			struct Class *q=p->classes;
			for(;q->student==NULL;q=q->next);//使q指向第一个有学生信息的班级链表	
			headp=(struct Count2*)malloc(sizeof(struct Count2));//建立头指针 
            strcpy(headp->graduate_place,q->student->graduate_place);
            headp->num=1;
            tail=headp;//tail指向头指针
			for(;q!=NULL;q=q->next)//遍历班级 
			{
				struct Student *t=q->student;
				for(t=t->next;t!=NULL;t=t->next)//遍历学生 
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
	if(flag==0) printf("该期间无毕业学生去往该公司"); 
}

/************************************************************
函数名称：_add 
函数功能：插入功能总函数 
函数参数：年级链表二级头指针head，年级系统返回主菜单的标识flag 
返回值：无 
************************************************************/ 
void _add(int *flag,struct Grade **head)
{
	add: 
		printf("\n\t\t\t------数据输入系统------\n\n");
		printf("1.插入年级信息    2.插入班级信息    3.插入学生信息    0.取消\n"); 
		int y;scanf("%d",&y);
		switch(y){
			case 1:
				(*head)=insert_grade(*head);
				sort_grade(*head);
				printf("是否继续插入信息？(0:是 1:否)：\n");
				int n1;scanf("%d",&n1);
				if(n1==0) goto add;
				else *flag=1;
				break; 
			case 2:
			    printf("请输入要插入班级的年级编号：");
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
			    printf("是否继续插入信息？(0:是 1:否)：\n");
				int n2;scanf("%d",&n2);
				if(n2==0) goto add; 
			    else *flag=1;
				break; 
			case 3:
			    printf("请输入要插入学生的班级编号：");
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
			    printf("是否继续插入信息？(0:是 1:否)：\n");
				int n3;scanf("%d",&n3);
				if(n3==0) goto add;
			    else *flag=1;
				break; 
			case 0:
			    *flag=1;break;
            }
}

/************************************************************
函数名称：_seek
函数功能：查询功能主函数 
函数参数：head为年级链表头指针，flag为返回主函数的标识 
返回值：无 
************************************************************/ 
void _seek(int *flag,Grade *head)
{
	seek:
		printf("\n\t\t\t------数据查询系统------\n\n"); 
		printf("1.年级查询     2.班级查询    3.学生查询   0.取消\n");
		int x;scanf("%d",&x);
		switch(x){
			case 1:
				seek1:
				printf("查询方式：\n");
				printf("1.年级编号    2.入学时间    3.入学人数   4.组合查询    0.返回\n");
				int x;scanf("%d",&x);
				switch(x){
					case 1:
						printf("请输入年级编号：");
						char s[10];
						scanf("%s",s); 
						seek_grade1(s,head);
						printf("1.继续查询    0.返回\n");
						int i1;scanf("%d",&i1);
						switch(i1){
							case 1:goto seek1;
							case 0:goto seek;
						}
						break;
					case 2:
						printf("请输入入学时间区间："); 
						int n1,n2;
						scanf("%d %d",&n1,&n2);
						seek_grade2(n1,n2,head);
						printf("1.继续查询    0.返回\n");
						int i2;scanf("%d",&i2);
						switch(i1){
							case 1:goto seek1;
							case 0:goto seek;
						}
						break;
					case 3:
					    printf("请输入入学人数区间：");
					    int n3,n4;
						scanf("%d %d",&n3,&n4);
						seek_grade3(n3,n4,head);
						printf("1.继续查询    0.返回\n");
						int i3;scanf("%d",&i3);
						switch(i3){
							case 1:goto seek1;
							case 0:goto seek;
						}
						break;
					case 4:
						printf("请按顺序输入年级编号、入学时间区间、入学人数区间：\n");
						char t[10];
						int m1,m2,m3,m4;
						scanf("%s %d %d %d %d",t,&m1,&m2,&m3,&m4);
						seek_grade4(t,m1,m2,m3,m4,head);
						printf("1.继续查询    0.返回\n");
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
			    printf("查询方式：\n");
				printf("1.班级编号      2.专业        3.人数\
				      \n4.班主任姓名    5.组合查询    0.返回\n");
				int y;scanf("%d",&y);
				switch(y){
					case 1:
					    printf("请输入班级编号：");
						char s[8];scanf("%s",s);
						seek_class1(s,head);
						printf("1.继续查询    0.返回\n");
						int i1;scanf("%d",&i1);
						switch(i1){
							case 1:goto seek2;
							case 0:goto seek;
						}
						break;
					case 2:
						printf("请输入专业名称：");
						char t[15];scanf("%s",t);
						seek_class2(t,head);
						printf("1.继续查询    0.返回\n");
						int i2;scanf("%d",&i2);
						switch(i2){
							case 1:goto seek2;
							case 0:goto seek;
						}						
						break;
					case 3:
						printf("请输入班级人数：");
						int n1,n2;scanf("%d%d",&n1,&n2);
						seek_class4(n1,n2,head); 
						printf("1.继续查询    0.返回\n");
						int i3;scanf("%d",&i3);
						switch(i3){
							case 1:goto seek2;
							case 0:goto seek;
						}
						break;
					case 4:
						printf("请输入班主任姓名：");
						char r[10];scanf("%s",r);
						seek_class3(r,head);
						printf("1.继续查询    0.返回\n");
						int i4;scanf("%d",&i4);
						switch(i4){
							case 1:goto seek2;
							case 0:goto seek;
						}
						break;
					case 5:
						printf("请按顺序输入班级编号、专业名称、班级人数、班主任姓名\n");
						char v1[8],v2[15],v3[20];
						int m1,m2;
						scanf("%s %s %d %d %s",v1,v2,&m1,&m2,v3);
						seek_class5(v1,v2,v3,m1,m2,head);
						printf("1.继续查询    0.返回\n");
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
			    printf("查询方式：\n");
				printf("1.姓名      2.专业      3.入学时间   4.年龄\
				      \n5.是否毕业  6.毕业去向  7.组合查询   0.返回\n");
				int z;scanf("%d",&z);
				switch(z){
					case 1:
						printf("请输入学生姓名：");
						char s1[10];scanf("%s",s1);
						seek_student1(s1,head);
						printf("1.继续查询    0.返回\n");
						int i1;scanf("%d",&i1);
						switch(i1){
							case 1:goto seek3;
							case 0:goto seek;
						}
						break;
					case 2:
					    printf("请输入学生专业：");
						char s2[15];scanf("%s",s2);
						seek_student5(s2,head);
						printf("1.继续查询    0.返回\n");
						int i2;scanf("%d",&i2);
						switch(i2){
							case 1:goto seek3;
							case 0:goto seek;
						}
						break;
					case 3:
					    printf("请输入学生入学时间：");
						int n1,n4;scanf("%d%d",&n1,&n4);
						seek_student4(n1,n4,head);
						printf("1.继续查询    0.返回\n");
						int i3;scanf("%d",&i3);
						switch(i3){
							case 1:goto seek3;
							case 0:goto seek;
						}
						break;
					case 4:
					    printf("请输入学生年龄：");
						int n2,n5;scanf("%d%d",&n2,&n5);
						seek_student6(n2,n5,head);
						printf("1.继续查询    0.返回\n");
						int i4;scanf("%d",&i4);
						switch(i4){
							case 1:goto seek3;
							case 0:goto seek;
						}
						break;
					case 5:
					    printf("请选择输出毕业\未毕业学生（0：未毕业； 1：毕业）："); 
						int n3;scanf("%d",&n3);
						seek_student3(n3,head);
						printf("1.继续查询    0.返回\n");
						int i5;scanf("%d",&i5);
						switch(i5){
							case 1:goto seek3;
							case 0:goto seek;
						}
						break;
					case 6:
					    printf("请输入企业名称：");
						char s3[10];scanf("%s",s3);
						seek_student2(s3,head);
						printf("1.继续查询    0.返回\n");
						int i6;scanf("%d",&i6);
						switch(i6){
							case 1:goto seek3;
							case 0:goto seek;
						}
						break;
					case 7:
					    printf("请按顺序输入学生姓名、专业、入学时间、年龄、是否毕业、毕业去向：\n");
						char t1[10],t2[15],t3[10];
						int m1,m2,m3,m4,m5;
						scanf("%s %s %d %d %d %d %d %s",s1,s2,&m1,&m2,&m3,&m4,&m5,s3);
						seek_student7(s1,m3,m4,s2,m1,m2,m5,s3,head);
						printf("1.继续查询    0.返回\n");
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
函数名称：_census
函数功能：统计功能主函数 
函数参数：head为年级链表头指针，flag为返回主菜单的标识 
返回值：无 
************************************************************/ 	
void _census(int *flag,struct Grade *head)
{
	census:
	    printf("\n\t\t\t------数据统计系统------\n\n");
	   	printf("1.年级统计    2.班级统计    3.学生统计    0.取消\n");
	   	int z;scanf("%d",&z);
		switch(z){
			case 1:
				census1:
				printf("请输入要统计的数据：\n");
				printf("年级统计包括班数、入学人数、毕业人数、未毕业人数\n");
				printf("请输入期限："); 
				int y1,y2;scanf("%d%d",&y1,&y2);
				printf("请选择排序方式：\n");
				printf("1.年级编号   2.入学人数   3.未毕业人数\n");
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
				printf("是否继续统计？(0:是 1：否)\n");
				int m1;scanf("%d",&m1);
				if(m1==0) goto census1;
				else goto census;
				break;
			case 2:
				census2:
			    printf("班级统计只支持统计各班未毕业人数功能\n"); 
			    printf("请输入期限：");
				int t1,t2;
				scanf("%d%d",&t1,&t2);
				count_class1(t1,t2,head);
				printf("是否继续统计？(0:是 1：否)\n");
				int m2;scanf("%d",&m2);
				if(m2==0) goto census2;
				else goto census; 
			    break;
			case 3:
				census3:
				printf("请输入要统计的数据：\n");
			    printf("1.毕业去向    2.出生时间    0.返回\n");
			    int n3;scanf("%d",&n3);
			    switch(n3){
			    	case 1:
			    		printf("请输入期限及要查询的公司：\n");
						int r1,r2;char s[10];
						scanf("%d%d%s",&r1,&r2,s);
						count_student1(r1,r2,head,s);
					    break;
			    	case 2:
			    		printf("请输入出生时间区间：");
			    		int r3,r4;
			    		scanf("%d%d",&r3,&r4);
			    		brith(r3,r4,head);
					    break;
			    	case 0:
			    		goto census;
				}
			    printf("是否继续统计？(0:是 1：否)\n");
				int m3;scanf("%d",&m3);
				if(m3==0) goto census3;
				else goto census;
				break;
			case 0:			    
				*flag=1;	break; 
		}
}

/************************************************************
函数名称：creat_student
函数功能：创建学生链表 
函数参数：学生链表二级头指针head 
返回值：无 
************************************************************/ 
void creat_student(struct Student **headp)
{
	struct Student *tail=NULL,*p;
	char ch;
	tail=(struct Student *)malloc(sizeof(struct Student));
	printf("请输入学号，姓名，性别，籍贯，出生年月，联系电话，入学分数，是否毕业，毕业去向\n");
	scanf("%s %s %c %s %s %s %f %d %s",tail->SNo,tail->name,&tail->sex,tail->native_place,tail->year,tail->telephone,&tail->score,&tail->graduate,tail->graduate_place);
	getchar();//读取换行符	 
		printf("是否继续创建学生信息？\n");
		ch=getchar();getchar();
		p=tail;
		while(ch=='y'||ch=='Y')
		{
			p->next=(struct Student *)malloc(sizeof(struct Student));
		    p=p->next;
		    printf("请输入学号，姓名，性别，籍贯，出生年月，联系电话，入学分数，是否毕业，毕业去向\n");
		    scanf("%s %s %c %s %s %s %f %d %s",p->SNo,p->name,&p->sex,p->native_place,p->year,p->telephone,&p->score,&p->graduate,p->graduate_place);
		    getchar();
		    printf("是否继续创建学生信息？\n");
		    ch=getchar();getchar(); 
	}
	p->next=NULL;
	*headp=tail;
 }

/************************************************************
函数名称：creat_class
函数功能：创建二级十字交叉链表班级链表 
函数参数：班级链表二级头指针 
返回值：无 
************************************************************/ 
void creat_class(struct Class **head)
{
	struct Class *hp=NULL,*p;
	char ch;
    loop:
    	p=(struct Class *)malloc(sizeof(struct Class));
    	printf("请输入班级编号，专业名称，入学人数,入学平均年龄，毕业人数,班长姓名，班长联系电话，班主任姓名，班主任联系电话\n");
		scanf("%s %s %d %f %d %s %s %s %s",p->CNo,p->major,&p->num_enter,&p->ave_of_age,&p->num_graduate,p->monitor,p->telephone,p->teacher,p->telephone_teacher);
		getchar();
		p->student=NULL;
		p->next=hp;
		hp=p;
		printf("是否继续创建班级信息表？\n");
		ch=getchar();getchar();
		if(ch=='y'||ch=='Y') goto loop;//创建下一个班级信息表 
		(*head)=hp;//head指向新创建的班级信息表
		printf("是否创建学生信息表？\n");
		ch=getchar();getchar();
		if(ch=='y'||ch=='Y')
		{	
			p=(*head); //p指向班级信息表链链头 
		    while(p!=NULL)
		   {
		   	   printf("班级%s的学生信息表：\n",p->CNo); 
			   struct Student * pcrs;
			   creat_student(&pcrs);//创建学生信息表 
			   p->student=pcrs;
			   p=p->next;
		   } 	
		}			
 } 

/************************************************************
函数名称：creat_grade
函数功能：创建三级链表年级链表 
函数参数：年级链表二级头指针head 
返回值：无 
************************************************************/ 
void creat_grade(struct Grade **head)
{
	struct Grade *hp=NULL,*p;
	char ch;
    loop:
    	p=(struct Grade *)malloc(sizeof(struct Grade));
    	printf("请输入年级编号，入学时间，入学人数，毕业人数，年级辅导员姓名，辅导员电话，年级学生会主席\n");
		scanf("%s %d %d %d %s %s %s",p->CSNo,&p->time,&p->num_enter,&p->num_graduate,p->name,p->telephone,p->name_chairman);
		getchar();
		p->classes=NULL;
		p->next=hp;
		hp=p;
		printf("是否继续创建年级信息表？\n");
		ch=getchar();getchar();
		if(ch=='y'||ch=='Y') goto loop;//创建下一个班级信息表 
		(*head)=hp;//head指向新创建的班级信息表
		printf("是否创建班级信息表？\n");
		ch=getchar();getchar();
		if(ch=='y'||ch=='Y')
		{
			p=(*head); //p指向班级信息表链链头 
		    while(p!=NULL)
		   {
		   	   printf("%s届的班级信息表:\n",p->CSNo);
			   struct Class * pcrs;
			   creat_class(&pcrs);//创建学生信息表 
			   p->classes=pcrs;
			   p=p->next;
		   } 	
		}			
}

/************************************************************
函数名称：load_list
函数功能：录入功能函数，将文件中内容读入三级十字交叉链表 
函数参数：无 
返回值：年级链表头指针 
************************************************************/ 
Grade * load_list(void)           //读取功能函数
{
	FILE *in1, *in2, *in3;
	Grade *hp = NULL, *p1,*p2;
	Class *pc1,*pc2;
	Student *ps1,*ps2;
	if ((in1 = fopen("D://c课设//grade.dat", "rb")) == NULL)
	{
		printf("文件D://c课设//grade.dat打开失败！\n");
		exit(1);
	}
	if ((in2 = fopen("D://c课设//class.dat", "rb")) == NULL)
	{
		printf("文件D://c课设//class.dat打开失败！\n");
		exit(1);
	}
	if ((in3 = fopen("D://c课设//student.dat", "rb")) == NULL)
	{
		printf("文件D://c课设//student打开失败！\n");
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
函数名称：save
函数功能：将创建的或修改过后的三级十字交叉链表存储进对应的三个文件 
函数参数：年级链表头指针 
返回值：无 
************************************************************/ 
void save(struct Grade *head)
{
	FILE *out1,*out2,*out3;
	Grade *p=head;
	out1=fopen("D://c课设//grade.dat","w+");
	out2=fopen("D://c课设//class.dat","w+");
	out3=fopen("D://c课设//student.dat","w+");
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
	printf("\t\t\t------学生管理系统------\n");
	printf("\t\t\t------ 1 数据查询 ------\n");
	printf("\t\t\t------ 2 输入新数据-----\n");
	printf("\t\t\t------ 3 数据统计 ------\n");
	printf("\t\t\t------ 0 结束 ----------\n"); 
	int n;
	int flag=0;
	scanf("%d",&n);
	switch(n){
		case 1:
	        _seek(&flag,head);//查询系统函数 
	        if(flag==1){
	 	    flag=0;goto loop;//返回主菜单 
	        }
			break;
		case 2:
			_add(&flag,&head);//插入系统函数 
			if(flag==1){
	 	    flag=0;goto loop;//返回主菜单 
	        }
			break;
	    case 3:
	       _census(&flag,head);//统计函数主菜单 
	        if(flag==1){
	 	    flag=0;goto loop;//返回主菜单 
	        }
			break;
		case 0:
			break;
    }
    save(head);//将链表存到文件中 
    return 0;
}
