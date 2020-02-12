#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>
#include <QTimer>
#include <QDateTime>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QProcess>
#include <QPainter>
#include <QPixmap>
#include <QFileDialog>

#include <iostream>
using namespace  std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initstatus();
    initwidget();

    move(400,300);
    setFixedSize(570,400);	//窗口固定大小
    //QDesktopWidget* desktop = QApplication::desktop();
    //move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
    setWindowTitle("系统监控器");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timelabel;
    delete CPUusage;
    delete Memusage;
}

void MainWindow::initstatus()
{
    timelabel = new QLabel("时间：xxxx-xx-xx xx:xx:xx xx");
    CPUusage = new QLabel("CPU使用率:xx.xx%");
    Memusage = new QLabel("内存使用率：xx.xx%");

    //状态栏中加入组件
    QStatusBar *statusbar=ui->statusBar;
    statusbar->addWidget(timelabel);
    statusbar->addWidget(CPUusage);
    statusbar->addWidget(Memusage);

    //设置边框
    timelabel->setStyleSheet("border:2px solid gray;");
    //timelabel->setStyleSheet("background-color:gray");
    CPUusage->setStyleSheet("border:2px solid gray;");
    Memusage->setStyleSheet("border:2px solid gray;");

    //设置标签大小
    timelabel->setMinimumSize(230,30);
    CPUusage->setMinimumSize(140,30);
    Memusage->setMinimumSize(150,30);

    //每秒更新数据
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(update_time()));
    connect(timer,SIGNAL(timeout()),this,SLOT(update_CPUusage()));
    connect(timer,SIGNAL(timeout()),this,SLOT(update_Memusage()));
    timer->start(1000);
}

void MainWindow::initwidget()
{
    get_hostname();
    get_starttime();
    get_version();
    get_model();

    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(update_procinfo()));
    connect(timer,SIGNAL(timeout()),this,SLOT(get_runtime()));
    timer->start(1000);

    connect(ui->query1,SIGNAL(clicked()),this,SLOT(get_pid_info()));
    connect(ui->query2,SIGNAL(clicked()),this,SLOT(get_proc_info()));
    connect(ui->lineEdit1,SIGNAL(returnPressed()),this,SLOT(get_pid_info()));
    connect(ui->lineEdit2,SIGNAL(returnPressed()),this,SLOT(get_proc_info()));
    connect(ui->killproc,SIGNAL(clicked()),this,SLOT(killprocess()));
    connect(ui->run,SIGNAL(clicked()),this,SLOT(newprocess()));
    connect(ui->shutButton,SIGNAL(clicked()),this,SLOT(shut()));
}

void MainWindow::update_time()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //年月日，时分秒，星期
    timelabel->setText("时间："+str);
}

void MainWindow::update_CPUusage()
{
    float usage=get_CPUusage();
    if(usage==-1){
        CPUusage->setText("CPU使用率:error");
    }
    else{
        QString str=QString::number(usage,'f',2);
        //QString str=QString("CPU使用率:%1").arg(usage);
        CPUusage->setText("CPU使用率:"+str+"%");
        add_CPUpoint(usage);
    }
}

void MainWindow::update_Memusage()
{
    float usage=get_Memusage();
    if(usage==-1){
        Memusage->setText("内存使用率:error");
    }
    else{
        QString str=QString::number(usage,'f',2);
        Memusage->setText("内存使用率:"+str+"%");
        add_Mempoint(usage);
    }
}

void MainWindow::get_hostname()
{
    QFile file("/proc/sys/kernel/hostname");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    ui->hostname->setText(QString(t));
    file.close();
}

void MainWindow::get_starttime()
{
    time_t nowtime=0;		//当前时间
    struct tm *ptm=NULL;
    time_t boot_time=0;		//开机时间
    time_t runtime=(time_t)get_runtime_sec();	//运行时间
    QString start_time;
    QString week[7]={"周日","周一","周二","周三","周四","周五","周六"};

    time(&nowtime);		//获取当前时间
    boot_time=nowtime-runtime;
    ptm=localtime(&boot_time);	//将开机时间分解

    if(ptm->tm_min<=9)		//分钟数小于10
    {
        start_time=QString("%1-%2-%3 %4:0%5:%6 %7").arg(ptm->tm_year+1900).arg(ptm->tm_mon+1)
                .arg(ptm->tm_mday).arg(ptm->tm_hour).arg(ptm->tm_min).arg(ptm->tm_sec).arg(week[ptm->tm_wday]);
    }
    else if(ptm->tm_sec<=9)	//秒数小于10
    {
        start_time=QString("%1-%2-%3 %4:%5:0%6 %7").arg(ptm->tm_year+1900).arg(ptm->tm_mon+1)
                .arg(ptm->tm_mday).arg(ptm->tm_hour).arg(ptm->tm_min).arg(ptm->tm_sec).arg(week[ptm->tm_wday]);
    }
    else
    {
        start_time=QString("%1-%2-%3 %4:%5:%6 %7").arg(ptm->tm_year+1900).arg(ptm->tm_mon+1)
                .arg(ptm->tm_mday).arg(ptm->tm_hour).arg(ptm->tm_min).arg(ptm->tm_sec).arg(week[ptm->tm_wday]);
    }
    ui->start_time->setText(start_time);
}

void MainWindow::get_runtime()
{
    QString str;
    int day,hour,minute,second;
    float runtime = get_runtime_sec();
    if(runtime==-1){
        ui->run_time->setText("error");
    }
    else{
        int runtime2=(int)runtime;
        day=runtime2/86400;
        hour=(runtime2%86400)/3600;
        minute=(runtime2%3600)/60;
        second=runtime2%60;
        //QString str=QString::number(runtime2,'f',2);
        str=QString("%1:%2:%3:%4").arg(day).arg(hour).arg(minute).arg(second);
        ui->run_time->setText(str);
    }
}

void MainWindow::get_version()
{
    QFile file1("/proc/sys/kernel/ostype");
    QFile file2("/proc/sys/kernel/osrelease");
    file1.open(QIODevice::ReadOnly | QIODevice::Text);
    file2.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in1(&file1);
    QTextStream in2(&file2);
    QString str1 = in1.readLine();
    QString str2 = in2.readLine();
    ui->system_version->setText(str1+str2);
    file1.close();
    file2.close();
}

void MainWindow::get_model()
{
    int i=0;
    QString str;
    QFile file("/proc/cpuinfo");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    do{
        str=in.readLine();
        if(i==4) break;
        i++;
    }while(!in.atEnd());
    str=str.mid(13);
    ui->CPU_model->setText(str);
    file.close();
}

void MainWindow::update_procinfo()
{
    int i=0;
    QStringList header;
    pidnum=get_pidinfo(procinfo);
    //printf("%d ",pidnum);
    QTableWidgetItem *name_item;
    QTableWidgetItem *pid_item;
    QTableWidgetItem *ppid_item;
    QTableWidgetItem *mem_use_item;
    QTableWidgetItem *priority_item;
    ui->tableWidget->setColumnCount(5);		//设置列数
    ui->tableWidget->setRowCount(pidnum);	//设置行数
    header<<"进程名"<<"pid"<<"ppid"<<"内存占用/kb"<<"优先级";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    for(i=0;i<pidnum;i++)
    {
        //cout << i << " " << procinfo[i].name <<endl;
        name_item=new QTableWidgetItem(QString::fromStdString(procinfo[i].name));
        pid_item=new QTableWidgetItem(QString::fromStdString(procinfo[i].pid));
        ppid_item=new QTableWidgetItem(QString::fromStdString(procinfo[i].ppid));
        mem_use_item=new QTableWidgetItem(QString::fromStdString(procinfo[i].mem_use));
        priority_item=new QTableWidgetItem(QString::fromStdString(procinfo[i].priority));

        //插入数据
        ui->tableWidget->setItem(i,0,name_item);
        ui->tableWidget->setItem(i,1,pid_item);
        ui->tableWidget->setItem(i,2,ppid_item);
        ui->tableWidget->setItem(i,3,mem_use_item);
        ui->tableWidget->setItem(i,4,priority_item);

        //居中显示
        name_item->setTextAlignment(Qt::AlignCenter);
        pid_item->setTextAlignment(Qt::AlignCenter);
        ppid_item->setTextAlignment(Qt::AlignCenter);
        mem_use_item->setTextAlignment(Qt::AlignCenter);
        priority_item->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::get_pid_info()
{
    QString str=ui->lineEdit1->text();
    if(str.isEmpty()){
        QMessageBox::information(this,"ERROR","please input the name of the process you want to query!");
        return ;
    }

    int i=0;
    QStringList  header;
    QTableWidgetItem *name_item;
    QTableWidgetItem *pid_item;
    QTableWidgetItem *ppid_item;
    QTableWidgetItem *mem_use_item;
    QTableWidgetItem *priority_item;
    for(i=0;i<pidnum;i++)
    {
        if(str==QString::fromStdString(procinfo[i].pid)) break;
    }
    if(i==pidnum){  //进程不存在
        QMessageBox::information(this,"ERROR","This process isn't existed!");
        return ;
    }
    else{
        header<<"进程名"<<"pid"<<"ppid"<<"内存占用/kb"<<"优先级";
        ui->tableWidget2->setHorizontalHeaderLabels(header);
        ui->tableWidget2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);   //均匀分配列宽
        QHeaderView *hid = ui->tableWidget2->verticalHeader();
        hid->setHidden(true);// 隐藏行号
        ui->tableWidget2->setColumnCount(5);		//设置列数
        ui->tableWidget2->setRowCount(1);	//设置行数

        name_item = new QTableWidgetItem(QString::fromStdString(procinfo[i].name));
        pid_item = new QTableWidgetItem(str);
        ppid_item = new QTableWidgetItem(QString::fromStdString(procinfo[i].ppid));
        mem_use_item = new QTableWidgetItem(QString::fromStdString(procinfo[i].mem_use));
        priority_item = new QTableWidgetItem(QString::fromStdString(procinfo[i].priority));

        //插入数据
        ui->tableWidget2->setItem(0,0,name_item);
        ui->tableWidget2->setItem(0,1,pid_item);
        ui->tableWidget2->setItem(0,2,ppid_item);
        ui->tableWidget2->setItem(0,3,mem_use_item);
        ui->tableWidget2->setItem(0,4,priority_item);

        //居中显示
        name_item->setTextAlignment(Qt::AlignCenter);
        pid_item->setTextAlignment(Qt::AlignCenter);
        ppid_item->setTextAlignment(Qt::AlignCenter);
        mem_use_item->setTextAlignment(Qt::AlignCenter);
        priority_item->setTextAlignment(Qt::AlignCenter);

        //更新当前进程号
        proc_pid=QString::fromStdString(procinfo[i].pid);
    }
}

void MainWindow::get_proc_info()
{
    QString str=ui->lineEdit2->text();
    if(str.isEmpty()){
        QMessageBox::information(this,"ERROR","please input the pid of the process you want to query!");
        return ;
    }

    int i=0;
    int num=0;
    QStringList  header;
    QTableWidgetItem *name_item;
    QTableWidgetItem *pid_item;
    QTableWidgetItem *ppid_item;
    QTableWidgetItem *mem_use_item;
    QTableWidgetItem *priority_item;
    for(i=0;i<pidnum;i++)
    {
        if(str==QString::fromStdString(procinfo[i].name)) num++;
    }
    if(num==0){	//进程不存在
        QMessageBox::information(this,"ERROR","This process isn't existed!");
        return ;
    }

    header<<"进程名"<<"pid"<<"ppid"<<"内存占用/kb"<<"优先级";
    ui->tableWidget2->setHorizontalHeaderLabels(header);
    ui->tableWidget2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);   //均匀分配列宽
    QHeaderView *hid = ui->tableWidget2->verticalHeader();
    hid->setHidden(true);// 隐藏行号
    ui->tableWidget2->setColumnCount(5);		//设置列数
    ui->tableWidget2->setRowCount(1);	//设置行数
    ui->tableWidget2->setColumnCount(5);		//设置列数
    ui->tableWidget2->setRowCount(num);	//设置行数

    int num2=0;
    for(i=0;i<pidnum;i++){
        if(str==QString::fromStdString(procinfo[i].name)){
            name_item = new QTableWidgetItem(QString::fromStdString(procinfo[i].name));
            pid_item = new QTableWidgetItem(QString::fromStdString(procinfo[i].pid));
            ppid_item = new QTableWidgetItem(QString::fromStdString(procinfo[i].ppid));
            mem_use_item = new QTableWidgetItem(QString::fromStdString(procinfo[i].mem_use));
            priority_item = new QTableWidgetItem(QString::fromStdString(procinfo[i].priority));

            //插入数据
            ui->tableWidget2->setItem(num2,0,name_item);
            ui->tableWidget2->setItem(num2,1,pid_item);
            ui->tableWidget2->setItem(num2,2,ppid_item);
            ui->tableWidget2->setItem(num2,3,mem_use_item);
            ui->tableWidget2->setItem(num2,4,priority_item);

            //居中显示
            name_item->setTextAlignment(Qt::AlignCenter);
            pid_item->setTextAlignment(Qt::AlignCenter);
            ppid_item->setTextAlignment(Qt::AlignCenter);
            mem_use_item->setTextAlignment(Qt::AlignCenter);
            priority_item->setTextAlignment(Qt::AlignCenter);

            //更新当前进程号
            proc_pid=QString::fromStdString(procinfo[i].pid);
            if((++num2)==num) break;
        }
    }
}

void MainWindow::killprocess()
{
    //未查询进程
    if(proc_pid.isEmpty()){
        QMessageBox::information(this,"ERROR","Please query the process first!");
        return ;
    }

    //判断进程是否存在
    int i=0;
    for(i=0;i<pidnum;i++)
    {
        if(proc_pid==QString::fromStdString(procinfo[i].pid)) break;
    }
    if(i==pidnum){
        QMessageBox::information(this,"ERROR","This process isn't existed!");
        return ;
    }

    QString str;
    str = QString("kill %1").arg(proc_pid);
    QByteArray byte = str.toLatin1();       //改变编码
    char *command = byte.data();    //转为char*，并在结尾加'/0'
    system(command);
}

void MainWindow::newprocess()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("运行新任务"));
    fileDialog->setDirectory(".");			//设置初始目录为当前目录
    if(fileDialog->exec() == QDialog::Accepted) {
        QString path = fileDialog->selectedFiles()[0];
        bool result = QProcess::startDetached(path,QStringList());
        if(result==false){	//选择其他问价
            QMessageBox::warning(NULL, tr("Error"), tr("Please select the executable file!"));
        }
    }
}

void MainWindow::shut()
{
    QMessageBox msgBox;
    msgBox.move(450,350);
    msgBox.setWindowTitle(tr("shut"));
    msgBox.setText(tr("系统即将关机，是否确认?"));
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setButtonText(QMessageBox::Yes,QString(tr("确认")));
    msgBox.setButtonText(QMessageBox::Cancel,QString(tr("取消")));
    int ret = msgBox.exec();
    if(ret==QMessageBox::Yes)
    {
        system("poweroff");
    }
}

void MainWindow::update_CPUline()
{
    QPen pen;
    QPixmap pix(480,100);		//设置尺寸
    QPainter painter(&pix);
    pix.fill(Qt::green);		//背景色
    pen.setColor(Qt::lightGray);
    painter.setPen(pen);
    for(int i=0;i<4;i++){		//绘制网格，用于观察数据
        painter.drawLine(0,i*25,480,i*25);
        painter.drawLine(i*120,0,i*120,100);
    }
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    for(int i=0;i<ylist_CPU.size()-1;i++){	//使用率曲线
        painter.drawLine(4*i,100-(ylist_CPU.value(i)),4*(i+1),
                         100-(ylist_CPU.value(i+1)));
    }

    ui->CPU_label->setPixmap(pix);
}

void MainWindow::update_Memline()
{
    QPen pen;
    QPixmap pix(480,100);		//设置尺寸
    QPainter painter(&pix);
    pix.fill(Qt::green);		//背景色
    pen.setColor(Qt::lightGray);
    painter.setPen(pen);
    for(int i=0;i<4;i++){		//绘制网格，用于观察数据
        painter.drawLine(0,i*25,480,i*25);
        painter.drawLine(i*120,0,i*120,100);
    }
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    for(int i=0;i<ylist_Mem.size()-1;i++){	//使用率曲线
        painter.drawLine(4*i,100-(ylist_Mem.value(i)),4*(i+1),
                         100-(ylist_Mem.value(i+1)));
    }

    ui->Mem_label->setPixmap(pix);
}

void MainWindow::add_CPUpoint(float usage)
{
    if(ylist_CPU.size()==0){
        for(int i=0;i<120;i++){
            ylist_CPU.push_back(0);
        }
    }
    ylist_CPU.pop_front();
    ylist_CPU.push_back(usage);
    update_CPUline();
    //QDebug << "CPU使用率数据未录入!\n";
}

void MainWindow::add_Mempoint(float usage)
{
    if(ylist_Mem.size()==0){
        for(int i=0;i<120;i++){
            ylist_Mem.push_back(0);
        }
    }
    ylist_Mem.pop_front();
    ylist_Mem.push_back(usage);
    update_Memline();
    //QDebug << "内存使用率数据未录入!\n";
}
