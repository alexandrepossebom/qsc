#ifndef VENDEDORCONTROLLER_H
#define VENDEDORCONTROLLER_H
#include "vendedor.h"

class VendedorController
{
public:
    VendedorController();
    QList<Vendedor> * getAll(bool *ok,QString *error);
    Vendedor * getByName(bool *ok,QString *error,QString nome);
};

#endif // VENDEDORCONTROLLER_H
