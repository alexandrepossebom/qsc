#ifndef PARCELA_H
#define PARCELA_H
#include <QDate>


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
};

#endif // PARCELA_H
