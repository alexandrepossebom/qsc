#include "cepaddview.h"
#include "ui_cepaddview.h"
#include "cidadecontroller.h"
#include "estadocontroller.h"
#include "enderecocontroller.h"
#include <QDebug>
#include <QList>
#include <QCompleter>


CepAddView::CepAddView(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::CepAddView)
{
    m_ui->setupUi(this);

    connect(m_ui->enderecoLineEdit,SIGNAL(textChanged(QString)),this,SLOT(enderecoChanged(QString)));

    {
        CidadeController cc;
        QList<Cidade> cidades;
        cidades = cc.getAll();

        while (!cidades.isEmpty())
        {
            Cidade cidade;
            cidade = cidades.takeFirst();
            QVariant v(cidade.getId());
            m_ui->cidadeComboBox->addItem(cidade.getNome(),v);

        }
        int pr = m_ui->cidadeComboBox->findText("S.o Jos. dos Pinhais",Qt::MatchFlag(4));
        m_ui->cidadeComboBox->setCurrentIndex(pr);
    }

    {
        EstadoController ec;
        QList<Estado> estados;
        estados = ec.getAll();

        while(!estados.isEmpty())
        {
            Estado estado;
            estado = estados.takeFirst();
            QVariant v(estado.getUF());
            m_ui->estadoComboBox->addItem(estado.getNome(),v);
        }
        int pr = m_ui->estadoComboBox->findText("Paran.",Qt::MatchFlag(4));
        m_ui->estadoComboBox->setCurrentIndex(pr);
    }



//    {
//        EnderecoController ec;
//        QList<Endereco> enderecos;
//        enderecos = ec.getAll();
//
//        while(!enderecos.isEmpty())
//        {
//            Endereco endereco;
//            endereco = enderecos.takeFirst();
//            QVariant v(endereco.getId());
//            m_ui->enderecoComboBox->addItem(endereco.getNome(),v);
//        }
//    }


}

void CepAddView::enderecoChanged(QString nome)
{

    if (nome.length() < 3)
        return;

    EnderecoController ec;
    QList<Endereco> enderecos;
    enderecos = ec.getAll(nome);

    qDebug() << enderecos.size();



    QStringList wordList;
//    QList<QString> enderecosNome;
    while(!enderecos.isEmpty())
    {
        Endereco endereco;
        endereco = enderecos.takeFirst();
//        enderecosNome.append(endereco.getNome());
       wordList << endereco.getNome();
    }
//    wordList.append(enderecosNome);
  QCompleter *completer = new QCompleter(wordList, this);
completer->setCaseSensitivity(Qt::CaseInsensitive);
//completer->setCompletionMode(QCompleter::InlineCompletion);
completer->setModelSorting(QCompleter::UnsortedModel);
m_ui->enderecoLineEdit->setCompleter(completer);



}

void CepAddView::setCep(QString cep)
{
    this->cep = cep;
    m_ui->cepLineEdit->setText(cep);
}

QString CepAddView::getCep()
{
    return cep;
}

QString CepAddView::getError()
{
    return error;
}

CepAddView::~CepAddView()
{
    delete m_ui;
}

void CepAddView::changeEvent(QEvent *e)
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
