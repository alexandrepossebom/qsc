#ifndef CLIENTELIST_H
#define CLIENTELIST_H

#include <QtGui/QWidget>

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
};

#endif // CLIENTELIST_H
