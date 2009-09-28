#include "formapagamentocontroller.h"

FormaPagamentoController::FormaPagamentoController()
{
}
QList<FormaPagamento> FormaPagamentoController::getAll(bool *ok,QString *error)
{
   QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);

    query.prepare("select nome,id from forma_pagamento order by nome");

    if( ok && !query.exec() )
    {
        *error = query.lastError().text();
        *ok = false;
    }


    QList<FormaPagamento> formasPagamentos;
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
