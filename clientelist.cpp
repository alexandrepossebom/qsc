#include "clientelist.h"
#include "ui_clientelist.h"

ClienteList::ClienteList(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ClienteList)
{
    m_ui->setupUi(this);
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
