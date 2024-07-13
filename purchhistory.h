#ifndef PURCHHISTORY_H
#define PURCHHISTORY_H

#include <QWidget>
#include "oneBuy.h"
#include <QTableWidget>
namespace Ui {
class purchhistory;
}

class purchhistory : public QWidget
{
    Q_OBJECT

public:
    explicit purchhistory(QWidget *parent = nullptr);
    ~purchhistory();
    void zap();
    bool flag = true;
    void print(QTableWidget*);
private slots:
    void on_historycheck_clicked();

    void on_deletehistrory_clicked();

private:
    Ui::purchhistory *ui;
    QList<oneBuy>* list;
};

#endif // PURCHHISTORY_H
