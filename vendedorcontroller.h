#ifndef VENDEDORCONTROLLER_H
#define VENDEDORCONTROLLER_H
#include "vendedor.h"

class VendedorController
{
public:
    VendedorController();
    QList<Vendedor> getAll();
    Vendedor getByName(QString nome);
};

#endif // VENDEDORCONTROLLER_H
