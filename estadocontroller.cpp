#include "estadocontroller.h"
#include <QtSql>
#include "dbutil.h"
EstadoController::EstadoController()
{
}

QList<Estado> EstadoController::getAll()
{
    bool ok;

    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    query.prepare("select nome,uf from estado order by nome");

    QList<Estado> estados;
    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
        return estados;
    }

    int fieldNome = query.record().indexOf("nome");
    int fieldUF = query.record().indexOf("uf");
    Estado estado;
    while (query.next()) {
        estado.setNome(query.value(fieldNome).toString());
        estado.setUF(query.value(fieldUF).toString());
        estados.append(estado);
    }

    return estados;
}

Estado EstadoController::getEstadoByUF(QString uf)
{

    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    query.prepare("select nome,id from estado where uf = :uf");
    query.bindValue(":uf", uf);

    Estado estado;
    if( !query.exec() )
    {
        qDebug() <<  query.lastError().text();
        return estado;
    }

    int fieldNome = query.record().indexOf("nome");
    int fieldUf = query.record().indexOf("uf");

    while (query.next()) {
        estado.setNome(query.value(fieldNome).toString());
        estado.setUF(query.value(fieldUf).toString());
    }

    return estado;
}
