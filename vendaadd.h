#ifndef VENDAADD_H
#define VENDAADD_H

#include <QtGui/QWidget>

namespace Ui {
    class VendaAdd;
}

class VendaAdd : public QWidget {
    Q_OBJECT
public:
    VendaAdd(QWidget *parent = 0);
    ~VendaAdd();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::VendaAdd *m_ui;
};

#endif // VENDAADD_H
