#include "cidadecontroller.h"
#include <QList>
#include <QtSql>

CidadeController::CidadeController()
{
}


QList<Cidade> CidadeController::getAll()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("loja");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open()) {
        qDebug() << db.lastError().text();
    }

    QSqlQuery query;
    query.prepare("select nome,id from cidade order by nome");

    if (!query.exec())
    {
       qDebug() << db.lastError().text();
    }

    QList<Cidade> cidades;


    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    Cidade cidade;
    while (query.next()) {
        cidade.setNome(query.value(fieldNome).toString());
        cidade.setId(query.value(fieldId).toInt());
        cidades.append(cidade);
    }

    return cidades;
}
