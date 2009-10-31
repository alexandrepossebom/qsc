#include "pagaraddview.h"
#include "ui_pagaraddview.h"
#include "clientecontroller.h"
#include "compracontroller.h"
#include "parcelacontroller.h"
#include "pagarcontroller.h"
#include <QList>
#include "compra.h"
#include <QStringListModel>
#include <QCompleter>
#include <QTableView>

#include <QRegExp>

PagarAddView::PagarAddView(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::PagarAddView)
{
    m_ui->setupUi(this);

    connect(m_ui->nomeLineEdit,SIGNAL(textEdited(QString)),this,SLOT(slotNomeChanged(QString)));
    connect(m_ui->nomeLineEdit,SIGNAL(returnPressed()),this,SLOT(slotClienteSelected()));
    connect(m_ui->compraTableWidget,SIGNAL(pressed(QModelIndex)),this,SLOT(slotCompraSelected(QModelIndex)));
    connect(m_ui->parcelaTableWidget,SIGNAL(pressed(QModelIndex)),this,SLOT(slotParcelaSelected(QModelIndex)));
    connect(m_ui->doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(slotValorChanged(double)));
    connect(m_ui->buttonBox,SIGNAL(accepted()),this,SLOT(slotOk()));

}
void PagarAddView::slotOk()
{
    PagarController pc;
    bool ok;
    QString error;
    pc.add(&ok,&error,parcela,m_ui->doubleSpinBox->value());


    if(m_ui->checkBox->checkState())
    {
        ParcelaController pc;
        bool ok;
        QString error;
        pc.setPaga(&ok,&error,parcela);
        if (numParcelas == 1)
        {
            CompraController cc;
            cc.setPaga(&ok,&error,compra);
        }
    }
    if(ok)
    {
        repaintPagamento();
        repaintParcelas();
        repaintCompras();
    }
}

void PagarAddView::slotValorChanged(double valor)
{
    if(valor < parcela.valor)
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
    m_ui->doubleSpinBox->setValue(parcela.getValorAberto());
}

void PagarAddView::slotParcelaSelected(QModelIndex modelIndex)
{
    int row = modelIndex.row();
    parcela.id = m_ui->parcelaTableWidget->item(row,0)->text().toInt();
    parcela.valor = m_ui->parcelaTableWidget->item(row,3)->text().replace("R$ ","").toDouble();
    repaintPagamento();
}
void PagarAddView::repaintParcelas()
{
    ParcelaController pc;
    QString error;
    bool ok;
    QList<Parcela> parcelas = pc.getNaoPagasByCompra(&ok,&error,compra);
    numParcelas = parcelas.size();

    QStringList header;
    header << "id" <<  "Data da Compra" << "Valor Parcela" << "Valor Aberto";

    m_ui->parcelaTableWidget->setRowCount( parcelas.size() );
    m_ui->parcelaTableWidget->setColumnCount(4);
    m_ui->parcelaTableWidget->setHorizontalHeaderLabels(header);
    m_ui->parcelaTableWidget->verticalHeader()->hide();
    m_ui->parcelaTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->parcelaTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->parcelaTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    int i = 0;
    while(!parcelas.isEmpty())
    {
        Parcela parcela = parcelas.takeFirst();
        QTableWidgetItem *itemValor = new QTableWidgetItem(parcela.getValorFormatado());
        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(parcela.id));
        QTableWidgetItem *itemData = new QTableWidgetItem(parcela.dataVencimento.toString("dd/MM/yyyy"));
        QString valor;
        valor.append("R$ ");
        valor.append(QString::number(parcela.getValorAberto(),'F',2));
        QTableWidgetItem *itemAberto = new QTableWidgetItem(valor);
        m_ui->parcelaTableWidget->setItem(i,0,itemId);
        m_ui->parcelaTableWidget->setItem(i,2,itemValor);
        m_ui->parcelaTableWidget->setItem(i,1,itemData);
        m_ui->parcelaTableWidget->setItem(i,3,itemAberto);

        i++;
    }
    m_ui->parcelaTableWidget->hideColumn(0);
    m_ui->parcelaTableWidget->resizeColumnsToContents();
    m_ui->parcelaTableWidget->horizontalHeader()->setStretchLastSection( true );
}

void PagarAddView::slotCompraSelected(QModelIndex modelIndex)
{
    int row = modelIndex.row();
    compra.id = m_ui->compraTableWidget->item(row,0)->text().toInt();
    m_ui->doubleSpinBox->setValue(0);
    m_ui->checkBox->setEnabled(false);
    m_ui->checkBox->setChecked(false);
    repaintParcelas();
}

void PagarAddView::repaintCompras()
{
    CompraController cc;
    QString error;
    bool ok;
    QList<Compra> compras = cc.getNaoPagasByCliente(&ok,&error,cliente);

    QStringList header;
    header << "id"  << "Data da Compra" << "Valor" << "itens";

    m_ui->compraTableWidget->setRowCount( compras.size() );
    m_ui->compraTableWidget->setColumnCount(4);
    m_ui->compraTableWidget->setHorizontalHeaderLabels(header);
    m_ui->compraTableWidget->verticalHeader()->hide();
    m_ui->compraTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->compraTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->compraTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int i = 0;
    while(!compras.isEmpty())
    {
        Compra compra = compras.takeFirst();
        QTableWidgetItem *itemValor = new QTableWidgetItem(compra.getValorFormatado());
        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(compra.id));
        QTableWidgetItem *itemData = new QTableWidgetItem(compra.dataCompra.toString("dd/MM/yyyy"));
        QTableWidgetItem *itemItens = new QTableWidgetItem(QString::number(compra.itens));
        m_ui->compraTableWidget->setItem(i,0,itemId);
        m_ui->compraTableWidget->setItem(i,2,itemValor);
        m_ui->compraTableWidget->setItem(i,1,itemData);
        m_ui->compraTableWidget->setItem(i,3,itemItens);
        i++;
    }
    m_ui->compraTableWidget->hideColumn(0);
    m_ui->compraTableWidget->resizeColumnsToContents();
    m_ui->compraTableWidget->horizontalHeader()->setStretchLastSection( true );
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
    bool ok;
    QString error;
    cliente = cc.getClienteByCpf(&ok,&error,cpf);
    repaintCompras();
}

void PagarAddView::slotNomeChanged(QString nome)
{

    ClienteController cc;
    bool ok;
    QString error;
    QList<Cliente> clientes = cc.getClientesByName(&ok,&error,nome,20);

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

    QCompleter *completer = new QCompleter;
    completer->setModel(model);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    completer->setModelSorting(QCompleter::UnsortedModel);
    m_ui->nomeLineEdit->setCompleter(completer);
}

PagarAddView::~PagarAddView()
{
    delete m_ui;
}

void PagarAddView::changeEvent(QEvent *e)
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
