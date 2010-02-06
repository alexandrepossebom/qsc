#include "pagaraddview.h"
#include "ui_pagaraddview.h"
#include "clientecontroller.h"
#include "compracontroller.h"
#include "parcelacontroller.h"
#include "pagarcontroller.h"
#include <QList>
#include "compra.h"
#include <QStringListModel>
#include <QRegExp>

#define ParcelaDataRole Qt::UserRole
Q_DECLARE_METATYPE(Parcela)


PagarAddView::PagarAddView(View *parent) :
        View(parent),
        m_ui(new Ui::PagarAddView)
{
    m_ui->setupUi(this);

    connect(m_ui->nomeLineEdit,SIGNAL(textEdited(QString)),this,SLOT(slotNomeChanged(QString)));
    connect(m_ui->nomeLineEdit,SIGNAL(returnPressed()),this,SLOT(slotClienteSelected()));

    connect(m_ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(slotParcelaSelected(QTreeWidgetItem*,int)));
    connect(m_ui->doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(slotValorChanged(double)));
    connect(m_ui->buttonBox,SIGNAL(accepted()),this,SLOT(slotOk()));
    connect(m_ui->buttonBox,SIGNAL(rejected()),this,SLOT(slotCancel()));

    m_ui->checkBox->setEnabled(false);
    m_ui->doubleSpinBox->setEnabled(false);


    QStringList labels;
    labels << tr("Data") << tr("Valor Total") << tr("Valor Aberto") << tr("Valor Sugerido");
    m_ui->treeWidget->header()->setResizeMode(QHeaderView::Stretch);
    m_ui->treeWidget->setHeaderLabels(labels);
    m_ui->treeWidget->setColumnCount(4);
}
void PagarAddView::slotOk()
{
    PagarController pc;
    bool ok;
    ok = pc.add(parcela,m_ui->doubleSpinBox->value());


    if(m_ui->checkBox->checkState())
    {
        ParcelaController pc;
        bool ok;
        QString error;
        pc.setPaga(parcela);
        if (compra.parcelas.size() == 1)
        {
            CompraController cc;
            ok = cc.setPaga(compra);
        }
    }
    if(ok)
    {
        m_ui->treeWidget->clear();
        repaintPagamento();
        repaintCompras();
    }
}

void PagarAddView::slotValorChanged(double valorDouble)
{
    float valor = (float)valorDouble;
    float valorAberto = parcela.getValorAberto();
    if(valor < valorAberto)
    {
        m_ui->checkBox->setEnabled(false);
        m_ui->checkBox->setChecked(false);
    } else {
        m_ui->checkBox->setEnabled(true);
        m_ui->checkBox->setChecked(true);
    }
}

void PagarAddView::repaintPagamento()
{
    m_ui->doubleSpinBox->setValue(parcela.getValorSugerido());
    m_ui->doubleSpinBox->setMaximum(parcela.getValorSugerido());
}

void PagarAddView::slotParcelaSelected(QTreeWidgetItem* item,int id)
{
    if(!item->parent())
        return;
    parcela = item->data(0,ParcelaDataRole).value<Parcela>();
    repaintPagamento();
    m_ui->doubleSpinBox->setEnabled(true);
}

void PagarAddView::repaintCompras()
{
    compras.clear();
    m_ui->treeWidget->clear();

    CompraController cc;
    compras = cc.getNaoPagasByCliente(cliente);

    foreach(Compra compra, compras)
    {
        QTreeWidgetItem *compraItem = new QTreeWidgetItem(m_ui->treeWidget);
        compraItem->setText(0, compra.dataCompra.toString("dd/MM/yyyy") );
        compraItem->setText(1, compra.getValorFormatado() );

        foreach(Parcela parcela,compra.parcelas)
        {
            QString valorAberto;
            valorAberto.append("R$ ");
            valorAberto.append(QString::number(parcela.getValorAberto(),'F',2));

            QString valorSugerido;
            valorSugerido.append("R$ ");
            valorSugerido.append(QString::number(parcela.getValorSugerido(),'F',2));

            QTreeWidgetItem *parcelaItem = new QTreeWidgetItem(compraItem);
            parcelaItem->setText(0,parcela.dataVencimento.toString("dd/MM/yyyy"));
            parcelaItem->setText(1,parcela.getValorFormatado());
            parcelaItem->setText(2,valorAberto);
            parcelaItem->setText(3,valorSugerido);
            parcelaItem->setData(0,ParcelaDataRole, qVariantFromValue(parcela));
        }
    }

    m_ui->treeWidget->expandAll();
}

void PagarAddView::slotClienteSelected()
{
    QRegExp rx("(\\d{3}\\.\\d{3}\\.\\d{3}-\\d{2})");

    long long int cpf = 0;
    int pos = rx.indexIn( m_ui->nomeLineEdit->text() );
    if (pos > -1)
    {
        cpf = rx.cap(1).replace(".","").replace("-","").toLongLong();
    }else{
        return;
    }
    ClienteController cc;
    cliente = cc.getClienteByCpf(cpf);
    repaintCompras();
}

void PagarAddView::slotNomeChanged(QString nome)
{
    if (nome.length() < 3)
        return;

    m_ui->treeWidget->clear();

    ClienteController cc;
    QStringListModel *model = new QStringListModel();

    QStringList list;
    foreach(Cliente cliente,cc.getClientesByName(nome,20) )
    {
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
    m_ui->nomeLineEdit->setCompleter(completer);
    connect(completer,SIGNAL(activated(QString)),this,SLOT(slotClienteSelected()));
}

void PagarAddView::slotCancel()
{
    this->close();
}

PagarAddView::~PagarAddView()
{
    delete m_ui;
}
