#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QList>
#include "caculate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    int pidnum;
    QString proc_pid;
    QLabel *timelabel;
    QLabel *CPUusage;
    QLabel *Memusage;
    QList<float> ylist_CPU;
    QList<float> ylist_Mem;
    ProcInfo procinfo[1024];

public:
    void initstatus();			//初始化状态栏
    void initwidget();			//初始化TabWidget的界面
    void get_hostname();		//获取主机名
    void get_starttime();		//获取开启时间
    void get_version();			//获取版本号
    void get_model();			//获取CPU型号和主频大小
    void update_CPUline();		//更新CPU使用率曲线
    void update_Memline();		//更新内存使用率曲线
    void add_CPUpoint(float usage);		//加入新的CPU使用率数据
    void add_Mempoint(float usage);		//加入新的内存使用率数据

public slots:
    void update_time();			//更新时间
    void update_CPUusage();		//更新CPU使用率
    void update_Memusage();		//更新内存使用率
    void update_procinfo();		//更新进程信息
    void get_pid_info();		//查找进程号对应的进程信息
    void get_proc_info();		//查找进程名对应的进程信息
    void killprocess();			//结束进程
    void newprocess();			//运行新进程
    void shut();				//关机
    void get_runtime();			//获取运行时间
};

#endif // MAINWINDOW_H
