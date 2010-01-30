#ifndef CLIENTELIST_H
#define CLIENTELIST_H

#include <QtGui/QWidget>
#include "clientecontroller.h"


namespace Ui {
    class ClienteList;
}

class ClienteList : public QWidget {
    Q_OBJECT
public:
    ClienteList(QWidget *parent = 0);
    ~ClienteList();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ClienteList *m_ui;
    ClienteController clienteController;
private slots:
    void repaint(QString);
};

#endif // CLIENTELIST_H
