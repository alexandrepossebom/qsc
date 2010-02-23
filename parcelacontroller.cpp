#include "parcelacontroller.h"
#include "pagarcontroller.h"

ParcelaController::ParcelaController()
{
}



bool ParcelaController::Add(Parcela parcela)
{
return true;
}

bool ParcelaController::setPaga(Parcela parcela)
{
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    QString sql;
    sql.append("UPDATE parcela SET paga = :paga WHERE id = :id");
    query.prepare(sql);
    query.bindValue(":id",parcela.id);
    query.bindValue(":paga",true);

    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

QList<Parcela> ParcelaController::getByCompra(Compra compra)
{
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    QString sql;
    sql.append("SELECT valor,data_vencimento,id,paga FROM parcela WHERE compra_id = :compra_id ");
    query.prepare(sql);
    query.bindValue(":compra_id",compra.id);

    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
    }

    int fieldValor = query.record().indexOf("valor");
    int fieldDataVencimento = query.record().indexOf("data_vencimento");
    int fieldId = query.record().indexOf("id");
    int fieldPaga = query.record().indexOf("paga");

    QList<Parcela> parcelas;
    Parcela parcela;
    while (query.next()) {
        parcela.id = query.value(fieldId).toInt();
        parcela.valor = query.value(fieldValor).toDouble();
        parcela.paga = query.value(fieldPaga).toBool();
        parcela.dataVencimento = query.value(fieldDataVencimento).toDate();
        parcelas.append(parcela);
    }
    return parcelas;
}



QList<Parcela> ParcelaController::getNaoPagasByCompra(Compra compra)
{
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    QString sql;
    sql.append("SELECT valor,data_vencimento,id FROM parcela WHERE compra_id = :compra_id and paga = :paga");
    query.prepare(sql);
    query.bindValue(":compra_id",compra.id);
    query.bindValue(":paga",false);

    QList<Parcela> parcelas;
    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
        return parcelas;
    }

    int fieldValor = query.record().indexOf("valor");
    int fieldDataVencimento = query.record().indexOf("data_vencimento");
    int fieldId = query.record().indexOf("id");


    Parcela parcela;
    while (query.next()) {
        parcela.id = query.value(fieldId).toInt();
        parcela.valor = query.value(fieldValor).toDouble();
        parcela.paga = false;
        parcela.dataVencimento = query.value(fieldDataVencimento).toDate();

        PagarController pc;
        parcela.valorPago = pc.getTotalPagoByParcela(parcela);
        parcelas.append(parcela);

    }
    return parcelas;
}
