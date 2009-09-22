#include "empresaaddview.h"
#include "ui_empresaaddview.h"
#include <QDebug>
#include "empresacontroller.h"

EmpresaAddView::EmpresaAddView(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::EmpresaAddView)
{
    m_ui->setupUi(this);
    connect(m_ui->buttonBox,SIGNAL(accepted()),this,SLOT(add()));
}

EmpresaAddView::~EmpresaAddView()
{
    delete m_ui;
}

void EmpresaAddView::add()
{
    qDebug() << "oi";
    EmpresaController ec;
    empresa.setNome(m_ui->nomeLineEdit->text());
     if(!ec.addEmpresa(&empresa))
    {
        QMessageBox *msgBox;
        msgBox = new QMessageBox;
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setText(ec.getError());
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->exec();
    }
}

Empresa EmpresaAddView::getNew()
{
    return empresa;
}

void EmpresaAddView::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
