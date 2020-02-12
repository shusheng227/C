#include "caculate.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;

float get_CPUusage()
{
    FILE *fp;
    char buf[128];
    char cpu[5];
    int user;		//从系统启动开始处于用户态时间
    int nice;		//从系统启动开始nice为负的进程占用CPU时间
    int system; 	//从系统启动开始累计到当前时刻，处于核心态的运行时间
    int idle;		//从系统启动开始累计到当前时刻，除IO等待时间以外的其它等待时间
    int iowait;		//从系统启动开始累计到当前时刻，IO等待时间(since 2.5.41)
    int irq;		//从系统启动开始累计到当前时刻，硬中断时间(since 2.6.0-test4)
    int softirq;	//从系统启动开始累计到当前时刻，软中断时间(since 2.6.0-test4)

    int total1,idle1,total2,idle2;
    float usage;

    fp=fopen("/proc/stat","r");
    if(fp==NULL){
        perror("open the file \"/proc/stat\" error:");
        return -1;
    }
    //第一次获取信息
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%s%d%d%d%d%d%d%d",cpu,&user,&nice,&system,&idle,&iowait,&irq,&softirq);
    total1 = user+nice+system+idle+iowait+irq+softirq;
    idle1 = idle;
    //第二次获取信息
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%s%d%d%d%d%d%d%d",cpu,&user,&nice,&system,&idle,&iowait,&irq,&softirq);
    total2 = user+nice+system+idle+iowait+irq+softirq;
    idle2 = idle;
    //计算CPU使用率
    if(total1==total2) usage=0;
    else{
        usage = (float)(total2-total1-(idle2-idle1))/(total2-total1)*100 ;
    }

    fclose(fp);
    return usage;
}

float get_Memusage()
{
    FILE *fp;
    char buf[30];
    float usage=0.0;
    char Memtotal[10],Memfree[15],Memavailable[20],Membuffer[10],Memcached[10];
    float total,free,available,buffer,cached;

    fp=fopen("/proc/meminfo","r");
    if(fp==NULL){
        perror("open the file \"/proc/meminfo\" error:");
        return -1;
    }
    //获取内存信息
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%s %f",Memtotal,&total);
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%s %f",Memfree,&free);
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%s %f",Memavailable,&available);
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%s %f",Membuffer,&buffer);
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%s %f",Memcached,&cached);
    //printf("%s %f %s %f %s %f %s %f \n",Memtotal,total,Memfree,free,Membuffer,buffer,Memcached,cached);
    //计算内存使用率
    usage=(1-(free+buffer+cached)/total)*100;

    fclose(fp);
    return usage;
}

float get_runtime_sec()
{
    FILE *fp;
    char buf[32];
    float runtime;

    fp=fopen("/proc/uptime","r");
    if(fp==NULL){
        perror("open the file \"/proc/uptime\" error:");
        return -1;
    }
    //获取时间信息
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%f",&runtime);

    fclose(fp);
    return runtime;
}

//从文件"/proc/(pid)/stat"中提取出进程号为pid的信息，
//保存到结构pidinfo中
void read_proc(ProcInfo *procinfo,const char *pid)
{
    char filename[18];
    FILE *fp;
    char buf[1024];
    char temp[10],pid2[6],pidname[20],ppid[6],priority[5],mem_use[10],pidname2[20];

    sprintf(filename,"/proc/%s/stat",pid);
    fp=fopen(filename,"r");
    if(fp==NULL){
        perror("open the file \"/proc/stat\" error:");
        return ;
    }
    //获取时间信息
    fgets(buf,sizeof(buf),fp);
    sscanf(buf,"%s %s",pid2,pidname);
    int length = strlen(pidname);
    if(pidname[length-1]!=')'){         //进程名中间有空格
        sscanf(buf,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s ",
               pid2,pidname,pidname2,temp,ppid,temp,temp,temp,temp,temp,temp,temp,temp,temp,temp,temp,
               temp,temp,priority,temp,temp,temp,temp,temp,mem_use);
        procinfo->name=pidname;
        procinfo->name=procinfo->name+" ";
        procinfo->name=procinfo->name+pidname2;
    }
    else{
        sscanf(buf,"%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s ",
               pid2,pidname,temp,ppid,temp,temp,temp,temp,temp,temp,temp,temp,temp,temp,temp,
               temp,temp,priority,temp,temp,temp,temp,temp,mem_use);
        procinfo->name=pidname;
    }
    procinfo->pid=pid2;
    procinfo->ppid=ppid;
    procinfo->priority=priority;
    procinfo->mem_use=mem_use;
    procinfo->name=procinfo->name.substr(1,procinfo->name.find(')')-1);
    //if(!strcmp("S",ppid)) cout << buf;
    /*cout << procinfo->pid << " "<< procinfo->name << " " << procinfo->ppid << " "
         << procinfo->mem_use << " " << procinfo->priority << endl;*/
    fclose(fp);
}

int get_pidinfo(ProcInfo procinfo[])
{
    DIR *dir;
    struct dirent *ptr;
    int num=0;		//保存进程数
    if(!(dir=opendir("/proc"))){
        perror("open the dir \"/proc\" error:");
        return -1;
    }
    while((ptr=readdir(dir))!=NULL)
    {
        if((ptr->d_name[0]>='1')&&(ptr->d_name[0]<='9'))
        {
            read_proc(&(procinfo[num]),ptr->d_name);
            //将进程名保存入数组procinfo
            num++;
        }
    }
    closedir(dir);
    return num;
}
