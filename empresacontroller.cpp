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

Empresa EmpresaController::getById(int id)
{
    QSqlDatabase db = DBUtil::getDatabase(&ok, &error);
    QSqlQuery query(db);
    query.prepare("select e.nome,e.id,t.numero from empresa e,empresa_has_telefone et,telefone t where e.id = :id and et.empresa_id = e.id and t.id = et.telefone_id");
    query.bindValue(":id",id);

    Empresa empresa;
    empresa.id = id;

    if( ok && !query.exec() )
    {
        error = query.lastError().text();
        return empresa;
    }
    int fieldNome = query.record().indexOf("nome");
    int fieldNumero = query.record().indexOf("numero");
    Telefone telefone;
    while (query.next()) {
       empresa.nome = query.value(fieldNome).toString();
       telefone.numero = query.value(fieldNumero).toLongLong();
       empresa.telefones.append(telefone);
    }
    return empresa;
}


bool EmpresaController::addEmpresa(Empresa *empresa)
{

    QSqlDatabase db = DBUtil::getDatabase(&ok, &error);
    QSqlQuery query(db);


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
