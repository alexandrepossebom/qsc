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

bool Compra::isAtrasada()
{
    foreach(Parcela parcela,parcelas)
    {
        if(!parcela.paga)
            if(parcela.dataVencimento.operator <=(QDate::currentDate()) )
                return true;
    }
    return false;
}
