#include "clientecontroller.h"
#include <QtSql>
#include <QDebug>

ClienteController::ClienteController()
{



}

bool ClienteController::addCliente(Cliente cliente)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("loja");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open()) {
        qDebug() << "Error open database.";
        qDebug() << db.lastError();
        return false;
    }


    QSqlQuery query;
    query.prepare("INSERT INTO nacionalidade (nome) VALUES (:nome)");
    query.bindValue(":nome", cliente.getNacionalidade().getNome());


    if (!query.execBatch())
        qDebug() << query.lastError();
    int nascionalidade_id = query.lastInsertId().toInt();

    query.prepare("INSERT INTO cliente (nome,nascionalidade_id) VALUES (:nome,:nacionalidade_id)");
    query.bindValue(":nome", cliente.getNome());
    query.bindValue(":nascionalidade_id", nascionalidade_id);

    if(query.exec())
    {
        return true;
    }else{
        qDebug() << query.lastError();
        return false;
    }
}
