#include "vendedorcontroller.h"
#include "dbutil.h"
#include <QList>

VendedorController::VendedorController()
{
}

QList<Vendedor> VendedorController::getAll()
{
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    query.prepare("select nome,id from vendedor order by nome");


    QList<Vendedor> vendedores;
    if( !query.exec() )
    {
        return vendedores;
    }

    int fieldNome = query.record().indexOf("nome");
    int fieldId = query.record().indexOf("id");
    Vendedor vendedor;
    while (query.next())
    {
        vendedor.setNome(query.value(fieldNome).toString());
        vendedor.setId(query.value(fieldId).toInt());
        vendedores.append(vendedor);
    }
    return vendedores;
}


Vendedor VendedorController::getByName(QString nome)
{
    Vendedor vendedor;
    return vendedor;
}
