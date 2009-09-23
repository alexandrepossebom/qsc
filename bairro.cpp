#include "bairro.h"

Bairro::Bairro()
{
}


void Bairro::setId(int id)
{
    this->id = id;
}
void Bairro::setNome(QString nome)
{
    this->nome = nome;
}
QString Bairro::getNome()
{
    return nome;
}
int Bairro::getId()
{
    return id;
}
