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

    if(compra.formaPagamento.parcelas == 1 && compra.formaPagamento.entrada)
        compra.paga = true;
    else
        compra.paga = false;

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
        return;
    }
    compra.id = query.lastInsertId().toInt();

    double parcela_valor = compra.valor / compra.formaPagamento.parcelas ;
    if (compra.formaPagamento.desconto != 0)
        parcela_valor = parcela_valor * (1 - compra.formaPagamento.desconto);
    else if ( compra.formaPagamento.juro != 0)
        parcela_valor = parcela_valor * compra.formaPagamento.juro;

    for (int i=0;i<compra.formaPagamento.parcelas;i++)
    {
        QString sql;
        sql.append("INSERT INTO parcela ");
        sql.append("( compra_id, data_vencimento, paga, valor )");
        sql.append(" VALUES ");
        sql.append("(:compra_id,:data_vencimento,:paga,:valor )");

        QDate dataVencimento;
        if( compra.formaPagamento.entrada && i == 0)
        {
            dataVencimento = compra.dataCompra;
            compra.paga = true;
        }else{
            dataVencimento = compra.dataCompra.addMonths( i+1 );
            compra.paga = false;
        }

        query.prepare(sql);
        query.bindValue(":compra_id", compra.id);
        query.bindValue(":data_vencimento", dataVencimento);
        query.bindValue(":paga", compra.paga);
        query.bindValue(":valor", parcela_valor);

        if( ok && !query.exec() )
        {
            qDebug() << query.executedQuery();
            *error = query.lastError().text();
            qDebug() << error;
            ok = false;
            return;
        }

        int parcela_id = query.lastInsertId().toInt();

        if ( compra.formaPagamento.entrada && i == 0 )
        {
            QString sql;
            sql.append("INSERT INTO pagamento ");
            sql.append("( parcela_id, data_pagamento, valor )");
            sql.append(" VALUES ");
            sql.append("(:parcela_id,:data_pagamento,:valor )");

            query.prepare(sql);
            query.bindValue(":parcela_id", parcela_id);
            query.bindValue(":data_pagamento", compra.dataCompra);
            query.bindValue(":valor", parcela_valor);

            if( ok && !query.exec() )
            {
                qDebug() << query.executedQuery();
                *error = query.lastError().text();
                qDebug() << error;
                ok = false;
                return;
            }
        }

    }



}