#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

class TextWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextWidget(QWidget *parent = nullptr);
    void Init(QString str_name,QString str_unit);
    void SetValue(quint32 value);
    void ReInit();
    int m_hege;
    QString m_str_name;

private:
    QHBoxLayout *m_layout;

    QLabel* m_name;
    QLabel* m_unit;
    QLabel* m_value;

signals:

public slots:
};

#endif // TEXTWIDGET_H
