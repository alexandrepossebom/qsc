#include "tipotelefonecontroller.h"
#include <QtSql>
TipoTelefoneController::TipoTelefoneController()
{
}

QList<TipoTelefone> TipoTelefoneController::getAll()
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
    query.prepare("select nome,id from tipo_telefone order by nome");

    if (!query.exec())
    {
       qDebug() << db.lastError().text();
    }

    QList<TipoTelefone> tipos;


    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    TipoTelefone tipo;
    while (query.next()) {
        tipo.setNome(query.value(fieldNome).toString());
        tipo.setId(query.value(fieldId).toInt());
        tipos.append(tipo);
    }

    return tipos;
}
