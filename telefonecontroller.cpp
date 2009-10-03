#include "telefonecontroller.h"

TelefoneController::TelefoneController()
{
}
bool TelefoneController::Add(Telefone *  telefone)
{
    bool ok;
    QString error;
    Add(&ok,&error,telefone);
    if(!ok)
    {
        qDebug() << error;
        return false;
    }
    return true;
}
void TelefoneController::Add(bool *ok,QString *error,Telefone *telefone)
{
    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);

    QString sql;
    sql.append("insert into telefone (numero,tipo_telefone_id) VALUES (:numero,:tipo_telefone_id)");
    query.prepare(sql);
    query.bindValue(":tipo_telefone_id",telefone->tipoTelefone.id);
    query.bindValue(":numero",telefone->numero);

    if( ok && !query.exec() )
    {
        query.prepare("select id from telefone where numero = :numero");
        query.bindValue(":numero",telefone->numero);
        if(query.exec())
        {
            query.next();
            telefone->id = query.value(0).toInt();
        }else{
            qDebug() << query.executedQuery();
            *error = query.lastError().text();
            ok = false;
        }

    }else{
        telefone->id = query.lastInsertId().toInt();
    }
}
