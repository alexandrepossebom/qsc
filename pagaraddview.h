#ifndef PAGARADDVIEW_H
#define PAGARADDVIEW_H
#include <QTreeWidgetItem>
#include <QDebug>
#include "cliente.h"
#include "compra.h"
#include "parcela.h"
#include "view.h"
#include <QCompleter>

namespace Ui {
    class PagarAddView;
}

class PagarAddView : public View {
    Q_OBJECT
public:
    PagarAddView(View *parent = 0);
    ~PagarAddView();

private:
    Ui::PagarAddView *m_ui;
    Cliente cliente;
    Compra compra;
    Parcela parcela;
    QList<Compra> compras;
    int numParcelas;
    void repaintCompras();
    void repaintPagamento();
    QCompleter *completer;
private slots:
    void slotNomeChanged(QString nome);
    void slotClienteSelected();
    void slotParcelaSelected(QTreeWidgetItem* item,int id);
    void slotValorChanged(double);
    void slotOk();
    void slotCancel();
};

#endif // PAGARADDVIEW_H
