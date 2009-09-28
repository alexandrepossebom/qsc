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
#include "cep.h"
#include "cepcontroller.h"
#include "tipotelefonecontroller.h"
#include "tipotelefone.h"
#include "cepaddview.h"
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
    connect(m_ui->estadocivilComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(estadoCivilChanged(QString)));
    connect(m_ui->cepToolButton,SIGNAL(clicked()),this,SLOT(addCep()));

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

bool ClienteAddView::addCep()
{
    CepAddView cav;
    cav.setCep( m_ui->cepLineEdit->text() );
    cav.exec();
    return true;
}

void ClienteAddView::estadoCivilChanged(QString estadoCivil)
{
    if( estadoCivil.indexOf("Casado") != 0)
        m_ui->conjugeGroupBox->setVisible(false);
    else
        m_ui->conjugeGroupBox->setVisible(true);
}

bool ClienteAddView::addNacionalidade()
{
    NacionalidadeAddView nv;
    nv.exec();
    Nacionalidade nacionalidade = nv.getNew();
    if (nacionalidade.getId() > 0)
    {
        QVariant v( nacionalidade.getId() );
        m_ui->nacionalidadeComboBox->addItem( nacionalidade.getNome() , v );
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
    return true;
}

void ClienteAddView::accepted()
{

    //NacionalidadeController nc;
    //nc.getError();

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
    m_ui->conjugeGroupBox->setVisible(false);
    repaintEmpresa();
    repaintEstado();
    repaintNacionalidade();
    repaintTipoTelefone();
}

void ClienteAddView::repaintEmpresa()
{
    EmpresaController ec;
    QList<Empresa> empresas = ec.getAll();
    while (!empresas.isEmpty())
    {
        Empresa empresa = empresas.takeFirst();
        QVariant v(empresa.getId());
        m_ui->empresaComboBox->addItem(empresa.getNome(),v);
        m_ui->conjugeEmpresaComboBox->addItem(empresa.getNome(),v);
    }
}

void ClienteAddView::repaintNacionalidade()
{
    NacionalidadeController nc;
    QList<Nacionalidade> nacionalidades = nc.getAll();
    while (!nacionalidades.isEmpty())
    {
        Nacionalidade nacionalidade = nacionalidades.takeFirst();
        QVariant v(nacionalidade.getId());
        m_ui->nacionalidadeComboBox->addItem(nacionalidade.getNome(),v);
    }
    int br = m_ui->nacionalidadeComboBox->findText("Brasileiro");
    if (br > 0)
        m_ui->nacionalidadeComboBox->setCurrentIndex(br);
}


void ClienteAddView::repaintTipoTelefone()
{
    TipoTelefoneController ttc;
    QList<TipoTelefone> tipos = ttc.getAll();

    while (!tipos.isEmpty())
    {
        TipoTelefone tipo = tipos.takeFirst();
        QVariant v( tipo.getId() );
        m_ui->tp1comboBox->addItem( tipo.getNome() , v );
        m_ui->tp2comboBox->addItem( tipo.getNome() , v );
        m_ui->tp3comboBox->addItem( tipo.getNome() , v );
    }
}
void ClienteAddView::repaintEstado()
{
    EstadoController ec;
    QList<Estado> estados = ec.getAll();

    int pr = 0;
    while(!estados.isEmpty())
    {
        Estado estado = estados.takeFirst();
        QVariant v(estado.getUF());
        m_ui->naturalidadeComboBox->addItem(estado.getNome(),v);
        if(estado.getNome().indexOf("Paran") != -1)
            pr = m_ui->naturalidadeComboBox->count();
    }
    if(pr > 0)
        m_ui->naturalidadeComboBox->setCurrentIndex(pr-1);
}



void ClienteAddView::cepEdited(QString strCep)
{
    strCep = strCep.replace("-","").replace(".","");
    if(strCep.length() == 8)
    {
        CepController cc;
        Cep cep = cc.getByCep(strCep.toInt());

        m_ui->estadoLineEdit->setText( cep.getEstado().getNome() );
        m_ui->cidadeLineEdit->setText( cep.getCidade().getNome() );
        m_ui->bairroLineEdit->setText( cep.getBairro().getNome() );
        m_ui->enderecoLineEdit->setText( cep.getEndereco().getNome() );

    }else{
        m_ui->cidadeLineEdit->clear();
        m_ui->bairroLineEdit->clear();
        m_ui->estadoLineEdit->clear();
        m_ui->enderecoLineEdit->clear();
    }

}
