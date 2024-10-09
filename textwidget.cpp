#include "textwidget.h"

TextWidget::TextWidget(QWidget *parent) : QWidget(parent)
{
//    this->setStyleSheet("background-color:rgb(43,48,70)");

     m_layout = new QHBoxLayout();

     m_name = new QLabel();
     m_value  = new QLabel();
     m_unit = new QLabel();
     m_name->setText("初始化");
     m_value->setText("0");
     m_unit->setText("Unit");
     m_name->setStyleSheet("background-color:rgb(43,48,70);color:rgb(255,245,238);font:35px");
     m_value->setStyleSheet("background-color:rgb(43,48,70);color:rgb(255,245,238);font:35px");
     m_unit->setStyleSheet("background-color:rgb(43,48,70);color:rgb(255,245,238);font:35px");

     m_layout->addStretch(1);
     m_layout->addWidget(m_name);
     m_layout->addStretch(1);
     m_layout->addWidget(m_value);

     m_layout->addWidget(m_unit);
     m_layout->addStretch(1);

     m_hege =0;

     setLayout(m_layout);


}

void TextWidget::Init(QString str_name,QString str_unit)
{
     m_name->setText(str_name);
     m_value->setText("0");
     m_unit->setText(str_unit);
     m_str_name = str_name;
}

void TextWidget::SetValue(quint32 value)
{
    m_value->setText(QString::number(value));
     // qDebug()<<"接收到的电压："<<QString::number(value)<<endl;
    if( m_str_name.contains("AI", Qt::CaseInsensitive) && value > 4700 && value < 5200) m_hege = 1;
    if( m_str_name.contains("FI", Qt::CaseInsensitive) && value > 650 && value < 750) m_hege = 1;

}

void TextWidget::ReInit()
{
     m_hege =0;
    m_value->setText("0");
}
