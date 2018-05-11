#ifndef DIALOGTUTKSEARCH_H
#define DIALOGTUTKSEARCH_H

#include <QDialog>
#include <QListWidget>
#include <QDebug>

namespace Ui {
class DialogTutkSearch;
}

class DialogTutkSearch : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTutkSearch(QWidget *parent = 0);
    ~DialogTutkSearch();

     QString tutkID;

private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::DialogTutkSearch *ui;
};

#endif // DIALOGTUTKSEARCH_H
