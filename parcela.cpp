#include "parcela.h"

Parcela::Parcela()
{
    valorPago = 0;
}
QString Parcela::getValorFormatado()
{
    QString string;
    string.append("R$ ");
    string.append(QString::number(valor,'F',2));
    return string;
}

float Parcela::getValorSugerido()
{
    if (dataVencimento.daysTo( QDate::currentDate() ) <= 5)
        return getValorAberto();
    float newValor = valor;
    QDate newDate = dataVencimento;
    while(newDate.operator <(QDate::currentDate()))
    {
        newDate = newDate.addDays(1);
        newValor = newValor * 1.00166667;
    }
    return newValor - valorPago;
}

float Parcela::getValorAberto()
{
    if (paga)
        return 0;
    if (dataVencimento.daysTo( QDate::currentDate() ) <= 5)
        return valor - valorPago;
    return getValorSugerido();
}
float Parcela::getValorPago()
{
    return valorPago;
}
