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
    void Add(bool *ok,QString *error,Parcela parcela);
    QList<Parcela> getNaoPagasByCompra(bool *ok,QString *error,Compra compra);
    QList<Parcela> getByCompra(Compra compra);
    void setPaga(bool *ok,QString *error,Parcela parcela);
};

#endif // PARCELACONTROLLER_H


