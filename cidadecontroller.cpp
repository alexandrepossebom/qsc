#include "cidadecontroller.h"
#include <QList>
#include <QtSql>
#include "dbutil.h"

CidadeController::CidadeController()
{
}


QList<Cidade> CidadeController::getAll()
{
    bool ok;
    QString error;

    QSqlDatabase db = DBUtil::getDatabase(&ok, &error);
    QSqlQuery query(db);

    query.prepare("select nome,id from cidade order by nome");


    if( ok && !query.exec() )
    {
        error = query.lastError().text();
    }

    QList<Cidade> cidades;

    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    Cidade cidade;
    while (query.next()) {
        cidade.setNome(query.value(fieldNome).toString());
        cidade.setId(query.value(fieldId).toInt());
        cidades.append(cidade);
    }

    return cidades;
}
