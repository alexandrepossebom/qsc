#include "empresacontroller.h"
#include <QDebug>
#include <QtSql>


EmpresaController::EmpresaController()
{
}

QString EmpresaController::getError()
{
    return error;
}

QList<Empresa> EmpresaController::getAll()
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
    query.prepare("select nome,id from empresa order by nome");

    if (!query.exec())
    {
        error = query.lastError().text();
        qDebug() << error;

    }



    QList<Empresa> empresas;


    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    Empresa a;
    while (query.next()) {
        a.setNome(query.value(fieldNome).toString());
        a.setId(query.value(fieldId).toInt());
        empresas.append(a);
    }

    return empresas;
}


bool EmpresaController::addEmpresa(Empresa *empresa)
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
    query.prepare("INSERT INTO empresa (nome) VALUES (:nome)");
    query.bindValue(":nome", empresa->getNome());

    if (!query.exec())
    {
        error = query.lastError().text();
        qDebug() << error;
        return false;
    }
    empresa->setId(query.lastInsertId().toInt());
    return true;
}
