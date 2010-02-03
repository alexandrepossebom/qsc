#ifndef COMPRACONTROLLER_H
#define COMPRACONTROLLER_H
#include "compra.h"
#include "dbutil.h"
#include <QList>
#include "compra.h"


class CompraController
{
public:
    CompraController();
    bool Add(Compra compra);
    QList<Compra> getNaoPagasByCliente(Cliente cliente);
    QList<Compra> getByCliente(Cliente cliente);
    bool setPaga(Compra compra);
};

#endif // COMPRACONTROLLER_H
