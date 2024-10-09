#ifndef CHARTVIEWWID_H
#define CHARTVIEWWID_H

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
QT_CHARTS_USE_NAMESPACE

#include <QDateTimeAxis>//时间坐标轴
#include <QValueAxis>//普通坐标轴
#include <QDateTime>
#include <QBoxLayout>


# define Line_num 8

class ChartViewWid : public QWidget
{
public:
    explicit ChartViewWid(QWidget *parent = nullptr);
    void ElectricChange(int numa,int numb,int numc,int numd,int nume,int numf,int numg,int numh/*,int numi,int numj,int numk,int numl*/);
    void Init(QString str_name);
    void ReInit();
    QString m_name;
    int m_hegenum[Line_num];



private:
    QChart *qchart;
    QChartView *chartView;
    QLineSeries *line_num[Line_num];
    QDateTimeAxis *QaX;
    QValueAxis *QaY;
    QColor color;

};

#endif // CHARTVIEWWID_H
