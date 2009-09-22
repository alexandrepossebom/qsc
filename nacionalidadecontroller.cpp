#include "nacionalidadecontroller.h"
#include <QtSql>

NacionalidadeController::NacionalidadeController()
{
}

QString NacionalidadeController::getError()
{
    qDebug() << "ola";
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("ceps");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open()) {
        error = db.lastError().text();
        qDebug() << error;
        return false;
    }


    QSqlQuery query;

    query.prepare("select logradouro,bairro,cep from pr where cidade = 'São José dos Pinhais' order by cep");

      if (!query.exec())
    {
        error = query.lastError().text();
        qDebug() << error;

    }

   while (query.next()) {
        qDebug() << query.value(0).toString();
        qDebug() << query.value(1).toString();
    }

    return error;
}


bool NacionalidadeController::add(Nacionalidade *nacionalidade)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("loja");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open()) {
        error = db.lastError().text();
        qDebug() << error;
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO nascionalidade (nome) VALUES (:nome)");
    query.bindValue(":nome", nacionalidade->getNome());

    return true;
}


QList<Nacionalidade> NacionalidadeController::getAll()
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
    query.prepare("select nome,id from nascionalidade order by nome");

    if (!query.exec())
    {
        error = query.lastError().text();
        qDebug() << error;

    }

    QList<Nacionalidade> nacionalidades;


    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    Nacionalidade n;
    while (query.next()) {
        n.setNome(query.value(fieldNome).toString());
        n.setId(query.value(fieldId).toInt());
        nacionalidades.append(n);
    }

    return nacionalidades;
}
