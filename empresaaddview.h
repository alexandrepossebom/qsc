#ifndef EMPRESAADDVIEW_H
#define EMPRESAADDVIEW_H

#include <QtGui/QDialog>
#include "empresa.h"
#include <QMessageBox>


namespace Ui {
    class EmpresaAddView;
}

class EmpresaAddView : public QDialog {
    Q_OBJECT
public:
    EmpresaAddView(QWidget *parent = 0);
    ~EmpresaAddView();
    Empresa getNew();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::EmpresaAddView *m_ui;
    Empresa empresa;
private slots:
    void add();
};

#endif // EMPRESAADDVIEW_H
