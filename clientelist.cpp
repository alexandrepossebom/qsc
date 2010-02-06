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
    connect(m_ui->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(slotClientSelected(QListWidgetItem*)));

    connect(m_ui->nomeLineEdit,SIGNAL(textChanged(QString)),this,SLOT(repaint(QString)));
    clearLabels();
    QStringList labels;
    labels << tr("Data") << tr("Valor");
    m_ui->treeWidget->header()->setResizeMode(QHeaderView::Stretch);
    m_ui->treeWidget->setHeaderLabels(labels);
    m_ui->treeWidget->setColumnCount(2);
    repaint();
}

void ClienteList::repaint(QString filter)
{
    if(filter.length() > 0 && filter.length() < 3)
        return;
    m_ui->listWidget->clear();
    m_ui->treeWidget->clear();
    clearLabels();
    foreach(Cliente cliente,clienteController.getClientesByName(filter))
    {
        QListWidgetItem *listItem = new QListWidgetItem();
        listItem->setText(cliente.nome);
        listItem->setData(ClientDataRole, qVariantFromValue(cliente));
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

void ClienteList::paintCompras(Cliente cliente)
{
    m_ui->treeWidget->clear();
    QColor color(255,255,255,255);
    foreach(Compra compra, compraController.getByCliente(cliente))
    {
        QTreeWidgetItem *compraItem = new QTreeWidgetItem(m_ui->treeWidget);
        compraItem->setText(0, compra.dataCompra.toString("dd/MM/yyyy") );
        compraItem->setText(1, compra.getValorFormatado() );
        if(compra.isAtrasada())
            color.setRgb(255, 0, 0, 40);//vermelho
        else if(compra.paga)
            color.setRgb(124, 252, 0, 240);//verde
        else
            color.setRgb(255,255,255,255);//branco

        compraItem->setBackgroundColor(0,color);
        compraItem->setBackgroundColor(1,color);

        foreach(Parcela parcela,compra.parcelas)
        {
            QString valor;
            valor.append("R$ ");
            valor.append(QString::number(parcela.getValorAberto(),'F',2));

            QTreeWidgetItem *parcelaItem = new QTreeWidgetItem(compraItem);
            if(parcela.paga)
                color.setRgb(124, 252, 0, 240); //verde
            else if(parcela.dataVencimento.operator <=(QDate::currentDate()))
                color.setRgb(255, 0, 0, 40);//vermelho
            else
                color.setRgb(255,255,255,255);//branco

            parcelaItem->setBackgroundColor(0,color);
            parcelaItem->setBackgroundColor(1,color);
            parcelaItem->setBackgroundColor(2,color);
            parcelaItem->setText(0,parcela.dataVencimento.toString("dd/MM/yyyy"));
            parcelaItem->setText(1,parcela.getValorFormatado());            
            parcelaItem->setText(2,valor);
            foreach(Pagamento pagamento,pagarController.getAllByParcela(parcela))
            {
                QTreeWidgetItem *pagamentoItem = new QTreeWidgetItem(parcelaItem);
                if (pagamento.dataPagamento.operator <=(parcela.dataVencimento))
                    color.setRgb(124, 252, 0, 240); //verde
                else
                    color.setRgb(255, 0, 0, 40);//vermelho
                pagamentoItem->setBackgroundColor(0,color);
                pagamentoItem->setBackgroundColor(1,color);
                pagamentoItem->setText(0,pagamento.dataPagamento.toString("dd/MM/yyyy"));
                pagamentoItem->setText(1,pagamento.getValorFormatado());
            }
        }
    }
}

void ClienteList::slotClientSelected(QListWidgetItem *item)
{
    clearLabels();
    Cliente cliente = item->data(ClientDataRole).value<Cliente>();
    m_ui->labelEmpresaNome->setText(cliente.empresa.nome);

    paintEmpresa(cliente);
    paintTelefones(cliente);
    paintCompras(cliente);
}
