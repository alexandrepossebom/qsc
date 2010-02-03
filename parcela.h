#ifndef PARCELA_H
#define PARCELA_H
#include <QDate>
#include <QList>
#include "pagamento.h"


class Parcela
{
public:
    Parcela();
    double valor;
    QDate dataVencimento;
    bool paga;
    int id;
    QString getValorFormatado();
    float getValorAberto();
    float getValorPago();
    float valorPago;
    QList<Pagamento> pagamentos;
};




#endif // PARCELA_H
