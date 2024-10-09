#include "dataread.h"
#include "ui_dataread.h"
#include <QTime>
#include <QMessageBox>
#include <QDebug>


DataRead::DataRead(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataRead)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:black;color:white");
    ui->groupBox->setStyleSheet("background-color:rgb(43,48,70);color:white;font-size:20px");
    ui->groupBox_2->setStyleSheet("background-color:rgb(43,48,70);color:white;font-size:20px");
    ui->groupBox_3->setStyleSheet("background-color:rgb(43,48,70);color:white;font-size:20px");
    ui->groupBox_4->setStyleSheet("background-color:rgb(43,48,70);color:white;font-size:20px");
    ui->tableWidget->setStyleSheet("background-color:rgb(43,48,70);color:black;font-size:20px");
//    this->setStyleSheet("background-color:rgb(43,48,70);color:white");
    QStringList listHeader;
    listHeader << "系统时间" << "时间标识" << "时间标识(s)" << "CAN通道" << "传输方向" << "ID号" << "帧类型" << "帧格式" << "长度" << "数据";

    ui->comboBox_3->setCurrentIndex(8);

    ui->tableWidget->setColumnCount(listHeader.count());
    ui->tableWidget->setHorizontalHeaderLabels(listHeader);


    ui->tableWidget->setColumnWidth(0,140);
    ui->tableWidget->setColumnWidth(1,140);
    ui->tableWidget->setColumnWidth(2,140);
    ui->tableWidget->setColumnWidth(3,140);
    ui->tableWidget->setColumnWidth(4,140);
    ui->tableWidget->setColumnWidth(5,140);
    ui->tableWidget->setColumnWidth(6,140);
    ui->tableWidget->setColumnWidth(7,140);
    ui->tableWidget->setColumnWidth(8,140);
    ui->tableWidget->setColumnWidth(9,270);

    //for(int i = 0;i < 9;i ++)
    //    ui->tableWidget->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);


    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(CheckEverySec()));
    canthread = new CANThread();
    connect(canthread,&CANThread::getProtocolData,this,&DataRead::onGetProtocolData);
    connect(canthread,&CANThread::boardInfo,this,&DataRead::onBoardInfo);

    iFlag_zuoyi = false;
    iFlag_lihe = false;
    iFlag_zhuche_datuo =false;
    iFlag_kongdang = false;
    iFlag_shuangbian = false;
    iFlag_pto_shineng = false;
    iFlag_pto_waibu = false;
    iFlag_tsq_weizhi = false;
    iFlag_tsq_diwei =false;
    iFlag_siqu = false;
    iFlag_tsq_jiaodu = false;
    iFlag_zhuche_zhongxiaotuo = true;
    iSta_Dev,iSta_CanInit,iSta_CanStart = false;
    iSta_RecIng = false;

    for(int i=0;i<18;i++) iFlag_DI[i] = false;

    timer->start(2000);


//    Widget.show();
//    emit signal_send(1);
}

DataRead::~DataRead()
{
    delete ui;
}

void DataRead::AddDataToList(QStringList strList)
{

    if(!ui->checkBox_4->checkState())
        return;
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    for(int i = 0; i < strList.count();i ++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(strList.at(i),0);
        ui->tableWidget->setItem(row, i, item);
        if(i != strList.count() - 1)
            ui->tableWidget->item(row,i)->setTextAlignment(Qt::AlignCenter | Qt::AlignHCenter);

    }
    ui->tableWidget->scrollToBottom();
    if(ui->tableWidget->rowCount()>20) ui->tableWidget->setRowCount(0);
    // ui->tableWidget->setRowCount(10);
}
void DataRead::onGetProtocolData(VCI_CAN_OBJ *vci,unsigned int dwRel,unsigned int channel)
{
    QStringList messageList;
    QString str;
    for(unsigned int i = 0;i < dwRel;i ++)
    {
        messageList.clear();
        messageList << QTime::currentTime().toString("hh:mm:ss zzz");//时间
        if(vci[i].TimeFlag == 1)
        {
            messageList << "0x" + QString("%1").arg(vci[i].TimeStamp,8,16,QChar('0')).toUpper();//时间
            messageList << QString("%1").arg(QVariant(vci[i].TimeStamp * 0.1).toUInt(),8,10,QChar('0'));//时间
        }
        else
        {
            messageList << "无";//时间
            messageList << "无";//时间
        }
        messageList << "CH" + QString::number(channel);
        messageList << "接收";//收发
        messageList << "0x" + QString("%1").arg(vci[i].ID,8,16,QChar('0')).toUpper();//ID
        messageList << ((vci[i].RemoteFlag == 1) ? "远程帧" : "数据帧");//类型
        messageList << ((vci[i].ExternFlag == 1) ? "扩展帧" : "标准帧");//Frame
        QString str = "";
        if(vci[i].RemoteFlag == 0)//数据帧显示数据
        {
            messageList << "0x" + QString::number(vci[i].DataLen,16).toUpper();//长度
            str = "x| ";

            for(int j = 0;j < vci[i].DataLen;j ++)
                str += QString("%1 ").arg(vci[i].Data[j],2,16,QChar('0')).toUpper();//QString::number(recvCANData[i].frame.data[j],16) + " ";

        }
        else
            messageList << "0x0";//长度
        messageList << str;//数据
        /*
        //listHeader << "时间"  << "收/发" << "ID" << "Frame" << "类型" << "长度" << "数据";
        messageList.clear();
        messageList << QString::number(channel);
        messageList << "收";//收发
        messageList << "0x" + QString("%1").arg(vci[i].ID,8,16,QChar('0'));//ID
        messageList << ((vci[i].ExternFlag == 1) ? "扩展帧" : "标准帧");//Frame
        messageList << ((vci[i].RemoteFlag == 1) ? "远程帧" : "数据帧");//类型
        str = "";
        if(vci[i].RemoteFlag == 0)//数据帧显示数据
        {
            messageList << QString::number(vci[i].DataLen);//长度
            for(int j = 0;j < vci[i].DataLen;j ++)
                str += QString("%1 ").arg(vci[i].Data[j],2,16,QChar('0'));//QString::number(recvCANData[i].frame.data[j],16) + " ";
        }
        else
            messageList << "0";//长度
        messageList << str;//数据
        */

        AddDataToList(messageList);
        DataAnalysis(messageList);


    }

    iSta_RecIng = true;

}

QString versionStr(USHORT ver)
{
    return "V" + QString::number((ver & 0x0FFF) /0x100,16).toUpper() + "." + QString("%1 ").arg((ver & 0x0FFF) % 0x100,2,16,QChar('0')).toUpper();
}

void DataRead::onBoardInfo(VCI_BOARD_INFO vbi)
{
    ui->label_9->setText(QString::number(vbi.can_Num));
    ui->label_10->setText(versionStr(vbi.hw_Version));
    ui->label_12->setText(versionStr(vbi.in_Version));
    ui->label_13->setText(QString::number(vbi.irq_Num));
}

void DataRead::on_pushButton_clicked()//打开
{
//    emit signal_send(1);
    if(ui->pushButton->text() == tr("打开设备"))
    {
        UINT baundRate = 0;
        if(ui->comboBox_3->currentText().indexOf("Kbps") != -1)
            baundRate = ui->comboBox_3->currentText().remove("Kbps").toUInt();
        else
            baundRate = QVariant(ui->comboBox_3->currentText().remove("Mbps").toFloat()).toUInt();
        bool dev = canthread->openDevice(4,//QVariant(ui->comboBox->currentIndex()).toUInt(),
                                      QVariant(ui->comboBox_2->currentIndex()).toUInt(),
                                      baundRate);
        if(dev == true)
        {
            ui->comboBox->setEnabled(false);
            ui->comboBox_2->setEnabled(false);
            ui->comboBox_3->setEnabled(false);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton->setText(tr("关闭设备"));
            iSta_Dev = true ;
        }
        else
            {
            QMessageBox::warning(this,"警告","打开设备失败！");
            iSta_Dev = false;
            iSta_CanInit = false;
            iSta_CanStart = false;
            }
    }
    else if(ui->pushButton->text() == tr("关闭设备"))
    {
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->comboBox_3->setEnabled(true);
        ui->comboBox_4->setEnabled(true);
        ui->sendBtn->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton->setText(tr("打开设备"));
        canthread->stop();
        canthread->closeDevice();
        iSta_Dev = false;
        iSta_CanInit = false;
        iSta_CanStart = false;
    }

    emit status_send(iSta_Dev,iSta_CanInit,iSta_CanStart);
}

void DataRead::on_sendBtn_clicked()
{
    if(ui->comboBox_6->currentIndex() == 0)//标准帧，ID 范围0-0x7FF
    {
        if(ui->sendIDEdit->text().toInt(Q_NULLPTR,16) > 0x7FF)
        {
            QMessageBox::warning(this,"警告","发送失败，标准帧ID范围为0~0x7FF！");
            return;
        }
    }
    else
    {
        if(ui->sendIDEdit->text().toInt(Q_NULLPTR,16) > 0x1FFFFFFF)
        {
            QMessageBox::warning(this,"警告","发送失败，扩展帧ID范围为0~0x1FFFFFFF！");
            return;
        }
    }
    QStringList strList = ui->sendDataEdit->text().split(" ");
    unsigned char data[8];
    memset(data,0,8);
    UINT dlc = 0;
    dlc = strList.count() > 8 ? 8 : strList.count();
    for(int i = 0;i < dlc;i ++)
        data[i] = strList.at(i).toInt(Q_NULLPTR,16);
    if(canthread->sendData(QVariant(ui->comboBox_4->currentIndex()).toUInt(),
                           QVariant(ui->sendIDEdit->text().toInt(Q_NULLPTR,16)).toUInt(),
                           ui->comboBox_5->currentIndex(),//标准帧
                           ui->comboBox_6->currentIndex(),//数据帧
                           data,dlc))
    {//发送成功，打印数据
        QStringList messageList;

        messageList.clear();
        messageList << QTime::currentTime().toString("hh:mm:ss zzz");//时间
        messageList << "无";//时间
        messageList << "无";//时间
        messageList << "CH" + QString::number(QVariant(ui->comboBox_4->currentIndex()).toUInt());
        messageList << "发送";//收发
        messageList << "0x" + ui->sendIDEdit->text().toUpper();//ID
        messageList << ((ui->comboBox_5->currentIndex() == 0) ? "数据帧" : "远程帧");//类型
        messageList << ((ui->comboBox_6->currentIndex() == 0) ? "标准帧" : "扩展帧");//Frame
        QString str = "";
        if(ui->comboBox_5->currentIndex() == 0)//数据帧显示数据
        {
            messageList << "0x" + QString::number(dlc,16).toUpper();//长度
            str = "x| ";
            for(int j = 0;j < dlc;j ++)
                str += QString("%1 ").arg((unsigned char)data[j],2,16,QChar('0')).toUpper();//QString::number((unsigned char)data[j],16) + " ";
        }
        else
            messageList << "0x0";//长度
        messageList << str;//数据
        AddDataToList(messageList);
    }
    else
        QMessageBox::warning(this,"警告","数据发送失败！");
}

void DataRead::on_cleanListBtn_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
}

void DataRead::on_pushButton_4_clicked()//复位
{
    if(canthread->reSetCAN())
    {
        ui->pushButton_4->setEnabled(false);
        ui->sendBtn->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
    }
    else
        QMessageBox::warning(this,"警告","CAN复位失败！");
}

void DataRead::on_pushButton_2_clicked()//初始化
{
    if(canthread->initCAN())
    {
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        iSta_CanInit = true;
    }
    else
    {
        QMessageBox::warning(this,"警告","CAN初始化失败！");
        iSta_CanInit = false;
    }
    emit status_send(iSta_Dev,iSta_CanInit,iSta_CanStart);
}

void DataRead::on_pushButton_3_clicked()//启动
{
    if(canthread->startCAN())
    {
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(true);
        ui->sendBtn->setEnabled(true);
        canthread->start();
        iSta_CanStart = true;
    }
    else
    {
        QMessageBox::warning(this,"警告","CAN启动失败！");
        iSta_CanStart = false;
    }
    emit status_send(iSta_Dev,iSta_CanInit,iSta_CanStart);
}

QByteArray DataRead::GetHexValue(QString str)
//直接将字符串，按照每两个字符分隔，然后转换成16进制发送。把Qstring类型转成QByteArray ，然后发送出去。
{
    QByteArray senddata;
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}
char DataRead::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))      //限定字符0-9
         return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F')) //限定字符A-F
         return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f')) //限定字符a-f
         return ch-'a'+10;
    else return (-1);
}

void DataRead::DataAnalysis(QStringList messageList)
{

    if(messageList.at(5)== "0x18FF5003")//0x18FF5032
        {
//                qDebug()<<"messageList.size()"<<messageList.size()<<endl
//                       <<"messageList:"<<messageList<<endl
//                      <<"messageList.at(5)"<<messageList.at(5)<<endl
//                         <<"messageList.at(9)"<<messageList.at(9)<<endl;
            QString string_data;
            string_data = messageList.at(9);
            string_data.remove("x|").remove(" ").simplified();
            QString string_data_head = string_data.mid(0,8);
            QString string_data_tail = string_data.mid(8,8);

            bool ok;
            quint32 hex_data_head = string_data_head.toUInt(&ok,16);
            quint32 hex_data_tail = string_data_tail.toUInt(&ok,16);
            quint32 and_result = 0x00000000 ;

                // qDebug()<<"接收到的数据："<<string_data_head.toLatin1()
                //         <<"前四个字节hex_data_head:"<<QString::number(hex_data_head ,16).toUpper()<<endl;
                // qDebug()<<"接收到的数据："<<string_data_tail.toLatin1()
                //         <<"后四个字节hex_data_tail:"<<QString::number(hex_data_tail ,16).toUpper()<<endl;

                // qDebug()<<"and_result"<<QString::number(and_result ,16).toUpper()<<endl;


              //DI-01
             and_result =  hex_data_head & 0x01000000 ;
            if (and_result == 0x01000000 && iFlag_DI[0]== false)
            {
                iFlag_DI[0] = true ;
                emit signal_send(0,iFlag_DI[0]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[0] == true)
            {
                iFlag_DI[0] = false ;
                emit signal_send(0,iFlag_DI[0]);
            }
            //DI-02
            and_result =  hex_data_head & 0x02000000 ;
            if (and_result == 0x02000000 && iFlag_DI[1]== false)
            {
                iFlag_DI[1] = true ;
                emit signal_send(1,iFlag_DI[1]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[1] == true)
            {
                iFlag_DI[1] = false ;
                emit signal_send(1,iFlag_DI[1]);
            }
            //DI-03
            and_result =  hex_data_head & 0x04000000 ;
            if (and_result == 0x04000000 && iFlag_DI[2]== false)
            {

                iFlag_DI[2] = true ;
                emit signal_send(2,iFlag_DI[2]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[2] == true)
            {
                iFlag_DI[2] = false ;
                emit signal_send(2,iFlag_DI[2]);
            }
            //DI-04
            and_result =  hex_data_head & 0x08000000 ;
            if (and_result == 0x08000000 && iFlag_DI[3]== false)
            {

                iFlag_DI[3] = true ;
                emit signal_send(3,iFlag_DI[3]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[3] == true)
            {
                iFlag_DI[3] = false ;
                emit signal_send(3,iFlag_DI[3]);
            }
            //DI-05
            and_result =  hex_data_head & 0x10000000 ;
            if (and_result == 0x10000000 && iFlag_DI[4]== false)
            {

                iFlag_DI[4] = true ;
                emit signal_send(4,iFlag_DI[4]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[4] == true)
            {
                iFlag_DI[4] = false ;
                emit signal_send(4,iFlag_DI[4]);
            }
            //DI-06
            and_result =  hex_data_head & 0x20000000 ;
            if (and_result == 0x20000000 && iFlag_DI[5]== false)
            {

                iFlag_DI[5] = true ;
                emit signal_send(5,iFlag_DI[5]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[5] == true)
            {
                iFlag_DI[5] = false ;
                emit signal_send(5,iFlag_DI[5]);
            }
            //DI-07
            and_result =  hex_data_head & 0x40000000 ;
            if (and_result == 0x40000000 && iFlag_DI[6]== false)
            {

                iFlag_DI[6] = true ;
                emit signal_send(6,iFlag_DI[6]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[6] == true)
            {
                iFlag_DI[6] = false ;
                emit signal_send(6,iFlag_DI[6]);
            }
            //DI-08
            and_result =  hex_data_head & 0x80000000 ;
            if (and_result == 0x80000000 && iFlag_DI[7]== false)
            {

                iFlag_DI[7] = true ;
                emit signal_send(7,iFlag_DI[7]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[7] == true)
            {
                iFlag_DI[7] = false ;
                emit signal_send(7,iFlag_DI[7]);
            }
            //DI-09
            and_result =  hex_data_head & 0x00010000 ;
            if (and_result == 0x00010000 && iFlag_DI[8]== false)
            {

                iFlag_DI[8] = true ;
                emit signal_send(8,iFlag_DI[8]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[8] == true)
            {
                iFlag_DI[8] = false ;
                emit signal_send(8,iFlag_DI[8]);
            }
            //DI-10
            and_result =  hex_data_head & 0x00020000 ;
            if (and_result == 0x00020000 && iFlag_DI[9]== false)
            {

                iFlag_DI[9] = true ;
                emit signal_send(9,iFlag_DI[9]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[9] == true)
            {
                iFlag_DI[9] = false ;
                emit signal_send(9,iFlag_DI[9]);
            }
            //DI-11
            and_result =  hex_data_head & 0x00040000 ;
            if (and_result == 0x00040000 && iFlag_DI[10]== false)
            {

                iFlag_DI[10] = true ;
                emit signal_send(10,iFlag_DI[10]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[10] == true)
            {
                iFlag_DI[10] = false ;
                emit signal_send(10,iFlag_DI[10]);
            }
            //DI-12
            and_result =  hex_data_head & 0x00080000 ;
            if (and_result == 0x00080000 && iFlag_DI[11]== false)
            {

                iFlag_DI[11] = true ;
                emit signal_send(11,iFlag_DI[11]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[11] == true)
            {
                iFlag_DI[11] = false ;
                emit signal_send(11,iFlag_DI[11]);
            }
            //DI-13
            and_result =  hex_data_head & 0x00100000 ;
            if (and_result == 0x00100000 && iFlag_DI[12]== false)
            {

                iFlag_DI[12] = true ;
                emit signal_send(12,iFlag_DI[12]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[12] == true)
            {
                iFlag_DI[12] = false ;
                emit signal_send(12,iFlag_DI[12]);
            }
            //DI-14
            and_result =  hex_data_head & 0x00200000 ;
            if (and_result == 0x00200000 && iFlag_DI[13]== false)
            {

                iFlag_DI[13] = true ;
                emit signal_send(13,iFlag_DI[13]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[13] == true)
            {
                iFlag_DI[13] = false ;
                emit signal_send(13,iFlag_DI[13]);
            }
            //DI-15
            and_result =  hex_data_head & 0x00400000 ;
            if (and_result == 0x00400000 && iFlag_DI[14]== false)
            {

                iFlag_DI[14] = true ;
                emit signal_send(14,iFlag_DI[14]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[14] == true)
            {
                iFlag_DI[14] = false ;
                emit signal_send(14,iFlag_DI[14]);
            }
            //DI-16
            and_result =  hex_data_head & 0x00800000 ;
            if (and_result == 0x00800000 && iFlag_DI[15]== false)
            {

                iFlag_DI[15] = true ;
                emit signal_send(15,iFlag_DI[15]);
            }
            else if (and_result == 0x00000000 && iFlag_DI[15] == true)
            {
                iFlag_DI[15] = false ;
                emit signal_send(15,iFlag_DI[15]);
            }




        }

    if(messageList.at(5)=="0x18FF5103")
    {
        QString string_data;
        string_data = messageList.at(9);
        string_data.remove("x|").remove(" ").simplified();
        QString string_data_1 = string_data.mid(0,2);
        QString string_data_2 = string_data.mid(2,2);
        QString string_data_3 = string_data.mid(4,2);
        QString string_data_4 = string_data.mid(6,2);
        QString string_data_5 = string_data.mid(8,2);
        QString string_data_6 = string_data.mid(10,2);
        QString string_data_7 = string_data.mid(12,2);
        QString string_data_8 = string_data.mid(14,2);

        bool ok;
        quint32 voltage_1 = (string_data_1).toUInt(&ok,16)*20;
        quint32 voltage_2 = (string_data_2).toUInt(&ok,16)*20;
        quint32 voltage_3 = (string_data_3).toUInt(&ok,16)*20;
        quint32 voltage_4 = (string_data_4).toUInt(&ok,16)*20;
        quint32 voltage_5 = (string_data_5).toUInt(&ok,16)*20;
        quint32 voltage_6 = (string_data_6).toUInt(&ok,16)*64;
        quint32 voltage_7 = (string_data_7).toUInt(&ok,16)*20;
        quint32 voltage_8 = (string_data_8).toUInt(&ok,16)*20;

        emit voltage_send(voltage_1,voltage_2,voltage_3,voltage_4,voltage_5,voltage_6,voltage_7,voltage_8);

    }

    // if(messageList.at(5)=="0x18FF2232")
    // {
    //     QString string_data;
    //     string_data = messageList.at(9);
    //     string_data.remove("x|").remove(" ").simplified();
    //     QString string_data_1 = string_data.mid(0,2);
    //      QString string_data_2 = string_data.mid(2,2);
    //     QString string_data_3 = string_data.mid(4,2);
    //      QString string_data_4 = string_data.mid(6,2);

    //     bool ok;
    //     quint32 voltage_1 = (string_data_2+string_data_1).toUInt(&ok,16);
    //     quint32 voltage_2 = (string_data_4+string_data_3).toUInt(&ok,16);

    //     emit voltage_send(5,5,5,5,voltage_1,voltage_2);

    // }

    if(messageList.at(5)=="0x18FF5303")
    {
        QString string_data;
        string_data = messageList.at(9);
        string_data.remove("x|").remove(" ").simplified();
        QString string_data_1 = string_data.mid(0,2);
        QString string_data_2 = string_data.mid(2,2);
        QString string_data_3 = string_data.mid(4,2);
        QString string_data_4 = string_data.mid(6,2);
        QString string_data_5 = string_data.mid(8,2);
        QString string_data_6 = string_data.mid(10,2);


        bool ok;
        quint32 frequency_1 = (string_data_1).toUInt(&ok,16)*50;
        quint32 frequency_2 = (string_data_2).toUInt(&ok,16)*50;
        quint32 frequency_3 = (string_data_3).toUInt(&ok,16)*50;

         emit speed_send(frequency_1,frequency_2,frequency_3);

    }

    // if(messageList.at(5)=="0x18FEF803")
    // {
    //     QString string_data;
    //     string_data = messageList.at(9);
    //     string_data.remove("x|").remove(" ").simplified();
    //     QString string_data_1 = string_data.mid(0,2);
    //     QString string_data_2 = string_data.mid(2,2);
    //     QString string_data_3 = string_data.mid(4,2);
    //     QString string_data_4 = string_data.mid(6,2);
    //     QString string_data_5 = string_data.mid(8,2);
    //     QString string_data_6 = string_data.mid(10,2);

    //     bool ok;
    //     quint32 voltage_5 = (string_data_2+string_data_1).toUInt(&ok,16);
    //     quint32 voltage_6 = (string_data_4+string_data_3).toUInt(&ok,16);
    //     quint32 voltage_7 = (string_data_6+string_data_5).toUInt(&ok,16);
    //     // qDebug()<<voltage_5<<"  "<<voltage_6<<"  "<<voltage_7<<endl;

    //     emit speed_send(5,5,5,5,voltage_5,voltage_6,voltage_7);

    // }



    if(messageList.at(5)=="0x18FF5203")
       {
        QString string_data;
        string_data = messageList.at(9);
        string_data.remove("x|").remove(" ").simplified();
        QString string_data_1 = string_data.mid(0,2);
        QString string_data_2 = string_data.mid(2,2);
        QString string_data_3 = string_data.mid(4,2);
        QString string_data_4 = string_data.mid(6,2);
        QString string_data_5 = string_data.mid(8,2);
        QString string_data_6 = string_data.mid(10,2);
        QString string_data_7 = string_data.mid(12,2);
        QString string_data_8 = string_data.mid(14,2);

        bool ok;
        quint32 data_1 = (string_data_1).toUInt(&ok,16)*8;
        quint32 data_2 = (string_data_2).toUInt(&ok,16)*8;
        quint32 data_3 = (string_data_3).toUInt(&ok,16)*8;
        quint32 data_4 = (string_data_4).toUInt(&ok,16)*8;
        quint32 data_5 = (string_data_5).toUInt(&ok,16)*8;
        quint32 data_6 = (string_data_6).toUInt(&ok,16)*8;
        quint32 data_7 = (string_data_7).toUInt(&ok,16)*8;
        quint32 data_8 = (string_data_8).toUInt(&ok,16)*8;

        emit electric_send(data_1,data_2,data_3,data_4,data_5,data_6,data_7,data_8);
       }

}

//设备连接
void DataRead::ConnectDev()
{
    on_pushButton_clicked();//打开
    on_pushButton_2_clicked();//初始化
    on_pushButton_3_clicked();//启动
}
//设备复位
void DataRead::ResetDev()
{
    on_pushButton_4_clicked();//复位
//    on_pushButton_clicked();//关闭
//    on_pushButton_clicked();//打开
//    on_pushButton_2_clicked();//初始化
    on_pushButton_3_clicked();//启动
}
void DataRead::CheckEverySec()
{
    if(iSta_RecIng == true)//数据接收中，设备上电状态
    {
    emit DataRec_sta();
//        qDebug()<<"CheckEverySec"<<endl;
    }
    else//没有接收到数据，界面重新初始化，为下一个设备上电做准备
    {
    StaReInit();//状态初始化
    emit UpdateUi();
    }
    iSta_RecIng = false;
}
void DataRead::StaReInit()
{
    // iFlag_zuoyi = false;
    // iFlag_lihe = false;
    // iFlag_zhuche_datuo = false;
    // iFlag_kongdang = false;
    // iFlag_shuangbian = false;
    // iFlag_pto_shineng = false;
    // iFlag_pto_waibu = false;
    // iFlag_tsq_weizhi = false;
    // iFlag_tsq_diwei =false;
    // iFlag_siqu = false;
    // iFlag_tsq_jiaodu = false;
    // iFlag_zhuche_zhongxiaotuo = true;
    // iSta_Dev,iSta_CanInit,iSta_CanStart = false;
    // iSta_RecIng = false;
    for(int i=0;i<16;i++) iFlag_DI[i] = false;

}
