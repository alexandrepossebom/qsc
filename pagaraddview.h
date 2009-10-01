#ifndef PAGARADDVIEW_H
#define PAGARADDVIEW_H
#include <QTableWidgetItem>
#include <QtGui/QDialog>
#include <QDebug>

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

private slots:
    void slotNomeChanged(QString nome);
    void slotClienteSelected();
};

#endif // PAGARADDVIEW_H