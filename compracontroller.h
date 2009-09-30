#ifndef COMPRACONTROLLER_H
#define COMPRACONTROLLER_H
#include "compra.h"
#include "dbutil.h"


class CompraController
{
public:
    CompraController();
    void Add(bool *ok,QString *error,Compra compra);
};

#endif // COMPRACONTROLLER_H
