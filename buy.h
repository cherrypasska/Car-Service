#ifndef BUY_H
#define BUY_H

#include <QWidget>
#include "Client.h"
#include "oneBuy.h"
#include <QHash>
#include <QList>
#include "car.h"

namespace Ui {
class buy;
}

class buy : public QWidget
{
    Q_OBJECT

public:
    explicit buy(QWidget *parent = nullptr);
    ~buy();

private slots:
    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_clientName_textChanged(const QString &arg1);

    void on_pass_textChanged(const QString &arg1);

    void on_sellerName_cursorPositionChanged(int arg1, int arg2);

    void on_sellerName_textChanged(const QString &arg1);

    void on_carNum_cursorPositionChanged(int arg1, int arg2);

    void on_carNum_textChanged(const QString &arg1);

    void check();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void zap();
    void on_checkBox_3_stateChanged(int arg1);

    void on_pushButton_3_clicked();

private:
    oneBuy *processForm();
    void fillForm(oneBuy *value);
    void showCost(oneBuy *value);
    Ui::buy *ui;
    QList<oneBuy>* buys;
    QList<Client>* clients;
    int skidka = 0;
    int finalPrice = 0;
    int wheels = 0;
    bool flag = true;
    QString clientName;
    QString pass;
    QString prodName;
    QString carNum;
};

#endif // BUY_H
