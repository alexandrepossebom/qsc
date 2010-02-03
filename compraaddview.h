#ifndef COMPRAADDVIEW_H
#define COMPRAADDVIEW_H
#include "formapagamento.h"
#include "cliente.h"

#include "view.h"

namespace Ui {
    class CompraAddView;
}

class CompraAddView : public View {
    Q_OBJECT
public:
    CompraAddView(View *parent = 0);
    ~CompraAddView();

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
    void slotCancel();
};

#endif // COMPRAADDVIEW_H
