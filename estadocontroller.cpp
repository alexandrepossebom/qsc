#include "estadocontroller.h"
#include <QtSql>
#include "dbutil.h"
EstadoController::EstadoController()
{
}

QList<Estado> EstadoController::getAll()
{
    bool ok;

    QSqlDatabase db = DBUtil::getDatabase(&ok, &error);
    QSqlQuery query(db);

    query.prepare("select nome,uf from estado order by nome");

    if( ok && !query.exec() )
    {
        error = query.lastError().text();
    }


    QList<Estado> estados;
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
    bool ok;

    QSqlDatabase db = DBUtil::getDatabase(&ok, &error);
    QSqlQuery query(db);

    query.prepare("select nome,id from estado where uf = :uf");
    query.bindValue(":uf", uf);

    if( ok && !query.exec() )
    {
        error = query.lastError().text();
    }




    int fieldNome = query.record().indexOf("nome");
    int fieldUf = query.record().indexOf("uf");
    Estado estado;
    while (query.next()) {
        estado.setNome(query.value(fieldNome).toString());
        estado.setUF(query.value(fieldUf).toString());
    }

    qDebug() << estado.getNome();

    return estado;
}
