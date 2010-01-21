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
    double getValorAberto();
    double getValorPago();

    double valorPago;
};

#endif // PARCELA_H
