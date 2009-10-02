#include "compra.h"

Compra::Compra()
{
}

QString Compra::getValorFormatado()
{
    QString string;
    string.append("R$ ");
    string.append(QString::number(valor,'F',2));
    return string;
}
