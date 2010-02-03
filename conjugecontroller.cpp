#include "conjugecontroller.h"

ConjugeController::ConjugeController()
{
}

void ConjugeController::Add(Conjuge *conjuge)
{
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    QString sql;
    sql.append("insert into conjuge (nome,renda,cliente_id,empresa_id) VALUES (:nome,:renda,:cliente_id,:empresa_id)");
    query.prepare(sql);
    query.bindValue(":nome",conjuge->nome);
    query.bindValue(":renda",conjuge->renda);
    query.bindValue(":cliente_id",conjuge->cliente.id);
    query.bindValue(":empresa_id",conjuge->empresa.id);

    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
        conjuge->id = 0;
    }else{
        conjuge->id = query.lastInsertId().toInt();
    }
}
