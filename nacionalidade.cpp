#include "nacionalidade.h"

Nacionalidade::Nacionalidade()
{
}

void Nacionalidade::setNome(QString nome)
{
    this->nome = nome;
}

QString Nacionalidade::getNome()
{
    return nome;
}


void Nacionalidade::setId(int id)
{
    this->id = id;
}


int Nacionalidade::getId()
{
    return id;
}
