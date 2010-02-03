#include "bairrocontroller.h"

BairroController::BairroController()
{
}

QList<Bairro> BairroController::getAll()
{
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    query.prepare("select nome,id from bairro order by nome");

    QList<Bairro> bairros;
    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
        return bairros;

    }



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
