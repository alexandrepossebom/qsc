#ifndef PAGARCONTROLLER_H
#define PAGARCONTROLLER_H
#include "parcela.h"
#include <QList>
#include "pagamento.h"

class PagarController
{
public:
    PagarController();
    QList<Pagamento>  getAll(bool *ok,QString *error);
    QList<Pagamento>  getAllByParcela(bool *ok,QString *error,Parcela parcela);
    double getTotalPagoByParcela(bool *ok,QString *error,Parcela parcela);
    void add(bool *ok,QString *error,Parcela parcela,double valor);
};

#endif // PAGARCONTROLLER_H
