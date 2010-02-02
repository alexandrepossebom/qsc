#ifndef CLIENTELIST_H
#define CLIENTELIST_H

#include <QtGui/QWidget>
#include <QListWidgetItem>
#include "clientecontroller.h"
#include "empresacontroller.h"
#include "telefonecontroller.h"
#include "compracontroller.h"
#include "pagarcontroller.h"

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
    EmpresaController empresaController;
    TelefoneController telefoneController;
    CompraController compraController;
    PagarController pagarController;
    void clearLabels();
    void paintEmpresa(Cliente cliente);
    void paintTelefones(Cliente cliente);
    void paintCompras(Cliente cliente);
private slots:
    void repaint(QString);
    void slotClientSelected(QListWidgetItem *item);
};

#endif // CLIENTELIST_H
