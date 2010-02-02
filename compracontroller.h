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
    void Add(bool *ok,QString *error,Compra compra);
    QList<Compra> getNaoPagasByCliente(bool *ok,QString *error,Cliente cliente);
    QList<Compra> getByCliente(Cliente cliente);
    void setPaga(bool *ok,QString *error,Compra compra);
private:
    bool ok;
    QString error;

};

#endif // COMPRACONTROLLER_H
