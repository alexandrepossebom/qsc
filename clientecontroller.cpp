#include "clientecontroller.h"
#include <QtSql>
#include <QDebug>
#include "dbutil.h"

ClienteController::ClienteController()
{



}

bool ClienteController::addCliente(bool *ok,QString *error,Cliente cliente)
{

    if( cliente.getNome().length() == 0)
        error->append("\n- Nome do cliente");
    if( cliente.getCpf() == 0 )
        error->append("\n- Cpf");
    if( cliente.getRenda() == 0 )
        error->append("\n- Renda");
    if( cliente.getCargo().length() == 0 )
        error->append("\n- Cargo");
    if( cliente.getEnderecoNumero() == 0 )
        error->append("\n- Endereço Número");

    if( error->length() > 0 )
    {
        QString string = "Verifique os seguintes dados:";
        string.append(error);
        *error = string;
        *ok = false;
        return false;
    }



    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);


    QString sql;
    sql.append("INSERT INTO cliente ");
    sql.append("( nome, nacionalidade_id, empresa_id, estado_uf,");
    sql.append(" cep_cep, data_nascimento, data_cadastro, cpf, estado_civil,");
    sql.append(" rg, rg_data_emissao, nome_pai, nome_mae, renda, cargo, rg_orgao_emissor, endereco_numero)");
    sql.append(" VALUES ");
    sql.append("(:nome,:nacionalidade_id,:empresa_id,:estado_uf,");
    sql.append(":cep_cep,:data_nascimento,:data_cadastro,:cpf,:estado_civil,");
    sql.append(":rg,:rg_data_emissao,:nome_pai,:nome_mae,:renda,:cargo,:rg_orgao_emissor,:endereco_numero)");


    query.prepare(sql);
    query.bindValue(":nome", cliente.getNome());
    query.bindValue(":empresa_id", cliente.getEmpresa().getId());
    query.bindValue(":estado_uf", cliente.getNaturalidade().getUF());
    query.bindValue(":nacionalidade_id", cliente.getNacionalidade().getId());
    query.bindValue(":cep_cep", cliente.getCep().getCep());
    query.bindValue(":data_nascimento", cliente.getDataNascimento() );
    query.bindValue(":data_cadastro", QDate::currentDate() );
    query.bindValue(":cpf", cliente.getCpf() );
    query.bindValue(":estado_civil", cliente.getEstadoCivil());
    query.bindValue(":rg", cliente.getRg() );
    query.bindValue("rg_data_emissao", cliente.getRgDataEmissao() );
    query.bindValue(":nome_pai", cliente.getNomePai() );
    query.bindValue(":nome_mae", cliente.getNomeMae() );
    query.bindValue(":renda", cliente.getRenda());
    query.bindValue(":cargo", cliente.getCargo() );
    query.bindValue(":rg_orgao_emissor", cliente.getRgOrgaoEmissor());
    query.bindValue(":endereco_numero", cliente.getEnderecoNumero());

    if( ok && !query.exec() )
    {
        qDebug() << query.executedQuery();
        *error = query.lastError().text();
        ok = false;
    }

}
