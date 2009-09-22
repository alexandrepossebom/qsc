#include "empresa.h"


Empresa::Empresa()
{
}

void Empresa::setId(int id)
{
    this->id = id;
}

void Empresa::setNome(QString nome)
{
    this->nome = nome;
}

QString Empresa::getNome()
{
    return nome;
}

int Empresa::getId()
{
    return id;
}

QString Empresa::getTelefone()
{
    return telefone;
}

void Empresa::setTelefone(QString telefone)
{
    this->telefone = telefone;
}
