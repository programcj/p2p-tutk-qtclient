#include "dialogtutksearch.h"
#include "ui_dialogtutksearch.h"
#include <QMessageBox>

#include <stdio.h>
#include "IOTCAPIs.h"
#include "AVAPIs.h"
#include "AVFRAMEINFO.h"
#include "AVIOCTRLDEFs.h"

DialogTutkSearch::DialogTutkSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTutkSearch)
{
    ui->setupUi(this);
}

DialogTutkSearch::~DialogTutkSearch()
{
    delete ui;
}

void DialogTutkSearch::on_pushButton_clicked()
{
    struct st_LanSearchInfo psLanSearchInfo[12];
     ui->listWidget->clear();

    if(psLanSearchInfo != NULL)
    {
        // wait time 1000 ms to get result, if result is 0 you can extend to 2000 ms
        int nDeviceNum = IOTC_Lan_Search(psLanSearchInfo, 12, 1000);
        printf("IOTC_Lan_Search ret[%d]\n", nDeviceNum);
        for(int i=0;i<nDeviceNum;i++)
        {
            //       printf("UID[%s] Addr[%s:%d]\n", psLanSearchInfo[i].UID, psLanSearchInfo[i].IP, psLanSearchInfo[i].port);
            QString sn=QString("%1%2%3%4%5").arg(psLanSearchInfo[i].UID).arg(",").arg(psLanSearchInfo[i].IP).arg(":").arg(QString::number(psLanSearchInfo[i].port));
            ui->listWidget->addItem(sn);
            qDebug() << sn;
        }
    }
}

void DialogTutkSearch::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString text=item->text();
    QString tutkid=text.left(text.indexOf(','));

   if(QMessageBox::Yes==QMessageBox::information(NULL, "select tutkid ?", tutkid, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes)){
       this->tutkID=tutkid;
       this->accept();
   }
//   else {
//       this->reject();
//   }
}
