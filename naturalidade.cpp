#include "naturalidade.h"

Naturalidade::Naturalidade()
{

}

void Naturalidade::setUF(QString UF)
{
    this->UF = UF;
}

void Naturalidade::setNome(QString nome)
{
    this->nome = nome;
}

QString Naturalidade::getNome()
{
    return nome;
}

QString Naturalidade::getUF()
{
    return UF;
}
