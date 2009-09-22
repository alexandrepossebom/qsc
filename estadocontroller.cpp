#include "estadocontroller.h"
#include <QtSql>
EstadoController::EstadoController()
{
}

QList<Estado> EstadoController::getAll()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("loja");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open()) {
        error = db.lastError().text();
        qDebug() << error;
    }

    QSqlQuery query;
    query.prepare("select nome,id from estado order by nome");

    if (!query.exec())
    {
        error = query.lastError().text();
        qDebug() << error;

    }

    QList<Estado> estados;
    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    Estado estado;
    while (query.next()) {
        estado.setNome(query.value(fieldNome).toString());
        estado.setId(query.value(fieldId).toInt());
        estados.append(estado);
    }

    return estados;
}

Estado EstadoController::getEstadoById(int id)
{
     QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("loja");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open()) {
        error = db.lastError().text();
        qDebug() << error;
    }

    qDebug() << "oi" << id;

    QSqlQuery query;
    query.prepare("select nome,id from estado where id = :id");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        error = query.lastError().text();
        qDebug() << error;
    }


    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    Estado estado;
    while (query.next()) {
        estado.setNome(query.value(fieldNome).toString());
        estado.setId(query.value(fieldId).toInt());
    }

    qDebug() << estado.getNome();

    return estado;
}
