#include "empresaaddview.h"
#include "ui_empresaaddview.h"
#include <QDebug>
#include "empresacontroller.h"
#include "cepcontroller.h"
#include "tipotelefonecontroller.h"
#include "telefone.h"

EmpresaAddView::EmpresaAddView(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::EmpresaAddView)
{
    m_ui->setupUi(this);
    connect(m_ui->buttonBox,SIGNAL(accepted()),this,SLOT(add()));
    connect(m_ui->cepLineEdit,SIGNAL(textEdited(QString)),this,SLOT(cepChanged(QString)));
    repaintTipoTelefone();
}

void EmpresaAddView::cepChanged(QString cepString)
{
    cepString = cepString.replace(".","").replace("-","");
    int cepNumber = cepString.toInt();
    if(cepString.length() < 8)
        return;
    CepController cc;
    bool ok;
    QString error;
    Cep cep = cc.getByCep(&ok,&error,cepNumber);

    m_ui->bairroLineEdit->setText(cep.bairro.nome);
    m_ui->enderecoLineEdit->setText(cep.endereco.nome);
    m_ui->estadoLineEdit->setText(cep.estado.nome);
    m_ui->cidadeLineEdit->setText(cep.cidade.nome);
}

void EmpresaAddView::repaintTipoTelefone()
{
    TipoTelefoneController ttc;
    QList<TipoTelefone> tipostelefones = ttc.getAll();
    while(!tipostelefones.isEmpty())
    {
        TipoTelefone tt = tipostelefones.takeFirst();
        m_ui->tipoFone01comboBox->addItem(tt.nome,QVariant(tt.id));
        m_ui->tiporFone02comboBox->addItem(tt.nome,QVariant(tt.id));
    }
}

EmpresaAddView::~EmpresaAddView()
{
    delete m_ui;
}

void EmpresaAddView::add()
{
    EmpresaController ec;
    empresa.setNome(m_ui->nomeLineEdit->text());
    empresa.cep.cep = m_ui->cepLineEdit->text().replace(".","").replace("-","").toInt();
    empresa.numero = m_ui->numeroSpinBox->value();

    int id = 0;
         Telefone telefone;
        TipoTelefone tipoTelefone;
    if ( m_ui->fone01lineEdit->text().length() > 8)
    {

        id = m_ui->tipoFone01comboBox->currentIndex();
        tipoTelefone.id = m_ui->tipoFone01comboBox->itemData(id).toInt();

        telefone.tipoTelefone = tipoTelefone;
        telefone.numero = m_ui->fone01lineEdit->text().replace("(","").replace(") ","").replace("-","").toLongLong();
        empresa.telefones.append(telefone);
    }
    if (m_ui->fone02LineEdit->text().length() >8){
        id = m_ui->tiporFone02comboBox->currentIndex();
        telefone.id = m_ui->tiporFone02comboBox->itemData( id ).toInt();

        telefone.numero = m_ui->fone02LineEdit->text().replace("(","").replace(") ","").replace("-","").toLongLong();
        empresa.telefones.append(telefone);
    }

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
