#include "tipotelefonecontroller.h"
#include <QtSql>
#include "dbutil.h"

TipoTelefoneController::TipoTelefoneController()
{
}

QList<TipoTelefone> TipoTelefoneController::getAll()
{

    bool ok;
    QString error;

    QSqlDatabase db = DBUtil::getDatabase(&ok, &error);
    QSqlQuery query(db);

    query.prepare("select nome,id from tipo_telefone order by nome");

    if( ok && !query.exec() )
    {
        error = query.lastError().text();
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
