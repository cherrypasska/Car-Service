#include "widget.h"
#include "./ui_widget.h"
#include "cars.h"
#include "buy.h"
#include "purchhistory.h"
#include "clientswindow.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    Cars *h = new Cars;
    h->show();
}


void Widget::on_pushButton_2_clicked()
{
    buy *s = new buy;
    s->show();
}


void Widget::on_pushButton_3_clicked()
{
    purchhistory *d = new purchhistory;
    d->show();
}


void Widget::on_pushButton_4_clicked()
{
    clientswindow *b = new clientswindow;
    b->show();
}

