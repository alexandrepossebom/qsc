#include "clientecontroller.h"
#include <QtSql>
#include <QDebug>
#include "telefonecontroller.h"
#include "dbutil.h"

ClienteController::ClienteController()
{

}

Cliente ClienteController::getClienteByCpf(bool *ok,QString *error,long long int cpf)
{
    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);
    query.prepare("select nome,id,cpf,data_nascimento from cliente where cpf = :cpf order by nome limit 1");
    query.bindValue(":cpf",cpf);

    if( ok && !query.exec() )
    {
        *error = query.lastError().text();
        *ok = false;
    }

    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    int fieldCpf = query.record().indexOf("cpf");
    int fieldDataNascimento = query.record().indexOf("data_nascimento");
    Cliente cliente;
    query.next();
    cliente.setNome(query.value(fieldNome).toString());
    cliente.setId(query.value(fieldId).toInt());
    cliente.setCpf(query.value(fieldCpf).toLongLong());
    cliente.setDataNascimento(query.value(fieldDataNascimento).toDate());

    return cliente;
}


QList<Cliente> ClienteController::getClientesAtrasados(bool *ok,QString *error,QString nome)
{

    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);
    query.prepare("select c.nome,c.id,c.cpf,c.data_nascimento,p.data_vencimento from cliente c, compra co, parcela p WHERE co.cliente_id = c.id AND p.compra_id = co.id AND p.paga = 0 AND p.data_vencimento < :now ");

    query.bindValue(":now",QDate::currentDate());
    //TODO add nome to query.
    query.bindValue(":nome",nome);

    if( ok && !query.exec() )
    {
        *error = query.lastError().text();
        *ok = false;
    }

    QList<Cliente> clientes;

    int fieldNome = query.record().indexOf("c.nome");
    int fieldId = query.record().indexOf("c.id");
    int fieldCpf = query.record().indexOf("c.cpf");
    int fieldDataNascimento = query.record().indexOf("c.data_nascimento");
    //    int fieldDataVencimento = query.record().indexOf("p.data_vencimento");

    Cliente cliente;
    while (query.next()) {
        cliente.setNome(query.value(fieldNome).toString());
        cliente.setId(query.value(fieldId).toInt());
        cliente.cpf = query.value(fieldCpf).toLongLong();
        cliente.dataNascimento = query.value(fieldDataNascimento).toDate();
        clientes.append(cliente);
    }

    return clientes;
}

QList<Cliente> ClienteController::getClientesByName(bool *ok,QString *error,QString nome,int limit)
{
    QString str = "%";
    str.append(nome);
    str.append("%");
    nome = str;

    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);

    if(limit <= 0)
    {
        query.prepare("select c.nome,c.id,c.cpf,c.data_nascimento,e.nome as empresa_nome,e.id as empresa_id from cliente c,empresa e where c.empresa_id = e.id and c.nome like :nome order by c.nome");
        query.bindValue(":nome",nome);
    }
    else
    {
        query.prepare("select c.nome,c.id,c.cpf,c.data_nascimento from cliente c where c.nome like :nome order by c.nome limit :limit");
        query.bindValue(":nome",nome);
        query.bindValue(":limit",limit);
    }
    if( ok && !query.exec() )
    {
        *error = query.lastError().text();
        *ok = false;
    }

    QList<Cliente> clientes;

    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    int fieldCpf = query.record().indexOf("cpf");
    int fieldEmpresa = query.record().indexOf("empresa_nome");
    int fieldEmpresaId = query.record().indexOf("empresa_id");
    int fieldDataNascimento = query.record().indexOf("data_nascimento");

    Cliente cliente;
    Empresa empresa;
    while (query.next()) {
        cliente.setNome(query.value(fieldNome).toString());
        cliente.setId(query.value(fieldId).toInt());
        cliente.cpf = query.value(fieldCpf).toLongLong();
        cliente.dataNascimento = query.value(fieldDataNascimento).toDate();
        empresa.nome = query.value(fieldEmpresa).toString();
        empresa.id = query.value(fieldEmpresaId).toInt();
        cliente.setEmpresa(empresa);
        clientes.append(cliente);
    }

    return clientes;
}

void ClienteController::addCliente(bool *ok,QString *error,Cliente *cliente)
{

    if( cliente->getNome().length() == 0)
        error->append("\n- Nome do cliente");
    if( cliente->getCpf() == 0 )
        error->append("\n- Cpf");
    if( cliente->getCargo().length() == 0 )
        error->append("\n- Cargo");
    if( cliente->renda == 0 )
        error->append(QString::fromUtf8("\n- Renda inválida"));
    if( cliente->getCep().cep == 0 )
        error->append(QString::fromUtf8("\n- Cep"));
    if( cliente->getEnderecoNumero() == 0 )
        error->append(QString::fromUtf8("\n- Endereço Número"));
    if( cliente->dataNascimento.operator ==(QDate::currentDate().addYears(-18)))
        error->append(QString::fromUtf8("\n- Data de nascimento inválida"));
    if( error->length() > 0 )
    {
        QString string = "Verifique os seguintes dados:";
        string.append(error);
        error->clear();
        error->append(string);
        *ok = false;
        return;
    }

    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);


    QString sql;
    sql.append("INSERT INTO cliente ");
    sql.append("( nome, nacionalidade_id, empresa_id, estado_uf,");
    sql.append(" cep_cep, data_nascimento, data_cadastro, cpf, estado_civil, local_nascimento,");
    sql.append(" rg, rg_data_emissao, nome_pai, nome_mae, renda, cargo, rg_orgao_emissor, endereco_numero)");
    sql.append(" VALUES ");
    sql.append("(:nome,:nacionalidade_id,:empresa_id,:estado_uf,");
    sql.append(":cep_cep,:data_nascimento,:data_cadastro,:cpf,:estado_civil,:local_nascimento,");
    sql.append(":rg,:rg_data_emissao,:nome_pai,:nome_mae,:renda,:cargo,:rg_orgao_emissor,:endereco_numero)");


    query.prepare(sql);
    query.bindValue(":nome", cliente->getNome());
    query.bindValue(":empresa_id", cliente->empresa.id);
    query.bindValue(":estado_uf", cliente->getNaturalidade().getUF());
    query.bindValue(":nacionalidade_id", cliente->getNacionalidade().getId());
    query.bindValue(":cep_cep", cliente->getCep().getCep());
    query.bindValue(":data_nascimento", cliente->getDataNascimento() );
    query.bindValue(":data_cadastro", QDate::currentDate() );
    query.bindValue(":cpf", cliente->getCpf() );
    query.bindValue(":estado_civil", cliente->getEstadoCivil());
    query.bindValue(":local_nascimento", cliente->localNascimento.id);
    query.bindValue(":rg", cliente->getRg() );
    query.bindValue("rg_data_emissao", cliente->getRgDataEmissao() );
    query.bindValue(":nome_pai", cliente->getNomePai() );
    query.bindValue(":nome_mae", cliente->getNomeMae() );
    query.bindValue(":renda", cliente->getRenda());
    query.bindValue(":cargo", cliente->getCargo() );
    query.bindValue(":rg_orgao_emissor", cliente->getRgOrgaoEmissor());
    query.bindValue(":endereco_numero", cliente->getEnderecoNumero());


    if( ok && !query.exec() )
    {
        qDebug() << query.executedQuery();
        error->clear();
        error->append(query.lastError().text());
        qDebug() << error;
        ok = false;
    }else{
        cliente->id = query.lastInsertId().toInt();
        while(!cliente->telefones.isEmpty())
        {
            Telefone telefone = cliente->telefones.takeFirst();
            TelefoneController tc;
            tc.Add(&telefone);
            if (telefone.id > 0)
            {
                query.prepare("insert into cliente_has_telefone (cliente_id,telefone_id) values (:cliente_id,:telefone_id)");
                query.bindValue(":cliente_id",cliente->id);
                query.bindValue(":telefone_id",telefone.id);
                query.exec();
            }
        }
    }
    DBUtil::log("cliente","Novo cliente adicionado" + cliente->nome);
}
