#include "bairrocontroller.h"

BairroController::BairroController()
{
}

QList<Bairro> BairroController::getAll(bool *ok,QString *error)
{
    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);

    query.prepare("select nome,id from bairro order by nome");


    if( ok && !query.exec() )
    {
        *error = query.lastError().text();
        ok = false;
    }

    QList<Bairro> bairros;

    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    while (query.next()) {
        Bairro bairro;
        bairro.setNome(query.value(fieldNome).toString());
        bairro.setId(query.value(fieldId).toInt());
        bairros.append(bairro);
    }

    return bairros;
}
