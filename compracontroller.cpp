#include "compracontroller.h"
#include "parcelacontroller.h"


CompraController::CompraController()
{
}

bool CompraController::setPaga(Compra compra)
{
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    QString sql;
    sql.append("UPDATE compra SET paga = :paga WHERE id = :id");
    query.prepare(sql);
    query.bindValue(":id",compra.id);
    query.bindValue(":paga",true);

    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}


QList<Compra> CompraController::getByCliente(Cliente cliente)
{
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    QString sql;
    sql.append("SELECT valor,data_compra,id,itens FROM compra WHERE cliente_id = :cliente_id order by data_compra");
    query.prepare(sql);
    query.bindValue(":cliente_id",cliente.id);

    QList<Compra> compras;

    if( !query.exec() )
    {
        qDebug() << query.lastError();
        return compras;
    }

    int fieldValor = query.record().indexOf("valor");
    int fieldDataCompra = query.record().indexOf("data_compra");
    int fieldId = query.record().indexOf("id");
    int fieldItens = query.record().indexOf("itens");

    Compra compra;
    while (query.next()) {
        compra.id = query.value(fieldId).toInt();
        compra.valor = query.value(fieldValor).toDouble();
        compra.paga = false;
        compra.dataCompra = query.value(fieldDataCompra).toDate();
        compra.itens = query.value(fieldItens).toInt();

        ParcelaController pc;
        compra.parcelas = pc.getByCompra(compra);

        compras.append(compra);
    }

    return compras;
}




QList<Compra> CompraController::getNaoPagasByCliente(Cliente cliente)
{
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    QString sql;
    sql.append("SELECT valor,data_compra,id,itens FROM compra WHERE cliente_id = :cliente_id and paga = :paga order by data_compra");
    query.prepare(sql);
    query.bindValue(":cliente_id",cliente.id);
    query.bindValue(":paga",false);

    QList<Compra> compras;
    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
        return compras;
    }

    int fieldValor = query.record().indexOf("valor");
    int fieldDataCompra = query.record().indexOf("data_compra");
    int fieldId = query.record().indexOf("id");
    int fieldItens = query.record().indexOf("itens");

    Compra compra;
    while (query.next()) {
        compra.id = query.value(fieldId).toInt();
        compra.valor = query.value(fieldValor).toDouble();
        compra.paga = false;
        compra.dataCompra = query.value(fieldDataCompra).toDate();
        compra.itens = query.value(fieldItens).toInt();
        //TODO
        ParcelaController pc;
        compra.parcelas = pc.getNaoPagasByCompra(compra);
        compras.append(compra);
    }
    return compras;
}

bool CompraController::Add(Compra compra)
{
    QSqlDatabase db = DBUtil::getDatabase();
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
    query.bindValue(":vendedor_id", compra.vendedor.id);
    query.bindValue(":forma_pagamento_id", compra.formaPagamento.id);
    query.bindValue(":cliente_id", compra.cliente.id);
    query.bindValue(":valor", compra.valor);
    query.bindValue(":data_compra", compra.dataCompra);
    query.bindValue(":itens", compra.itens );
    query.bindValue(":paga", compra.paga );

    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
        return false;
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

        if(!query.exec() )
        {
            qDebug() << query.lastError().text();
            return false;
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

            if( !query.exec() )
            {
                qDebug() << query.lastError().text();
            }
        }

    }
    return true;
}
