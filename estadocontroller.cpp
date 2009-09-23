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
    query.prepare("select nome,uf from estado order by nome");

    if (!query.exec())
    {
        error = query.lastError().text();
        qDebug() << error;

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
    query.prepare("select nome,id from estado where uf = :uf");
    query.bindValue(":uf", uf);

    if (!query.exec())
    {
        error = query.lastError().text();
        qDebug() << error;
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
