#include "pagamento.h"

Pagamento::Pagamento()
{
}

QString Pagamento::getValorFormatado()
{
    QString string;
    string.append("R$ ");
    string.append(QString::number(valor,'F',2));
    return string;
}
