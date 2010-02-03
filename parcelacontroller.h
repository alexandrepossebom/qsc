#ifndef PARCELACONTROLLER_H
#define PARCELACONTROLLER_H
#include "parcela.h"
#include "dbutil.h"
#include "compra.h"
#include <QList>

class ParcelaController
{
public:
    ParcelaController();
    bool Add(Parcela parcela);
    QList<Parcela> getNaoPagasByCompra(Compra compra);
    QList<Parcela> getByCompra(Compra compra);
    bool setPaga(Parcela parcela);
};

#endif // PARCELACONTROLLER_H


