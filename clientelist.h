#ifndef CLIENTELIST_H
#define CLIENTELIST_H

#include <QtGui/QWidget>
#include <QListWidgetItem>
#include <QStandardItemModel>
#include "clientecontroller.h"
#include "empresacontroller.h"
#include "telefonecontroller.h"
#include "compracontroller.h"
#include "pagarcontroller.h"
#include <QLabel>

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
    QStandardItemModel *model;
    void paintEmpresa(Cliente cliente);
    void paintTelefones(Cliente cliente);
    void paintCompras(Cliente cliente,QModelIndex item);
    QLabel *label;
private slots:
    void repaint(QString filter = 0);
    void slotClientSelected(QModelIndex item);
};

#endif // CLIENTELIST_H
