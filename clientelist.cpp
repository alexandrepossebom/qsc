#include "clientelist.h"
#include "ui_clientelist.h"
#include <QListWidgetItem>
#include <QDebug>

#define ClientDataRole Qt::UserRole
Q_DECLARE_METATYPE(Cliente)

ClienteList::ClienteList(QWidget *parent) :
QWidget(parent),
m_ui(new Ui::ClienteList)
{
    m_ui->setupUi(this);
    repaint("");
    connect(m_ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(slotClientSelected(QListWidgetItem*)));
    clearLabels();
}

void ClienteList::repaint(QString filter)
{
    bool ok = true;
    QString error;
    foreach(Cliente cliente,clienteController.getClientesByName(&ok,&error,filter,0))
    {
        QListWidgetItem *listItem = new QListWidgetItem();
        listItem->setText(cliente.nome);
        listItem->setData(ClientDataRole, qVariantFromValue(cliente));
        m_ui->listWidget->addItem(listItem);
    }

}

ClienteList::~ClienteList()
{
    delete m_ui;
}

void ClienteList::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void ClienteList::clearLabels()
{
    m_ui->labelCelular->clear();
    m_ui->labelResidencial->clear();
    m_ui->labelComercial->clear();
    m_ui->labelFax->clear();
    m_ui->labelRecado->clear();
    m_ui->labelEmpresaFone->clear();
    m_ui->labelEmpresaNome->clear();

}

void ClienteList::slotClientSelected(QListWidgetItem *item)
{
    clearLabels();
    Cliente cliente = item->data(ClientDataRole).value<Cliente>();
    m_ui->nomeLineEdit->setText(cliente.nome);
    m_ui->labelEmpresaNome->setText(cliente.empresa.nome);
    cliente.empresa = empresaController.getById(cliente.empresa.id);
    foreach(Telefone telefone, cliente.empresa.telefones)
    {
        m_ui->labelEmpresaFone->setText(QString::number(telefone.numero));
    }
    foreach(Telefone telefone,telefoneController.getByCliente(cliente))
    {
        if(telefone.tipoTelefone.nome.contains("Celular"))
            m_ui->labelCelular->setText(QString::number(telefone.numero));
        else if(telefone.tipoTelefone.nome.contains("Residencial"))
            m_ui->labelResidencial->setText(QString::number(telefone.numero));
        else if(telefone.tipoTelefone.nome.contains("Comercial"))
            m_ui->labelComercial->setText(QString::number(telefone.numero));
        else if(telefone.tipoTelefone.nome.contains("Fax"))
            m_ui->labelFax->setText(QString::number(telefone.numero));
        else if(telefone.tipoTelefone.nome.contains("Recado"))
            m_ui->labelRecado->setText(QString::number(telefone.numero));

    }
}
