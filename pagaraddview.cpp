#include "pagaraddview.h"
#include "ui_pagaraddview.h"
#include "clientecontroller.h"
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

}

void PagarAddView::slotClienteSelected()
{
    QRegExp rx("(\\d{3}\.\\d{3}\.\\d{3}-\\d{2})");

    long long int cpf = 0;
    int pos = rx.indexIn( m_ui->nomeLineEdit->text() );
    if (pos > -1) {
        cpf = rx.cap(1).replace(".","").replace("-","").toLongLong();
    }
    qDebug() << cpf;

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
