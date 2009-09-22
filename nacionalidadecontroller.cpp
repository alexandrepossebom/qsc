#include "nacionalidadecontroller.h"
#include <QtSql>

NacionalidadeController::NacionalidadeController()
{
}

QString NacionalidadeController::getError()
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
    query.prepare("select cidade,bairro,tp_logradouro,logradouro,cep from pr where cidade = :cidade");
    query.bindValue(":cidade", "sao jose dos pinhais");

    if (!query.exec())
    {
        error = query.lastError().text();
        qDebug() << error;
    }

    QString endereco;
    QString bairro;
    QString cep;
    QString cidade;
    int i = 0;
    while (query.next()) {
        i++;
        cidade = query.value(0).toString();
        bairro = query.value(1).toString();
        endereco = query.value(2).toString().append(" ").append( query.value(3).toString() );
        cep = query.value(4).toString().replace("-","");
        qDebug() << cidade << bairro << endereco << cep;
        QSqlQuery queryCidade;
        queryCidade.prepare("insert into cidade (estado_uf,nome) VALUES ('PR',:nome)");
        queryCidade.bindValue(":nome", cidade);
        if(!queryCidade.exec()){
            qDebug() << queryCidade.lastError().text();
            continue;
        }
        QSqlQuery queryEndereco;
        queryEndereco.prepare("insert into endereco (cidade_id,nome) VALUES (:id,:nome)");
        queryEndereco.bindValue(":nome", endereco);
        queryEndereco.bindValue(":id", queryCidade.lastInsertId().toInt());
        if(!queryEndereco.exec())
            continue;
        QSqlQuery queryCep;
        queryCep.prepare("insert into cep (endereco_id,cep) VALUES (:id,:cep)");
        queryCep.bindValue(":id", queryEndereco.lastInsertId().toInt());
        queryCep.bindValue(":cep", cep.toInt());
        if(!queryCep.exec())
            continue;
        qDebug() << i;
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
