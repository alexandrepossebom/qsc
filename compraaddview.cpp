#include "compraaddview.h"
#include "ui_compraaddview.h"
#include "clientecontroller.h"
#include <QDate>
#include <QCompleter>
#include "formapagamentocontroller.h"
#include "vendedorcontroller.h"

CompraAddView::CompraAddView(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::CompraAddView)
{
    m_ui->setupUi(this);
        QDate now = QDate::currentDate();
    m_ui->dataDateEdit->setDate(now);
    m_ui->dataDateEdit->setMaximumDate(now);

    connect(m_ui->nomeClienteLineEdit,SIGNAL(textEdited(QString)),this,SLOT(nomeChanged(QString)));
    connect(m_ui->nomeClienteLineEdit,SIGNAL(returnPressed()),this,SLOT(selectCliente()));
    connect(m_ui->formadePagamentoComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(formaChanged(int)));
    connect(m_ui->valorDoubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(valorChanged(double)));
    connect(m_ui->clienteToolButton,SIGNAL(clicked()),this,SLOT(selectCliente()));

       changeWidgets(true);
    repaintFormas();
    repaintVendedores();
}

CompraAddView::~CompraAddView()
{
    delete m_ui;
}

void CompraAddView::changeEvent(QEvent *e)
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



void CompraAddView::changeWidgets(bool visible)
{
    m_ui->labelCpf->setHidden( visible );
    m_ui->labelObs->setHidden( visible );
    m_ui->labelNascimento->setHidden( visible );
    m_ui->cpfLabel->setHidden( visible );
    m_ui->obsLabel->setHidden( visible );
    m_ui->nascimentoLabel->setHidden( visible );
}

void CompraAddView::selectCliente()
{
    if(m_ui->nomeClienteLineEdit->isEnabled())
    {
        ClienteController cc;
        bool ok;
        QString error;
        cliente = cc.getClienteByName(&ok,&error,m_ui->nomeClienteLineEdit->text());
        if(ok)
        {
            refreshCliente();
        }
    }else{
        m_ui->nomeClienteLineEdit->setEnabled(true);
        changeWidgets(true);
        cliente.setId(0);
    }
}

void CompraAddView::refreshCliente()
{
    if(cliente.getId() > 0)
    {
        m_ui->nomeClienteLineEdit->setEnabled(false);
        m_ui->cpfLabel->setText(cliente.getCpfFormated());
        m_ui->nascimentoLabel->setText(cliente.getDataNascimento().toString("dd/MM/yyyy"));
        changeWidgets(false);
    }
}

void CompraAddView::valorChanged(double valor)
{
    refresh();
}
void CompraAddView::refresh()
{
    m_ui->parcelasLabel->setText(QString::number(fp.getParcelas()));
    m_ui->descontoLabel->setText(QString::number(fp.getDesconto()*100).append(" %"));

    if(fp.getJuro() != 0)
        m_ui->juroLabel->setText(QString::number( (fp.getJuro()*100) -100 ).append(" %"));
    else
        m_ui->juroLabel->setText("0 %");

    int valor = m_ui->valorDoubleSpinBox->value();
    valor = valor / fp.getParcelas();

    QString valorString = "R$ ";
    if (fp.getDesconto() != 0 )
        valorString.append( QString::number(valor * ( 1 - fp.getDesconto()),'f',2) );
    else if ( fp.getJuro() != 0 )
        valorString.append( QString::number(valor * fp.getJuro(),'f',2) );
    else
        valorString.append( QString::number(valor,'f',2) );

    m_ui->valorLabel->setText(valorString);

    if(fp.isEntrada())
        m_ui->entradaLabel->setText("Sim");
    else
        m_ui->entradaLabel->setText(QString("Não").toAscii());
}

void CompraAddView::formaChanged(int index)
{
    int id = m_ui->formadePagamentoComboBox->itemData( index ).toInt();
    FormaPagamentoController fpc;
    bool ok;
    QString error;
    fp = fpc.getById(&ok,&error,id);
    refresh();
}

void CompraAddView::nomeChanged(QString nome)
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

void CompraAddView::repaintFormas()
{
  FormaPagamentoController fpc;
  bool ok;
  QString error;
    QList<FormaPagamento> formas = fpc.getAll(&ok,&error);
    int index = 0;
    while (!formas.isEmpty())
    {
        FormaPagamento forma = formas.takeFirst();
        QVariant v(forma.getId());
        m_ui->formadePagamentoComboBox->addItem(forma.getNome(),v);
        if (forma.getNome().indexOf("Vista") != -1)
            index = m_ui->formadePagamentoComboBox->count() -1;
    }
    m_ui->formadePagamentoComboBox->setCurrentIndex( index );
}

void CompraAddView::repaintVendedores()
{
  VendedorController vc;
  bool ok;
  QString error;
    QList<Vendedor> *vendedores = vc.getAll(&ok,&error);
    int index = 0;
    while (!vendedores->isEmpty())
    {
        Vendedor vendedor;
        vendedor = vendedores->takeFirst();
        QVariant v(vendedor.getId());
        m_ui->vendedorComboBox->addItem(vendedor.getNome(),v);
        if (vendedor.getNome().indexOf("Arlete") != -1)
            index = m_ui->vendedorComboBox->count() -1;
    }
    m_ui->vendedorComboBox->setCurrentIndex( index );
}

