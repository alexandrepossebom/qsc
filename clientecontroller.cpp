#include "clientecontroller.h"
#include <QtSql>
#include <QDebug>
#include "dbutil.h"

ClienteController::ClienteController()
{



}

bool ClienteController::addCliente(bool *ok,QString *error,Cliente cliente)
{

    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);


    QString sql;
    sql.append("INSERT INTO cliente ");
    sql.append("( nome, nacionalidade_id, empresa_id, estado_uf, cep_cep)");
    sql.append(" VALUES ");
    sql.append("(:nome,:nacionalidade_id,:empresa_id,:estado_uf, :cep_cep)");

    query.prepare(sql);
    query.bindValue(":nome", cliente.getNome());
    query.bindValue(":empresa_id", cliente.getEmpresa().getId());
    query.bindValue(":estado_uf", cliente.getNaturalidade().getUF());
    query.bindValue(":nacionalidade_id", cliente.getNacionalidade().getId());
    query.bindValue(":cep_cep", cliente.getCep().getCep());

    if( ok && !query.exec() )
    {
        qDebug() << query.executedQuery();
        *error = query.lastError().text();
        ok = false;
    }
}
