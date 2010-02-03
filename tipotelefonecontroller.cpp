#include "tipotelefonecontroller.h"
#include <QtSql>
#include "dbutil.h"

TipoTelefoneController::TipoTelefoneController()
{
}

QList<TipoTelefone> TipoTelefoneController::getAll()
{
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    query.prepare("select nome,id from tipo_telefone order by nome");

    QList<TipoTelefone> tipos;
    if(!query.exec() )
    {
        qDebug() << query.lastError().text();
        return tipos;
    }

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
