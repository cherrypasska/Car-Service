#ifndef CARS_H
#define CARS_H

#include <QWidget>
#include <QHash>
#include <QTableWidget>
#include "car.h"
#include "Client.h"
#include <QList>
#include "oneBuy.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Cars; }
QT_END_NAMESPACE

class Cars : public QWidget {
    Q_OBJECT

public:
    Cars(QWidget *parent = nullptr);
    ~Cars();

private slots:
    void on_addCar_clicked();
    void on_delCar_clicked();
    void on_checkAuto_clicked();
    void on_searchByNum_clicked();
    void on_checkByOptions_clicked();
    void checkEq(QString &);

    void on_sits_clicked();

    void on_rule_stateChanged(int arg1);

    void on_rule_clicked();

    void on_antirain_stateChanged(int arg1);

    void on_antirain_clicked();

    void on_top_clicked();

    void on_bitai_clicked(bool checked);

    void on_comboBox_currentIndexChanged(int index);

    void check();

    void on_num_textChanged(const QString &arg1);

    void on_probeg_textChanged(const QString &arg1);

    void on_year_textChanged(const QString &arg1);

    void on_carname_textChanged(const QString &arg1);

private:
    Ui::Cars *ui;
    QHash<QString, Car> *cars;
    bool flag = true;
    bool checkbit = false;
    QString options;
    void print(QTableWidget *table);
    void zap();
    void zapbuys();
    int index;
    QList<oneBuy>* buys;
    QHash<QString, Client> clients;
};

#endif // CARS_H
