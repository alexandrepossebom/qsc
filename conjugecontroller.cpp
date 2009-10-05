#include "conjugecontroller.h"

ConjugeController::ConjugeController()
{
}

void ConjugeController::Add(bool *ok,QString *error,Conjuge *conjuge)
{
    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);

    QString sql;
    sql.append("insert into conjuge (nome,renda,cliente_id,empresa_id) VALUES (:nome,:renda,:cliente_id,:empresa_id)");
    query.prepare(sql);
    query.bindValue(":nome",conjuge->nome);
    query.bindValue(":renda",conjuge->renda);
    query.bindValue(":cliente_id",conjuge->cliente.id);
    query.bindValue(":empresa_id",conjuge->empresa.id);

    if( ok && !query.exec() )
    {
        qDebug() << query.executedQuery();
        *error = query.lastError().text();
        ok = false;
    }else{
        conjuge->id = query.lastInsertId().toInt();
    }
}
