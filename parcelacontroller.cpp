#include "parcelacontroller.h"
#include "pagarcontroller.h"

ParcelaController::ParcelaController()
{
}



void ParcelaController::Add(bool *ok,QString *error,Parcela parcela)
{

}

void ParcelaController::setPaga(bool *ok,QString *error,Parcela parcela)
{
    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);

    QString sql;
    sql.append("UPDATE parcela SET paga = :paga WHERE id = :id");
    query.prepare(sql);
    query.bindValue(":id",parcela.id);
    query.bindValue(":paga",true);

    if( ok && !query.exec() )
    {
        qDebug() << query.executedQuery();
        *error = query.lastError().text();
        *ok = false;
    }
}

QList<Parcela> ParcelaController::getNaoPagasByCompra(bool *ok,QString *error,Compra compra)
{
    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);

    QString sql;
    sql.append("SELECT valor,data_vencimento,id FROM parcela WHERE compra_id = :compra_id and paga = :paga");
    query.prepare(sql);
    query.bindValue(":compra_id",compra.id);
    query.bindValue(":paga",false);

    if( ok && !query.exec() )
    {
        qDebug() << query.executedQuery();
        *error = query.lastError().text();
        *ok = false;
    }

    int fieldValor = query.record().indexOf("valor");
    int fieldDataVencimento = query.record().indexOf("data_vencimento");
    int fieldId = query.record().indexOf("id");

    QList<Parcela> parcelas;
    Parcela parcela;
    while (query.next()) {
        parcela.id = query.value(fieldId).toInt();
        parcela.valor = query.value(fieldValor).toDouble();
        parcela.paga = false;
        parcela.dataVencimento = query.value(fieldDataVencimento).toDate();

        PagarController pc;
        parcela.valorPago = pc.getTotalPagoByParcela(ok,error,parcela);
        parcelas.append(parcela);

    }
    return parcelas;
}
