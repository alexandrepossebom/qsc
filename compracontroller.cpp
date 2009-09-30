#include "compracontroller.h"


CompraController::CompraController()
{
}

void CompraController::Add(bool *ok,QString *error,Compra compra)
{
     QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);


    QString sql;
    sql.append("INSERT INTO compra ");
    sql.append("( vendedor_id, forma_pagamento_id, cliente_id, valor,");
    sql.append(" data_compra, itens, paga)");
    sql.append(" VALUES ");
    sql.append("(:vendedor_id,:forma_pagamento_id,:cliente_id,:valor,");
    sql.append(":data_compra,:itens,:paga)");


    query.prepare(sql);
    query.bindValue(":vendedor_id", compra.vendedor.getId());
    query.bindValue(":forma_pagamento_id", compra.formaPagamento.getId());
    query.bindValue(":cliente_id", compra.cliente.getId());
    query.bindValue(":valor", compra.valor);
    query.bindValue(":data_compra", compra.dataCompra);
    query.bindValue(":itens", compra.itens );
    query.bindValue(":paga", compra.paga );

    if( ok && !query.exec() )
    {
        qDebug() << query.executedQuery();
        *error = query.lastError().text();
        ok = false;
    }
}
