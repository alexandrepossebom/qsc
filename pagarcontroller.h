#ifndef PAGARCONTROLLER_H
#define PAGARCONTROLLER_H
#include "parcela.h"
#include <QList>
#include "pagamento.h"

class PagarController
{
public:
    PagarController();
    QList<Pagamento>  getAll();
    QList<Pagamento>  getAllByParcela(Parcela parcela);
    double getTotalPagoByParcela(Parcela parcela);
    bool add(Parcela parcela,double valor);
};

#endif // PAGARCONTROLLER_H
