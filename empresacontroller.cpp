#include "empresacontroller.h"
#include <QDebug>
#include <QtSql>
#include "dbutil.h"
#include "telefonecontroller.h"


EmpresaController::EmpresaController()
{
}

QString EmpresaController::getError()
{
    return error;
}

QList<Empresa> EmpresaController::getAll()
{
    QSqlDatabase db = DBUtil::getDatabase(&ok, &error);
    QSqlQuery query(db);
    query.prepare("select nome,id from empresa order by nome");

    QList<Empresa> empresas;

    if( ok && !query.exec() )
    {
        error = query.lastError().text();
        return empresas;
    }

    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    Empresa a;
    while (query.next()) {
        a.nome = query.value(fieldNome).toString();
        a.id = query.value(fieldId).toInt();
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
    query.prepare("INSERT INTO empresa (nome,numero,cep_cep) VALUES (:nome,:numero,:cep)");
    query.bindValue(":nome", empresa->nome);
    query.bindValue(":numero",empresa->numero);
    query.bindValue(":cep",empresa->cep.cep);

    if (!query.exec())
    {
        error = query.lastError().text();
        qDebug() << error;
        return false;
    }
    empresa->id = query.lastInsertId().toInt();

    if(empresa->id > 0 && empresa->telefones.size() > 0)
    {
        TelefoneController tc;
        while(!empresa->telefones.isEmpty())
        {

            Telefone telefone = empresa->telefones.takeFirst();
            telefone.id = 0;
            tc.Add(&telefone);
            if (telefone.id > 0)
            {
                query.prepare("insert into empresa_has_telefone (empresa_id,telefone_id) values (:empresa_id,:telefone_id)");
                query.bindValue(":empresa_id",empresa->id);
                query.bindValue(":telefone_id",telefone.id);
                query.exec();
            }
        }
    }
    return true;
}
