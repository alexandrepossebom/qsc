#include "clienteaddview.h"
#include "ui_clienteaddview.h"
#include "empresaaddview.h"
#include "nacionalidadeaddview.h"
#include "nacionalidade.h"
#include "nacionalidadecontroller.h"
#include "empresacontroller.h"
#include "endereco.h"
#include "enderecocontroller.h"
#include "estado.h"
#include "estadocontroller.h"
#include <QDate>
#include <QDebug>


ClienteAddView::ClienteAddView(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ClienteAddView)
{
    m_ui->setupUi(this);

    connect(m_ui->buttonBox,SIGNAL(accepted()),this,SLOT(accepted()));
    connect(m_ui->empresaToolButton,SIGNAL(clicked()),this,SLOT(addEmpresa()));
    connect(m_ui->conjugeEmpresaToolButton,SIGNAL(clicked()),this,SLOT(addEmpresa()));
    connect(m_ui->cepLineEdit,SIGNAL(textChanged(QString)),this,SLOT(cepEdited(QString)));
    connect(m_ui->nacionalidadeToolButton,SIGNAL(clicked()),this,SLOT(addNacionalidade()));

    QDate now = QDate::currentDate();

    // Seta a data de nascimento para 18 anos atras e maximo para 10 anos.
    m_ui->nascimentoDateEdit->setDate(now.addYears(-18));
    m_ui->nascimentoDateEdit->setMaximumDate(now.addYears(-10));

    //Seta a data do RG para hoje e maximo para hoje.
    m_ui->rgEmissaoDateEdit->setMaximumDate(now);
    m_ui->rgEmissaoDateEdit->setDate(now);

    //Desabilita o edit do endereco.
    m_ui->enderecoLineEdit->setEnabled(false);
    m_ui->cidadeLineEdit->setEnabled(false);
    m_ui->bairroLineEdit->setEnabled(false);

repaintAll();

}

bool ClienteAddView::addNacionalidade()
{
    NacionalidadeAddView nv;
    nv.exec();
    Nacionalidade nacionalidade = nv.getNew();
    if (nacionalidade.getId() > 0)
    {
        QVariant v(nacionalidade.getId());
        m_ui->nacionalidadeComboBox->addItem(nacionalidade.getNome(),v);
    }
    return true;
}

bool ClienteAddView::addEmpresa()
{
    EmpresaAddView empresaaddview;
    empresaaddview.exec();
    Empresa empresa = empresaaddview.getNew();
    if (empresa.getId() > 0){
        QVariant v(empresa.getId());
        m_ui->empresaComboBox->addItem(empresa.getNome(),v);
        m_ui->conjugeEmpresaComboBox->addItem(empresa.getNome(),v);
    }
    //repaintEmpresa();
    return true;
}

void ClienteAddView::accepted()
{

    NacionalidadeController nc;
    nc.getError();

//    //cliente = new Cliente();
//    cliente.setNome(m_ui->nomeLineEdit->text());
//
//    Nacionalidade nacionalidade;
//
//
//    nacionalidade.setNome(m_ui->cpfLineEdit->text());
//    cliente.setNacionalidade(nacionalidade);
//
//
//    qDebug() << cliente.getNome();
//    qDebug() << cliente.getNacionalidade().getNome();
//
//    Endereco endereco;
//    endereco.setNome(m_ui->enderecoLineEdit->text());
//    endereco.setCep( m_ui->cepLineEdit->text().replace("-","").toInt() );
//    endereco.setBairro( m_ui->bairroLineEdit->text());
//    endereco.setCidade( m_ui->cidadeLineEdit->text());
//
//    EstadoController estctrl;
//    int estadoIndex = m_ui->estadoComboBox->currentIndex();
//    int estadoId = m_ui->estadoComboBox->itemData( estadoIndex ).toInt();
//
//    endereco.setEstado(  estctrl.getEstadoById( estadoId ) );
//
//
//    EnderecoController ec;
//    ec.add(&endereco);
// //   clienteController.addCliente(cliente);
}

ClienteAddView::~ClienteAddView()
{
    delete m_ui;
}

void ClienteAddView::changeEvent(QEvent *e)
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

void ClienteAddView::repaintAll()
{
    repaintEmpresa();
    repaintEstado();
    repaintNacionalidade();
}

void ClienteAddView::repaintEmpresa()
{
    m_ui->empresaComboBox->clear();
    m_ui->conjugeEmpresaComboBox->clear();
   EmpresaController ec;
    QList<Empresa> empresas;
    empresas = ec.getAll();
    while (!empresas.isEmpty())
    {
        Empresa empresa;
        empresa = empresas.takeFirst();
        QVariant v(empresa.getId());
        m_ui->empresaComboBox->addItem(empresa.getNome(),v);
        m_ui->conjugeEmpresaComboBox->addItem(empresa.getNome(),v);
    }
}

void ClienteAddView::repaintNacionalidade()
{
    m_ui->nacionalidadeComboBox->clear();
    NacionalidadeController nc;
    QList<Nacionalidade> nacionalidades;
    nacionalidades = nc.getAll();
    while (!nacionalidades.isEmpty())
    {
        Nacionalidade nacionalidade;
        nacionalidade = nacionalidades.takeFirst();
        QVariant v(nacionalidade.getId());
        m_ui->nacionalidadeComboBox->addItem(nacionalidade.getNome(),v);
    }
    int br = m_ui->nacionalidadeComboBox->findText("Brasileiro");
    if (br > 0)
        m_ui->nacionalidadeComboBox->setCurrentIndex(br);
}

void ClienteAddView::repaintEstado()
{

    m_ui->estadoComboBox->clear();
    m_ui->naturalidadeComboBox->clear();
    EstadoController ec;
    QList<Estado> estados;
    estados = ec.getAll();

    while (!estados.isEmpty())
    {
        Estado estado;
        estado = estados.takeFirst();
        QVariant v( estado.getId() );
        m_ui->estadoComboBox->addItem( estado.getNome() , v );
        m_ui->naturalidadeComboBox->addItem( estado.getNome() , v );
    }
    int pr = m_ui->estadoComboBox->findText("Paran.",Qt::MatchFlags(4));
    if (pr > 0)
    {
        m_ui->estadoComboBox->setCurrentIndex(pr);
        m_ui->naturalidadeComboBox->setCurrentIndex(pr);
    }
}



void ClienteAddView::cepEdited(QString strCep)
{
    if(strCep.length() == 10)
    {
        int cep;
        cep = strCep.replace("-","").toInt();
        qDebug() << cep;

        EnderecoController ec;

        Endereco endereco;
        endereco = ec.getByCep(cep);

        if(endereco.getCidade().length() == 0)
        {
            m_ui->cidadeLineEdit->setEnabled(true);
            m_ui->cidadeLineEdit->clear();
        }else{
            m_ui->cidadeLineEdit->setEnabled(false);
            m_ui->cidadeLineEdit->setText( endereco.getCidade() );
        }

        if(endereco.getBairro().length() == 0)
        {
            m_ui->bairroLineEdit->setEnabled(true);
            m_ui->bairroLineEdit->clear();
        }else{
             m_ui->bairroLineEdit->setEnabled(false);
             m_ui->bairroLineEdit->setText( endereco.getBairro() );
        }

        if(endereco.getNome().length() == 0)
        {
            m_ui->enderecoLineEdit->setEnabled(true);
            m_ui->enderecoLineEdit->clear();
        }else{
            m_ui->enderecoLineEdit->setEnabled(false);
            m_ui->enderecoLineEdit->setText( endereco.getNome() );
        }
    }
}
