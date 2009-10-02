#ifndef PARCELA_H
#define PARCELA_H
#include "compra.h"
#include <QDate>

class Parcela
{
public:
    Parcela();
    Compra compra;
    double valor;
    QDate dataVencimento;
    bool paga;
    int id;
    QString getValorFormatado();
    double getValorAberto();
    double getValorPago();

    double valorPago;
};

#endif // PARCELA_H
