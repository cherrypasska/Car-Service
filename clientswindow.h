#ifndef CLIENTSWINDOW_H
#define CLIENTSWINDOW_H

#include <QWidget>
#include "oneBuy.h"
#include "buy.h"
#include "car.h"
#include <QHash>
#include <QList>
#include <QTableWidget>
namespace Ui {
class clientswindow;
}

class clientswindow : public QWidget
{
    Q_OBJECT

public:
    explicit clientswindow(QWidget *parent = nullptr);
    ~clientswindow();
    QList<oneBuy>* buys;
    QHash<QString, Client>* clients;

private slots:
    void on_pushButton_2_clicked();

    void zap();

    void zapbuys();
    void on_pushButton_5_clicked();
    void print(QTableWidget* table);
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::clientswindow *ui;
};

#endif // CLIENTSWINDOW_H
