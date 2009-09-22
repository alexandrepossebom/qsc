#ifndef CLIENTEADDVIEW_H
#define CLIENTEADDVIEW_H

#include <QtGui/QWidget>
#include "cliente.h"

#include "clientecontroller.h"

namespace Ui {
    class ClienteAddView;
}

class ClienteAddView : public QWidget {
    Q_OBJECT
public:
    ClienteAddView(QWidget *parent = 0);
    ~ClienteAddView();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ClienteAddView *m_ui;
    Cliente cliente;
    ClienteController clienteController;
    void repaintEmpresa();
    void repaintAll();
    void repaintEstado();
    void repaintNacionalidade();


private slots:
    void accepted();
    bool addEmpresa();
    bool addNacionalidade();
    void cepEdited(QString);
};

#endif // CLIENTEADDVIEW_H
