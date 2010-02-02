#include "pagarcontroller.h"
#include "dbutil.h"

PagarController::PagarController()
{
}

void PagarController::add(bool *ok,QString *error,Parcela parcela,double valor)
{
    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    if(!db.isValid())
        qDebug() << "error open database";
    QSqlQuery query(db);

    QString sql;
    sql.append("insert into pagamento (valor,parcela_id,data_pagamento) VALUES (:valor,:parcela_id,:data)");
    query.prepare(sql);
    query.bindValue(":parcela_id",parcela.id);
    query.bindValue(":valor",valor);
    query.bindValue(":data",QDateTime::currentDateTime());

    if( ok && !query.exec() )
    {
        qDebug() << query.executedQuery();
        *error = query.lastError().text();
        ok = false;
    }
}

double PagarController::getTotalPagoByParcela(bool *ok,QString *error,Parcela parcela)
{
    double total = 0;
    QList<Pagamento> pagamentos = getAllByParcela(parcela);
    while(!pagamentos.isEmpty())
    {
        Pagamento pagamento = pagamentos.takeFirst();
        total = total + pagamento.valor;
    }
    return total;
}

QList<Pagamento>  PagarController::getAllByParcela(Parcela parcela)
{
    bool ok;
    QString error;

    QSqlDatabase db = DBUtil::getDatabase(&ok, &error);
    if(!db.isValid())
        qDebug() << "error open database";
    QSqlQuery query(db);

    QString sql;
    sql.append("SELECT valor,data_pagamento,id FROM pagamento WHERE parcela_id = :parcela_id order by data_pagamento");
    query.prepare(sql);
    query.bindValue(":parcela_id",parcela.id);


    if( ok && !query.exec() )
    {
        qDebug() << query.executedQuery();
        error = query.lastError().text();
        ok = false;
    }

    int fieldValor = query.record().indexOf("valor");
    int fieldDataPagamento = query.record().indexOf("data_pagamento");
    int fieldId = query.record().indexOf("id");

    QList<Pagamento> pagamentos;
    Pagamento pagamento;
    while (query.next()) {
        pagamento.id = query.value(fieldId).toInt();
        pagamento.valor = query.value(fieldValor).toDouble();
        pagamento.dataPagamento = query.value(fieldDataPagamento).toDate();
        pagamentos.append(pagamento);
    }

    return pagamentos;
}
