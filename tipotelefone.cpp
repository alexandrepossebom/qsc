#include "tipotelefone.h"

TipoTelefone::TipoTelefone()
{
}


void TipoTelefone::setId(int id)
{
    this->id = id;
}

void TipoTelefone::setNome(QString nome)
{
    this->nome = nome;
}

QString TipoTelefone::getNome()
{
    return nome;
}

int TipoTelefone::getId()
{
    return id;
}
