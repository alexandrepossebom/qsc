#include "enderecocontroller.h"
#include "estado.h"
#include <QtSql>

EnderecoController::EnderecoController()
{
}

bool EnderecoController::add(Endereco *endereco)
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
    query.prepare("INSERT INTO endereco (nome,cep,cidade,bairro,estado_id) VALUES (:nome,:cep,:cidade,:bairro,:estado_id)");
    query.bindValue(":nome", endereco->getNome());
    query.bindValue(":cep", endereco->getCep());
    query.bindValue(":cidade", endereco->getCidade());
    query.bindValue(":bairro", endereco->getBairro());
    query.bindValue(":estado_id", endereco->getEstado().getId()   );

    if (!query.exec())
    {
        error = query.lastError().text();
        qDebug() << error;
        return false;
    }
    endereco->setId(query.lastInsertId().toInt());
    return true;
}

Endereco EnderecoController::getByCep(int cep)
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
    query.prepare("select nome,id,cep,bairro,cidade from endereco where cep = :cep");
    query.bindValue(":cep",cep);

    if (!query.exec())
    {
        error = query.lastError().text();
        qDebug() << error;

    }

    Endereco endereco;

    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    int fieldCep = query.record().indexOf("cep");
    int fieldBairro = query.record().indexOf("bairro");
    int fieldCidade = query.record().indexOf("cidade");

    while (query.next()) {
        endereco.setNome(query.value(fieldNome).toString());
        endereco.setId(query.value(fieldId).toInt());
        endereco.setCep(query.value(fieldCep).toInt());
        endereco.setBairro(query.value(fieldBairro).toString());
        endereco.setCidade(query.value(fieldCidade).toString());
    }

    return endereco;
}


