#include "nacionalidadecontroller.h"
#include "dbutil.h"
#include <QtSql>

NacionalidadeController::NacionalidadeController()
{
}

QString NacionalidadeController::getError()
{

    //        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //        db.setHostName("localhost");
    //        db.setDatabaseName("loja");
    //        db.setUserName("root");
    //        db.setPassword("");
    //
    //        if (!db.open()) {
    //            error = db.lastError().text();
    //            qDebug() << error;
    //        }
    //        QSqlQuery query;
    //         query.prepare("select cidade,bairro,tp_logradouro,logradouro,cep from pr");
    //        if (!query.exec())
    //        {
    //            error = query.lastError().text();
    //            qDebug() << error;
    //        }
    //
    //        QString endereco;
    //        QString bairro;
    //        QString cep;
    //        QString cidade;
    //
    //        int num_cidades = 0;
    //        int num_enderecos = 0;
    //        int num_bairros = 0;
    //        int num_ceps = 0;
    //
    //        while (query.next()) {
    //
    //            cidade = query.value(0).toString();
    //            bairro = query.value(1).toString();
    //            endereco = query.value(2).toString().append(" ").append( query.value(3).toString() );
    //            cep = query.value(4).toString().replace("-","");
    //            QSqlQuery queryCidade;
    //            queryCidade.prepare("insert into cidade (nome) VALUES (:nome)");
    //            queryCidade.bindValue(":nome", cidade);
    //            int cidade_id = 0;
    //            if(!queryCidade.exec()){
    //                queryCidade.prepare("select id from cidade where nome = :nome");
    //                queryCidade.bindValue(":nome", cidade);
    //                queryCidade.exec();
    //                queryCidade.next();
    //                cidade_id = queryCidade.value(0).toInt();
    //            }else{
    //                cidade_id = queryCidade.lastInsertId().toInt();
    //                num_cidades++;
    //            }
    //
    //            int bairro_id = 0;
    //
    //            QSqlQuery queryBairro;
    //            queryBairro.prepare("insert into bairro (nome) VALUES (:nome)");
    //            queryBairro.bindValue(":nome", bairro);
    //            if(!queryBairro.exec()){
    //                queryBairro.prepare("select id from bairro where nome = :nome");
    //                queryBairro.bindValue(":nome", bairro);
    //                queryBairro.exec();
    //                queryBairro.next();
    //                bairro_id = queryBairro.value(0).toInt();
    //            }else{
    //                bairro_id = queryBairro.lastInsertId().toInt();
    //                num_bairros++;
    //            }
    //
    //            int endereco_id = 0;
    //
    //            QSqlQuery queryEndereco;
    //            queryEndereco.prepare("insert into endereco (nome) VALUES (:nome)");
    //            queryEndereco.bindValue(":nome", endereco);
    //            if(!queryEndereco.exec()){
    //                queryEndereco.prepare("select id from endereco where nome = :nome");
    //                queryEndereco.bindValue(":nome", endereco);
    //                queryEndereco.exec();
    //                queryEndereco.next();
    //                endereco_id = queryEndereco.value(0).toInt();
    //            }else{
    //                endereco_id = queryEndereco.lastInsertId().toInt();
    //                num_enderecos++;
    //            }
    //
    //            QSqlQuery queryCep;
    //            queryCep.prepare("insert into cep (endereco_id,bairro_id,cidade_id,estado_uf,cep) VALUES (:endereco_id,:bairro_id,:cidade_id,:estado_uf,:cep)");
    //            queryCep.bindValue(":endereco_id", endereco_id);
    //            queryCep.bindValue(":bairro_id", bairro_id);
    //            queryCep.bindValue(":cidade_id", cidade_id);
    //            queryCep.bindValue(":estado_uf", "PR");
    //            queryCep.bindValue(":cep", cep.toInt());
    //
    //            if(!queryCep.exec()){
    //                qDebug() << queryCep.lastError().text();
    //                break;
    //            }else{
    //                num_ceps++;
    //            }
    //
    //        }
    //        qDebug() << num_cidades << num_bairros << num_enderecos << num_ceps;
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

    QSqlDatabase db = DBUtil::getDatabase(&ok, &error);
    QSqlQuery query(db);

    query.prepare("select nome,id from nacionalidade order by nome");


    if( ok && !query.exec() )
    {
        error = query.lastError().text();
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
