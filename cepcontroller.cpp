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

Cep CepController::getByCep(int cepnumber)
{
    bool ok;
    QString error;

    QSqlDatabase db = DBUtil::getDatabase(&ok, &error);
    QSqlQuery query(db);

    query.prepare("select es.nome as estado,es.uf as uf,e.nome as endereco,e.id as endereco_id,c.cep as cep,b.nome as bairro,b.id as bairro_id,ci.nome as cidade, ci.id as cidade_id from endereco e,cep c,bairro b,cidade ci,estado es where cep = :cep and c.endereco_id=e.id and c.bairro_id=b.id and ci.id=c.cidade_id and es.uf=c.estado_uf");
    query.bindValue(":cep",cepnumber);


    if( ok && !query.exec() )
    {
        error = query.lastError().text();
    }

    Cep cep;

    int fieldEndereco = query.record().indexOf("endereco");
    int fieldEndereco_id = query.record().indexOf("endereco_id");
    int fieldCep = query.record().indexOf("cep");
    int fieldBairro = query.record().indexOf("bairro");
    int fieldBairro_id = query.record().indexOf("bairro_id");
    int fieldCidade = query.record().indexOf("cidade");
    int fieldCidade_id = query.record().indexOf("cidade_id");
    int fieldEstado_uf = query.record().indexOf("estado_uf");
    int fieldEstado = query.record().indexOf("estado");

    while (query.next()) {
        Cidade cidade;
        Estado estado;
        Bairro bairro;
        Endereco endereco;

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


    }

    return cep;
}
