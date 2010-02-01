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
#include "conjugecontroller.h"
#include "cidadecontroller.h"
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
    if (empresa.id > 0){
        QVariant v(empresa.id);
        m_ui->empresaComboBox->addItem(empresa.nome,v);
        m_ui->conjugeEmpresaComboBox->addItem(empresa.nome,v);
    }
    return true;
}

void ClienteAddView::accepted()
{
    int i = 0;
    Cliente cliente;
    cliente.setNome( m_ui->nomeLineEdit->text() );

    cliente.setCpf( m_ui->cpfLineEdit->text().replace(".","").replace("-","").toLongLong() );
    cliente.setEstadoCivil( m_ui->estadocivilComboBox->currentText() );
    cliente.setDataNascimento( m_ui->nascimentoDateEdit->date() );

    Cidade cidade;
    i = m_ui->localNascimentoComboBox->currentIndex();
    cidade.id =  m_ui->localNascimentoComboBox->itemData(i).toInt();
    cliente.localNascimento = cidade;


    Nacionalidade nacionalidade;

    nacionalidade.setNome( m_ui->nacionalidadeComboBox->currentText() );
    i = m_ui->nacionalidadeComboBox->currentIndex();
    nacionalidade.setId( m_ui->nacionalidadeComboBox->itemData(i).toInt() );

    cliente.setNacionalidade(nacionalidade);

    Naturalidade naturalidade;
    naturalidade.setNome( m_ui->naturalidadeComboBox->currentText());
    i = m_ui->naturalidadeComboBox->currentIndex();
    naturalidade.setUF( m_ui->naturalidadeComboBox->itemData( i ).toString() );
    cliente.setNaturalidade(naturalidade);

    cliente.setNomeMae( m_ui->nomeMaeLineEdit->text() );
    cliente.setNomePai( m_ui->nomePaiLineEdit->text() );

    cliente.setRg( m_ui->rgLineEdit->text() );
    cliente.setRgOrgaoEmissor( m_ui->rgEmissorLineEdit->text() );
    cliente.setRgDataEmissao( m_ui->rgEmissaoDateEdit->date() );

    Empresa empresa;
    i = m_ui->empresaComboBox->currentIndex();
    empresa.id =  m_ui->empresaComboBox->itemData( i ).toInt() ;
    empresa.nome =  m_ui->empresaComboBox->currentText() ;

    cliente.setEmpresa(empresa);
    cliente.setCargo( m_ui->cargoLineEdit->text() );
    cliente.setRenda( m_ui->rendaDoubleSpinBox->value() );

    cliente.setEndercoNumero( m_ui->enderecoNumeroSpinBox->value() );

    Cep cep;
    cep.setCep( m_ui->cepLineEdit->text().replace(".","").replace("-","").toInt() );
    cliente.setCep( cep );

    Telefone telefone;
    TipoTelefone tipoTelefone;
    int id = 0;
    if ( m_ui->fone1LineEdit->text().length() > 8)
    {
        id = m_ui->tp1comboBox->currentIndex();
        tipoTelefone.id = m_ui->tp1comboBox->itemData(id).toInt();

        telefone.tipoTelefone = tipoTelefone;
        telefone.numero = m_ui->fone1LineEdit->text().replace("(","").replace(") ","").replace("-","").toLongLong();
        cliente.telefones.append(telefone);
    }
    if ( m_ui->fone2LineEdit->text().length() > 8)
    {
        id = m_ui->tp2comboBox->currentIndex();
        tipoTelefone.id = m_ui->tp2comboBox->itemData(id).toInt();

        telefone.tipoTelefone = tipoTelefone;
        telefone.numero = m_ui->fone2LineEdit->text().replace("(","").replace(") ","").replace("-","").toLongLong();
        cliente.telefones.append(telefone);
    }

    ClienteController cc;
    bool ok = true;
    QString error;
    cc.addCliente(&ok,&error,&cliente);
    if(!ok)
    {
        QMessageBox *msgBox;
        msgBox = new QMessageBox;
        msgBox->setIcon(QMessageBox::Warning);
        msgBox->setText(error);
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->exec();
    }else if (cliente.estadoCivil.indexOf("Casado") == 0){
        Conjuge conjuge;
        conjuge.nome = m_ui->conjugeNomeLineEdit->text();
        conjuge.renda = m_ui->rendaDoubleSpinBox_2->value();
        i = m_ui->conjugeEmpresaComboBox->currentIndex();
        empresa.id =  m_ui->conjugeEmpresaComboBox->itemData( i ).toInt();
        empresa.nome =  m_ui->conjugeEmpresaComboBox->currentText();
        conjuge.empresa = empresa;
        conjuge.cliente = cliente;
        ConjugeController conjugeController;
        conjugeController.Add(&ok,&error,&conjuge);
        if(ok)
            this->close();
    } else {
         this->close();
    }
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
    repaintCidade();
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
        QVariant v(empresa.id);
        m_ui->empresaComboBox->addItem(empresa.nome,v);
        m_ui->conjugeEmpresaComboBox->addItem(empresa.nome,v);
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

void ClienteAddView::repaintCidade()
{
    CidadeController cd;
    int index = 0;
    foreach(Cidade cidade, cd.getAll())
    {
        QVariant id(cidade.id);
        m_ui->localNascimentoComboBox->addItem(cidade.nome,id);
        if (cidade.nome.contains("dos Pinhais"))
            index = cidade.id;
    }
    index = m_ui->localNascimentoComboBox->findData(QVariant(index));
    m_ui->localNascimentoComboBox->setCurrentIndex(index);
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

void ClienteAddView::cepEdited(QString cepString)
{
    cepString = cepString.replace(".","").replace("-","");
    int cepNumber = cepString.toInt();
    if(cepString.length() < 8)
        return;
    CepController cc;
    bool ok;
    QString error;
    Cep cep = cc.getByCep(&ok,&error,cepNumber);

    if(ok)
    {
        m_ui->estadoLineEdit->setText( cep.estado.nome );
        m_ui->cidadeLineEdit->setText( cep.cidade.nome );
        m_ui->bairroLineEdit->setText( cep.bairro.nome );
        m_ui->enderecoLineEdit->setText( cep.endereco.nome );
    }else{
        m_ui->cidadeLineEdit->clear();
        m_ui->bairroLineEdit->clear();
        m_ui->estadoLineEdit->clear();
        m_ui->enderecoLineEdit->clear();
    }

}
