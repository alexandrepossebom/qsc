#ifndef VENDAADDVIEW_H
#define VENDAADDVIEW_H
#include "formapagamento.h"
#include "cliente.h"

#include <QtGui/QWidget>

namespace Ui {
    class VendaAddView;
}

class VendaAddView : public QWidget {
    Q_OBJECT
public:
    VendaAddView(QWidget *parent = 0);
    ~VendaAddView();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::VendaAddView *m_ui;
    void repaintFormas();
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


};

#endif // VENDAADDVIEW_H
