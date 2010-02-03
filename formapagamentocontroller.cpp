#include "formapagamentocontroller.h"

FormaPagamentoController::FormaPagamentoController()
{
}
FormaPagamento FormaPagamentoController::getById(int id)
{
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    query.prepare("select nome,id,parcelas,entrada,desconto,juro from forma_pagamento where id =:id");
    query.bindValue(":id",id);

    FormaPagamento fp;
    if( !query.exec() )
    {
        qDebug() <<  query.lastError().text();
        return fp;
    }

    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    int fieldParcelas = query.record().indexOf("parcelas");
    int fieldEntrada = query.record().indexOf("entrada");
    int fieldDesconto = query.record().indexOf("desconto");
    int fieldJuro = query.record().indexOf("juro");



    query.next();
    fp.setNome( query.value( fieldNome ).toString() );
    fp.setId( query.value( fieldId ).toInt() );
    fp.setParcelas( query.value( fieldParcelas ).toInt() );
    fp.setEntrada( query.value( fieldEntrada ).toBool() );
    fp.setDesconto( query.value( fieldDesconto ).toDouble() );
    fp.setJuro( query.value( fieldJuro).toDouble() );

    return fp;
}

QList<FormaPagamento> FormaPagamentoController::getAll()
{
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    query.prepare("select nome,id from forma_pagamento order by nome");

    QList<FormaPagamento> formasPagamentos;
    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
        return formasPagamentos;
    }

    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    FormaPagamento fp;
    while (query.next()) {
        fp.setNome(query.value(fieldNome).toString());
        fp.setId(query.value(fieldId).toInt());
        formasPagamentos.append(fp);
    }
    return formasPagamentos;
}
