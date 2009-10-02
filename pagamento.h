#ifndef PAGAMENTO_H
#define PAGAMENTO_H
#include "parcela.h"
#include <QDate>

class Pagamento
{
public:
    Pagamento();
    Parcela parcela;
    QDate dataPagamento;
    double valor;
    int id;
};

#endif // PAGAMENTO_H
