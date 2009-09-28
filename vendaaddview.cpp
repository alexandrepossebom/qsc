#include "vendaaddview.h"
#include "ui_vendaaddview.h"
#include "clientecontroller.h"
#include "cliente.h"
#include <QDate>
#include <QCompleter>
#include "formapagamentocontroller.h"

VendaAddView::VendaAddView(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::VendaAddView)
{
    m_ui->setupUi(this);
    QDate now = QDate::currentDate();
    m_ui->dataDateEdit->setDate(now);
    m_ui->dataDateEdit->setMaximumDate(now);

    connect(m_ui->nomeClienteLineEdit,SIGNAL(textEdited(QString)),this,SLOT(nomeChanged(QString)));

    repaintFormas();

}

void VendaAddView::nomeChanged(QString nome)
{
    if (nome.length() < 3)
        return;
    bool ok;
    QString error;

    ClienteController cc;
    QList<Cliente> clientes = cc.getClientesByName(&ok,&error,nome,20);

    QStringList wordList;

    while(!clientes.isEmpty())
    {
        wordList.append(clientes.takeFirst().getNome());
    }
    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    completer->setModelSorting(QCompleter::UnsortedModel);
    m_ui->nomeClienteLineEdit->setCompleter(completer);

}


VendaAddView::~VendaAddView()
{
    delete m_ui;
}

void VendaAddView::changeEvent(QEvent *e)
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

void VendaAddView::repaintFormas()
{
  FormaPagamentoController fpc;
  bool ok;
  QString error;
    QList<FormaPagamento> formas = fpc.getAll(&ok,&error);
    while (!formas.isEmpty())
    {
        FormaPagamento forma = formas.takeFirst();
        QVariant v(forma.getId());
        m_ui->formadePagamentoComboBox->addItem(forma.getNome(),v);
    }
}
