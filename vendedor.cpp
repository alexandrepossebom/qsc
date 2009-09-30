#include "vendedor.h"

Vendedor::Vendedor()
{
}

void Vendedor::setId(int id)
{
    this->id = id;
}

void Vendedor::setNome(QString nome)
{
    this->nome = nome;
}

QString Vendedor::getNome()
{
    return nome;
}

int Vendedor::getId()
{
    return id;
}

