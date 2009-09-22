#include "estado.h"

Estado::Estado()
{
}

void Estado::setId(int id)
{
    this->id = id;
}

void Estado::setNome(QString nome)
{
    this->nome = nome;
}

int Estado::getId()
{
    return id;
}

QString Estado::getNome()
{
    return nome;
}
