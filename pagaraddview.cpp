#include "pagaraddview.h"
#include "ui_pagaraddview.h"
#include "clientecontroller.h"
#include "compracontroller.h"
#include <QList>
#include "compra.h"
#include <QStringListModel>
#include <QCompleter>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QtSql>
 #include <QRegExp>

PagarAddView::PagarAddView(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::PagarAddView)
{
    m_ui->setupUi(this);

    connect(m_ui->nomeLineEdit,SIGNAL(textEdited(QString)),this,SLOT(slotNomeChanged(QString)));
    connect(m_ui->nomeLineEdit,SIGNAL(returnPressed()),this,SLOT(slotClienteSelected()));
    connect(m_ui->compraTableWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slotCompraSelected()));

}
void PagarAddView::slotCompraSelected()
{
    int row = m_ui->compraTableWidget->currentRow();
    qDebug() << m_ui->compraTableWidget->item(row-1,2)->text();
}

void PagarAddView::repaintCompras()
{
    CompraController cc;
    QString error;
    bool ok;
    QList<Compra> compras = cc.getNaoPagasByCliente(&ok,&error,cliente);

    QStringList header;
    header << "Valor" << "Data da Compra";

    m_ui->compraTableWidget->setRowCount( compras.size() );
    m_ui->compraTableWidget->setColumnCount(3);
    m_ui->compraTableWidget->setHorizontalHeaderLabels(header);
    m_ui->compraTableWidget->verticalHeader()->hide();
    m_ui->compraTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui->compraTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->compraTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int i = 0;
    while(!compras.isEmpty())
    {
        Compra compra = compras.takeFirst();
        QTableWidgetItem *itemValor = new QTableWidgetItem(QString::number(compra.valor));
        QTableWidgetItem *itemId = new QTableWidgetItem(QString::number(compra.id));
        QTableWidgetItem *itemData = new QTableWidgetItem(compra.dataCompra.toString("dd/MM/yyyy"));
        m_ui->compraTableWidget->setItem(i,0,itemValor);
        m_ui->compraTableWidget->setItem(i,1,itemData);
        m_ui->compraTableWidget->setItem(i,2,itemId);
        i++;
    }
    m_ui->compraTableWidget->hideColumn(2);
    m_ui->compraTableWidget->adjustSize();
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
    qDebug() << cliente.dataNascimento;

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
