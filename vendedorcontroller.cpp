#include "vendedorcontroller.h"
#include "dbutil.h"
#include <QList>

VendedorController::VendedorController()
{
}

QList<Vendedor> * VendedorController::getAll(bool *ok,QString *error)
{
    QSqlDatabase db = DBUtil::getDatabase(ok, error);
    QSqlQuery query(db);

    query.prepare("select nome,id from vendedor order by nome");


    if( ok && !query.exec() )
    {
        *error = query.lastError().text();
        ok = false;
    }

    QList<Vendedor> *vendedores = new QList<Vendedor>();

    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    Vendedor vendedor;
    while (query.next())
    {
        vendedor.setNome(query.value(fieldNome).toString());
        vendedor.setId(query.value(fieldId).toInt());
        vendedores->append(vendedor);
    }

    return vendedores;
}


Vendedor * VendedorController::getByName(bool *ok,QString *error,QString nome)
{
    Vendedor *vendedor = new Vendedor();
    return vendedor;
}
