#include "compraaddview.h"
#include "ui_compraaddview.h"
#include "clientecontroller.h"
#include <QDate>
#include <QCompleter>
#include "formapagamentocontroller.h"
#include "vendedorcontroller.h"
#include "compracontroller.h"
#include <QStringListModel>
#include <QMessageBox>


CompraAddView::CompraAddView(View *parent) :
        View(parent),
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
    connect(m_ui->buttonBox,SIGNAL(accepted()),this,SLOT(addCompra()));
    connect(m_ui->buttonBox,SIGNAL(rejected()),this,SLOT(slotCancel()));

    changeWidgets(true);
    repaintFormas();
    repaintVendedores();
}

void CompraAddView::slotCancel()
{
    this->close();
}

void CompraAddView::addCompra()
{
    //  Forma Pagamento
    int fpIndex = m_ui->formadePagamentoComboBox->currentIndex();
    int fpId = m_ui->formadePagamentoComboBox->itemData( fpIndex ).toInt();

    FormaPagamentoController fpc;
    fp = fpc.getById(fpId);

    Vendedor vendedor;
    int vendedorIndex = m_ui->vendedorComboBox->currentIndex();
    vendedor.setId( m_ui->vendedorComboBox->itemData( vendedorIndex ).toInt() );

    Compra compra;
    compra.cliente = cliente;
    compra.formaPagamento = fp;
    compra.formaPagamento.id = fpId;
    compra.vendedor = vendedor;

    compra.itens = m_ui->itensSpinBox->value();
    compra.paga = false;
    compra.valor = m_ui->valorDoubleSpinBox->value();

    compra.dataCompra = m_ui->dataDateEdit->date();
    QString error;
    if(cliente.nome.length() == 0)
        error.append(QString::fromUtf8("- Cliente inválido.\n"));
    if(compra.valor == 0)
        error.append(QString::fromUtf8("- Valor inválido.\n"));
    if(compra.itens == 0)
        error.append(QString::fromUtf8("- Número de itens inválido.\n"));
    if(error.length())
    {
        QMessageBox *msgBox;
        msgBox = new QMessageBox;
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setText(error);
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->exec();
        return;
    }
    CompraController cc;
    if(cc.Add(compra))
        this->close();
}

CompraAddView::~CompraAddView()
{
    delete m_ui;
}

void CompraAddView::changeWidgets(bool visible)
{
    m_ui->labelCpf->setHidden( visible );
    m_ui->labelObs->setHidden( visible );
    m_ui->cpfLabel->setHidden( visible );
    m_ui->obsLabel->setHidden( visible );
    m_ui->nascimentoLabel->setHidden( visible );
    m_ui->labelNascimento->setHidden( visible );
}

void CompraAddView::selectCliente()
{
    QRegExp rx("(\\d{3}\\.\\d{3}\\.\\d{3}-\\d{2})");

    long long int cpf = 0;
    int pos = rx.indexIn( m_ui->nomeClienteLineEdit->text() );
    if (pos > -1)
    {
        cpf = rx.cap(1).replace(".","").replace("-","").toLongLong();
    }else{
        return;
    }
    ClienteController cc;
    cliente = cc.getClienteByCpf(cpf);

    if(cliente.id > 0)
    {
        changeWidgets(true);
        refreshCliente();
    }
}

void CompraAddView::refreshCliente()
{
    if(cliente.getId() > 0)
    {
        m_ui->nomeClienteLineEdit->setEnabled(false);
        m_ui->cpfLabel->setText(cliente.getCpfFormated());
        m_ui->nascimentoLabel->setText(cliente.getDataNascimento().toString("dd/MM/yyyy"));
        m_ui->obsLabel->setText(cliente.aviso);
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

    double valor = m_ui->valorDoubleSpinBox->value();

    double parcela_valor = valor / fp.parcelas ;
    if (fp.desconto != 0)
        parcela_valor = parcela_valor * (1 - fp.desconto);
    else if ( fp.juro != 0)
        parcela_valor = parcela_valor * fp.juro;

    QString valorString = QString("R$ %1").arg(parcela_valor, 0, 'F', 2);

    m_ui->valorLabel->setText(valorString);

    if(fp.isEntrada())
        m_ui->entradaLabel->setText("Sim");
    else
        m_ui->entradaLabel->setText("Nao");
}

void CompraAddView::formaChanged(int index)
{
    int id = m_ui->formadePagamentoComboBox->itemData( index ).toInt();
    FormaPagamentoController fpc;
    fp = fpc.getById(id);
    refresh();
}

void CompraAddView::nomeChanged(QString nome)
{
    if (nome.length() < 3)
        return;

    ClienteController cc;
    bool ok;
    QString error;
    QList<Cliente> clientes = cc.getClientesByName(nome);

    QStringListModel *model = new QStringListModel();

    QStringList list;
    while(!clientes.isEmpty())
    {
        Cliente cliente = clientes.takeFirst();

        QString string;
        string.append(cliente.nome);
        string.append(" - ");
        string.append(cliente.getCpfFormated());
        string.append(" - ");
        string.append(cliente.dataNascimento.toString("dd/MM/yyyy"));

        list.append(string);

    }

    model->setStringList(list);

    completer = new QCompleter;
    completer->setModel(model);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    completer->setModelSorting(QCompleter::UnsortedModel);

    m_ui->nomeClienteLineEdit->setCompleter(completer);
    connect(completer,SIGNAL(activated(QString)),this,SLOT(selectCliente()));

}

void CompraAddView::repaintFormas()
{
    FormaPagamentoController fpc;
    QList<FormaPagamento> formas = fpc.getAll();
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
    QList<Vendedor> vendedores = vc.getAll();
    int index = 0;
    while (!vendedores.isEmpty())
    {
        Vendedor vendedor;
        vendedor = vendedores.takeFirst();
        QVariant v(vendedor.getId());
        m_ui->vendedorComboBox->addItem(vendedor.getNome(),v);
        if (vendedor.getNome().indexOf("Arlete") != -1)
            index = m_ui->vendedorComboBox->count() -1;
    }
    m_ui->vendedorComboBox->setCurrentIndex( index );
}

