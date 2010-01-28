#include "cidade.h"

Cidade::Cidade()
{
}

void Cidade::setId(int id)
{
    this->id = id;
}
void Cidade::setNome(QString nome)
{
    this->nome = nome;
}
QString Cidade::getNome()
{
    return nome;
}
int Cidade::getId()
{
    return id;
}
