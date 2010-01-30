#include "clientelist.h"
#include "ui_clientelist.h"
#include <QListWidgetItem>

ClienteList::ClienteList(QWidget *parent) :
        QWidget(parent),
        m_ui(new Ui::ClienteList)
{
    m_ui->setupUi(this);
repaint("");
}

void ClienteList::repaint(QString filter)
{
    bool ok = true;
    QString error;
    foreach(Cliente cliente,clienteController.getClientesByName(&ok,&error,filter,0))
    {
        QListWidgetItem *listItem = new QListWidgetItem();
        listItem->setText(cliente.nome);
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
