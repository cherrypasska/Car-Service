#ifndef CLIENTS_H
#define CLIENTS_H
#include "Client.h"
#include <QWidget>

namespace Ui {
class Clients;
}

class Clients : public QWidget
{
    Q_OBJECT

public:
    explicit Clients(QWidget *parent = nullptr);
    ~Clients();
    QList<Client> clients;
    void addOne();
private:
    Ui::Clients *ui;
};

#endif // CLIENTS_H
