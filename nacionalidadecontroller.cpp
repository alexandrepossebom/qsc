#include "nacionalidadecontroller.h"
#include "dbutil.h"
#include <QtSql>

NacionalidadeController::NacionalidadeController()
{
}

QString NacionalidadeController::getError()
{
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
    query.prepare("INSERT INTO nacionalidade (nome) VALUES (:nome)");
    query.bindValue(":nome", nacionalidade->getNome());
    if (!query.exec())
    {
        error = query.lastError().text();
        qDebug() << error;
        return false;
    }
    nacionalidade->setId(query.lastInsertId().toInt());
    return true;
}


QList<Nacionalidade> NacionalidadeController::getAll()
{

    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    query.prepare("select nome,id from nacionalidade order by nome");

QList<Nacionalidade> nacionalidades;
    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
        return nacionalidades;
    }

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
