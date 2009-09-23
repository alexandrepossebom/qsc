#include "estado.h"

Estado::Estado()
{
}

void Estado::setUF(QString UF)
{
    this->UF = UF;
}

void Estado::setNome(QString nome)
{
    this->nome = nome;
}

QString Estado::getUF()
{
    return UF;
}

QString Estado::getNome()
{
    return nome;
}
