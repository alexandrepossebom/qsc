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

float Parcela::getValorAberto()
{
    return valor - valorPago;
}
float Parcela::getValorPago()
{
    return valorPago;
}
