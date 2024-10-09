#include "chartviewwid.h"
#include <QChartView>
#include <QMainWindow>
#include <QDebug>
ChartViewWid::ChartViewWid(QWidget *parent) : QWidget(parent)

{
//    this->setStyleSheet("background-color:blue");
    qchart = new QChart();
  //  qchart->setBackgroundBrush(QColor(43,48,70));
//    qchart->setTitleBrush(QBrush(Qt.gray));
//    qchart->setBackgroundPen(QColor(43,48,70));

   //把chart放到容器里
   chartView = new QChartView(this);
   chartView->setStyleSheet("border-radius: 20px;");
   chartView->resize(865,690);//宽，高

   //设置抗锯齿
   chartView->setChart(qchart);
   chartView->setRenderHint(QPainter::Antialiasing);

   //创建线
//   line_low = new QLineSeries;
//   line_high = new QLineSeries;
   for(int i=0;i<Line_num;i++)
   {
       line_num[i] = new QLineSeries;
       m_hegenum[i] = 0;
   }

}
void ChartViewWid::Init(QString str_name)
{


    m_name = str_name;
    for(int i=0;i<Line_num;i++)
    {
     //设置线名字
    line_num[i]->setName("VL"+QString::number(i+1));
     line_num[i]->setUseOpenGL(true);
     //放入charts里
    qchart->addSeries(line_num[i]);
    }

     //设置图表名
   qchart->setTitle(m_name);
   qchart->setTitleFont(QFont("Microsoft YaHei", 25, QFont::Bold));
   qchart->setTitleBrush(QColor(43,48,70));



   //创建x坐标
   QaX = new QDateTimeAxis;
   //格式
   QaX->setFormat("hh:mm:ss");
   QaX->setTickCount(5);
   QaX->setTitleText("时间轴（秒）");
   QaX->setLabelsFont(QFont("Microsoft YaHei", 12, QFont::Bold));

   //创建y坐标
   QaY = new QValueAxis;
   //设置范围
   QaY->setRange(0,1400);
   QaY->setTickCount(8);
   QaY->setTitleText("电流值（mA）");
   QaY->setLabelsFont(QFont("Microsoft YaHei", 10, QFont::Bold));


   for(int i=0;i<Line_num;i++)
   {
        //将线条放入表中
       qchart->setAxisX(QaX, line_num[i]);
       qchart->setAxisY(QaY, line_num[i]);
       //初始化完成后取线条颜色
       color = line_num[i]->color();

        line_num[i]->append(0,800);

   }

}

//数据更新
void ChartViewWid::ElectricChange(int numa,int numb,int numc,int numd,int nume,int numf,int numg,int numh/*,int numi,int numj,int numk,int numl*/){


    //获取当前时间
    QDateTime currentTime = QDateTime::currentDateTime();
    if(numa!=5) line_num[0]->append(currentTime.toMSecsSinceEpoch(),numa);
    if(numb!=5) line_num[1]->append(currentTime.toMSecsSinceEpoch(),numb);
    if(numc!=5) line_num[2]->append(currentTime.toMSecsSinceEpoch(),numc);
    if(numd!=5) line_num[3]->append(currentTime.toMSecsSinceEpoch(),numd);
    if(nume!=5) line_num[4]->append(currentTime.toMSecsSinceEpoch(),nume);
    if(numf!=5) line_num[5]->append(currentTime.toMSecsSinceEpoch(),numf);
    if(numg!=5) line_num[6]->append(currentTime.toMSecsSinceEpoch(),numg);
    if(numh!=5) line_num[7]->append(currentTime.toMSecsSinceEpoch(),numh);
    // if(numi!=5) line_num[8]->append(currentTime.toMSecsSinceEpoch(),numi);
    // if(numj!=5) line_num[9]->append(currentTime.toMSecsSinceEpoch(),numj);
    // if(numk!=5) line_num[10]->append(currentTime.toMSecsSinceEpoch(),numk);
    // if(numl!=5) line_num[11]->append(currentTime.toMSecsSinceEpoch(),numl);
    // qDebug()<< line_num[0]->count()<<endl;
/**
* @brief 注释
* @author houyawei
* @date 2023/05/18
* setTitleBrush()使图表标题颜色改变
*在qt5.6.3上面，三个以及三个以上图表同时使用函数setTitleBrush()，会使界面卡顿
*在qt5.9.3上面同时使用四个函数，功能正常。
*/

    qchart->axisX()->setMin(QDateTime::currentDateTime().addSecs(-1*1));
    qchart->axisX()->setMax(QDateTime::currentDateTime().addSecs(0));


   for(int i=0;i<Line_num;i++)
   {
       if(line_num[i]->count()>15)line_num[i]->remove(0);
   }

   if(numa>600 && numa<1000) m_hegenum[0] = 1;
   if(numb>600 && numb<1000) m_hegenum[1] = 1;
   if(numc>600 && numc<1000) m_hegenum[2] = 1;
   if(numd>600 && numd<1000) m_hegenum[3] = 1;
   if(nume>600 && nume<1000) m_hegenum[4] = 1;
   if(numf>600 && numf<1000) m_hegenum[5] = 1;
   if(numg>600 && numg<1000) m_hegenum[6] = 1;
   if(numh>600 && numh<1000) m_hegenum[7] = 1;



}
void ChartViewWid::ReInit(){

    for(int i=0;i<Line_num;i++)
    {
        line_num[i]->removePoints(0,line_num[i]->count());
        m_hegenum[i] = 0;
    }
}
