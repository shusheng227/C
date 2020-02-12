#ifndef CACULATE_H
#define CACULATE_H
#include <string>
using namespace std;

//保存进程信息
struct ProcInfo{
    string name;	//进程名
    string pid;		//进程号
    string ppid;	//父进程号
    string mem_use;	//内存占用大小
    string priority;//优先级
};

float get_CPUusage();
float get_Memusage();
float get_runtime_sec();
void read_proc(ProcInfo *pidinfo,const char *pid);
int get_pidinfo(ProcInfo procinfo[]);

#endif // CACULATE_H
