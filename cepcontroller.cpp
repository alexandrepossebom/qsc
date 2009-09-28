#include "cepcontroller.h"
#include "cep.h"
#include "cidade.h"
#include "bairro.h"
#include "endereco.h"
#include "estado.h"
#include <QtSql>
#include "dbutil.h"

CepController::CepController()
{
}

Cep CepController::getByCep(bool *ok,QString *error,int cepnumber)
{
    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);

    QString sql = "select es.nome as estado,es.uf as uf,e.nome as endereco";
    sql.append(",e.id as endereco_id,c.cep as cep,b.nome as bairro,b.id as bairro_id,");
    sql.append("ci.nome as cidade, ci.id as cidade_id from endereco e,cep c,bairro b,cidade ci,");
    sql.append("estado es where cep = :cep and c.endereco_id=e.id and c.bairro_id=b.id ");
    sql.append("and ci.id=c.cidade_id and es.uf=c.estado_uf limit 1");

    query.prepare(sql);
    query.bindValue(":cep",cepnumber);


    if( ok && !query.exec() )
    {
        *error = query.lastError().text();
        *ok = false;
    }

    Cep cep;

    int fieldEndereco = query.record().indexOf("endereco");
    int fieldEndereco_id = query.record().indexOf("endereco_id");
    int fieldCep = query.record().indexOf("cep");
    int fieldBairro = query.record().indexOf("bairro");
    int fieldBairro_id = query.record().indexOf("bairro_id");
    int fieldCidade = query.record().indexOf("cidade");
    int fieldCidade_id = query.record().indexOf("cidade_id");
    int fieldEstado_uf = query.record().indexOf("uf");
    int fieldEstado = query.record().indexOf("estado");



    Cidade cidade;
    Estado estado;
    Bairro bairro;
    Endereco endereco;

    query.next();

    cep.setCep(query.value(fieldCep).toInt());

    cidade.setId(query.value(fieldCidade_id).toInt());
    cidade.setNome(query.value(fieldCidade).toString());
    cep.setCidade(cidade);

    estado.setUF(query.value(fieldEstado_uf).toString());
    estado.setNome(query.value(fieldEstado).toString());
    cep.setEstado(estado);

    bairro.setId(query.value(fieldBairro_id).toInt());
    bairro.setNome(query.value(fieldBairro).toString());

    cep.setBairro(bairro);

    endereco.setId(query.value(fieldEndereco_id).toInt());
    endereco.setNome(query.value(fieldEndereco).toString());

    cep.setEndereco(endereco);

    return cep;
}

void CepController::add(bool *ok,QString *error,Cep cep)
{
    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);

    QString cidade = cep.getCidade().getNome();
    QString bairro = cep.getBairro().getNome();
    QString endereco = cep.getEndereco().getNome();
    QString estado = cep.getEstado().getUF();
    int cepint = cep.getCep();

    query.prepare("insert into cidade (nome) VALUES (:nome)");
    query.bindValue(":nome", cidade);
    int cidade_id = 0;
    if(!query.exec()){
        query.prepare("select id from cidade where nome = :nome");
        query.bindValue(":nome", cidade);
        query.exec();
        query.next();
        cidade_id = query.value(0).toInt();
    }else{
        cidade_id = query.lastInsertId().toInt();
    }

    int bairro_id = 0;
    query.prepare("insert into bairro (nome) VALUES (:nome)");
    query.bindValue(":nome", bairro);
    if(!query.exec()){
        query.prepare("select id from bairro where nome = :nome");
        query.bindValue(":nome", bairro);
        query.exec();
        query.next();
        bairro_id = query.value(0).toInt();
        qDebug() << "new" << bairro_id;
    }else{
        bairro_id = query.lastInsertId().toInt();
    }

    int endereco_id = 0;
    query.prepare("insert into endereco (nome) VALUES (:nome)");
    query.bindValue(":nome", endereco);
    if(!query.exec()){
        query.prepare("select id from endereco where nome = :nome");
        query.bindValue(":nome", endereco);
        query.exec();
        query.next();
        endereco_id = query.value(0).toInt();
    }else{
        endereco_id = query.lastInsertId().toInt();
    }

    query.prepare("insert into cep (endereco_id,bairro_id,cidade_id,estado_uf,cep) VALUES (:endereco_id,:bairro_id,:cidade_id,:estado_uf,:cep)");
    query.bindValue(":endereco_id", endereco_id);
    query.bindValue(":bairro_id", bairro_id);
    query.bindValue(":cidade_id", cidade_id);
    query.bindValue(":estado_uf", estado);
    query.bindValue(":cep", cepint);

    if( ok && !query.exec() )
    {
        *error = query.lastError().text();
        ok = false;
    }

}
