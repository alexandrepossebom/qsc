#include "nacionalidadeaddview.h"
#include "ui_nacionalidadeaddview.h"
#include "nacionalidadecontroller.h"
#include <QMessageBox>

NacionalidadeAddView::NacionalidadeAddView(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::NacionalidadeAddView)
{
    m_ui->setupUi(this);
    connect(m_ui->buttonBox,SIGNAL( accepted() ),this,SLOT( add() ));
}

void NacionalidadeAddView::add()
{
    nacionalidade.setNome( m_ui->nomeLineEdit->text() );
    NacionalidadeController nc;
    if(! nc.add(&nacionalidade))
    {
        QMessageBox *msgBox;
        msgBox = new QMessageBox;
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setText(nc.getError());
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->exec();
    }
}

Nacionalidade NacionalidadeAddView::getNew()
{
    return nacionalidade;
}

NacionalidadeAddView::~NacionalidadeAddView()
{
    delete m_ui;
}

void NacionalidadeAddView::changeEvent(QEvent *e)
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
