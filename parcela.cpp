#include "parcela.h"

Parcela::Parcela()
{
}
QString Parcela::getValorFormatado()
{
    QString string;
    string.append("R$ ");
    string.append(QString::number(valor,'F',2));
    return string;
}

double Parcela::getValorAberto()
{
    return valor - valorPago;
}
double Parcela::getValorPago()
{
    return valorPago;
}
