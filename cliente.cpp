#include "cliente.h"

Cliente::Cliente()
{
}

void Cliente::setNome(QString nome)
{
    this->nome = nome;
}

QString Cliente::getNome()
{
    return nome;
}

void Cliente::setNacionalidade(Nacionalidade nacionalidade)
{
    this->nacionalidade = nacionalidade;
}

Nacionalidade Cliente::getNacionalidade()
{
    return nacionalidade;
}

void Cliente::setNaturalidade(Naturalidade naturalidade)
{
    this->naturalidade = naturalidade;
}

Naturalidade Cliente::getNaturalidade()
{
    return naturalidade;
}
