#include "naturalidade.h"

Naturalidade::Naturalidade()
{

}

void Naturalidade::setId(int id)
{
    this->id = id;
}

void Naturalidade::setNome(QString nome)
{
    this->nome = nome;
}

QString Naturalidade::getNome()
{
    return nome;
}

int Naturalidade::getId()
{
    return id;
}
