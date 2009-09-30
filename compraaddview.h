#ifndef COMPRAADDVIEW_H
#define COMPRAADDVIEW_H
#include "formapagamento.h"
#include "cliente.h"

#include <QtGui/QDialog>

namespace Ui {
    class CompraAddView;
}

class CompraAddView : public QDialog {
    Q_OBJECT
public:
    CompraAddView(QWidget *parent = 0);
    ~CompraAddView();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CompraAddView *m_ui;
    void repaintFormas();
    void repaintVendedores();
    FormaPagamento fp;
    Cliente cliente;
    void refresh();
    void refreshCliente();
    void changeWidgets(bool visible);

private slots:
    void nomeChanged(QString nome);
    void formaChanged(int index);
    void valorChanged(double valor);
    void selectCliente();
    void addCompra();
};

#endif // COMPRAADDVIEW_H
