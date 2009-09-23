#include "endereco.h"

Endereco::Endereco()
{
}

void Endereco::setNome(QString nome)
{
    this->nome = nome;
}

QString Endereco::getNome()
{
    return nome;
}

void Endereco::setId(int id)
{
    this->id = id;
}

int Endereco::getId()
{
    return id;
}

