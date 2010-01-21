#ifndef PAGARADDVIEW_H
#define PAGARADDVIEW_H
#include <QTreeWidgetItem>
#include <QtGui/QDialog>
#include <QDebug>
#include "cliente.h"
#include "compra.h"
#include "parcela.h"

namespace Ui {
    class PagarAddView;
}

class PagarAddView : public QDialog {
    Q_OBJECT
public:
    PagarAddView(QWidget *parent = 0);
    ~PagarAddView();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PagarAddView *m_ui;
    Cliente cliente;
    Compra compra;
    Parcela parcela;
    QList<Parcela> parcelas;
    int numParcelas;
    void repaintCompras();
    void repaintPagamento();

private slots:
    void slotNomeChanged(QString nome);
    void slotClienteSelected();
    void slotParcelaSelected(QTreeWidgetItem* item,int id);
    void slotValorChanged(double);
    void slotOk();
};

#endif // PAGARADDVIEW_H
