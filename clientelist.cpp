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
    //    connect(m_ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
    //            this, SLOT(slotClientSelected(QListWidgetItem*)));

    connect(m_ui->columnView,SIGNAL(clicked(QModelIndex)),
            this, SLOT(slotClientSelected(QModelIndex)));
    connect(m_ui->nomeLineEdit,SIGNAL(textChanged(QString)),this,SLOT(repaint(QString)));
    clearLabels();
    model = new QStandardItemModel();
    m_ui->columnView->setModel(model);
    repaint();
}

void ClienteList::repaint(QString filter)
{
    if(filter.length() > 0 && filter.length() < 3)
        return;
    clearLabels();

    model->clear();

    QStandardItem *parentItem = model->invisibleRootItem();
    foreach(Cliente cliente,clienteController.getClientesByName(filter))
    {
        QStandardItem *item = new QStandardItem();
        item->setText(cliente.nome);
        item->setData(qVariantFromValue(cliente),ClientDataRole);
        parentItem->appendRow(item);
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

void ClienteList::paintEmpresa(Cliente cliente)
{
    foreach(Telefone telefone, empresaController.getById(cliente.empresa.id).telefones)
    {
        m_ui->labelEmpresaFone->setText(QString::number(telefone.numero));
    }
}

void ClienteList::paintTelefones(Cliente cliente)
{
    QList<Telefone> fones = telefoneController.getByCliente(cliente);
    foreach(Telefone telefone,fones)
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

void ClienteList::paintCompras(Cliente cliente, QModelIndex index)
{

    QStandardItem *itemCliente = model->itemFromIndex(index);
    if (itemCliente->rowCount() > 0 )
        return;





    QBrush brush;
    QColor color(255,255,255,255);
    brush.setStyle(Qt::Dense4Pattern);
    foreach(Compra compra, compraController.getByCliente(cliente))
    {
        QStandardItem *itemCompra = new QStandardItem;
        QString text;
        text.append("Data Compra: ").append(compra.dataCompra.toString("dd/MM/yyyy"));
        text.append("\nValor Total: ").append(compra.getValorFormatado());
        text.append("\n");

        itemCompra->setText(text);
        if(compra.isAtrasada())
            color.setRgb(255, 0, 0, 40);//vermelho
        else if(compra.paga)
            color.setRgb(124, 252, 0, 240);//verde
        else
            color.setRgb(255,255,255,255);//branco
        brush.setColor(color);
        itemCompra->setBackground(brush);
        itemCliente->appendRow(itemCompra);

        foreach(Parcela parcela,compra.parcelas)
        {

            QStandardItem *itemParcela = new QStandardItem;

            QString text;

            text.append("Vencimento: ").append(parcela.dataVencimento.toString("dd/MM/yyyy"));
            text.append("\nTotal: ").append(parcela.getValorFormatado());
            text.append("\nEm aberto: R$").append( QString::number(parcela.getValorAberto(),'F',2) );
            text.append("\n");

            itemParcela->setText( text );
            itemParcela->setAccessibleText( text );

            if(parcela.paga)
                color.setRgb(124, 252, 0, 255); //verde
            else if(parcela.dataVencimento.operator <=(QDate::currentDate()))
                color.setRgb(255, 0, 0, 255);//vermelho
            else
                color.setRgb(255,255,255,255);//branco

            brush.setColor(color);
            itemParcela->setBackground(brush);
            itemCompra->appendRow(itemParcela);

            foreach(Pagamento pagamento,pagarController.getAllByParcela(parcela))
            {
                QStandardItem *itemPagamento = new QStandardItem;
                if (pagamento.dataPagamento.operator <=(parcela.dataVencimento))
                    color.setRgb(124, 252, 0, 240); //verde
                else
                    color.setRgb(255, 0, 0, 40);//vermelho
                brush.setColor(color);
                itemPagamento->setBackground(brush);
                QString text;
                text.append("Data Pagamento :").append(pagamento.dataPagamento.toString("dd/MM/yyyy"));
                text.append("\nValor Pago: ").append(pagamento.getValorFormatado());
                text.append("\n");
                itemPagamento->setText(text);
                itemParcela->appendRow(itemPagamento);
            }
        }
    }
}

void ClienteList::slotClientSelected(QModelIndex index)
{
    if(index.parent().isValid())
        return;
    clearLabels();
    Cliente cliente = model->data(index,ClientDataRole).value<Cliente>();

    m_ui->labelEmpresaNome->setText(cliente.empresa.nome);


    paintEmpresa(cliente);
    paintTelefones(cliente);
    paintCompras(cliente,index);
}
